#include <iostream>
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

using namespace std;

void SCP(const string &remoteHost, const string &remoteFile, const string &localFile, const string &username, const string &password) {
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    FILE *localFileStream;
    char buffer[1024];
    int bytesRead, bytesWritten;

    // 创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Failed to create socket" << endl;
        return;
    }

    // 远程主机信息
    struct sockaddr_in remoteAddr;
    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(22); // 默认 SSH 端口
    remoteAddr.sin_addr.s_addr = inet_addr(remoteHost.c_str()); // 解析远程主机 IP 地址

    // 连接到远程主机
    if (connect(sock, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) < 0) {
        cerr << "Failed to connect to remote host" << endl;
        close(sock);
        return;
    }

    // 初始化 SSH2 会话
    session = libssh2_session_init();
    if (!session) {
        cerr << "Failed to initialize SSH session" << endl;
        close(sock);
        return;
    }

    // 使用套接字进行握手
    if (libssh2_session_handshake(session, sock) != 0) {
        cerr << "Failed to handshake with the server" << endl;
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // 身份验证
    if (libssh2_userauth_password(session, username.c_str(), password.c_str()) != 0) {
        cerr << "Authentication failed!" << endl;
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // 打开 SCP 通道接收文件
    channel = libssh2_scp_recv(session, remoteFile.c_str(), NULL);
    if (!channel) {
        cerr << "Failed to open SCP channel" << endl;
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // 打开本地文件以写入内容
    localFileStream = fopen(localFile.c_str(), "wb");
    if (!localFileStream) {
        cerr << "Failed to open local file" << endl;
        libssh2_channel_free(channel);
        libssh2_session_free(session);
        close(sock);
        return;
    }

    // 从远程读取并写入本地文件
    while ((bytesRead = libssh2_channel_read(channel, buffer, sizeof(buffer))) > 0) {
        bytesWritten = fwrite(buffer, 1, bytesRead, localFileStream);
        if (bytesWritten != bytesRead) {
            cerr << "Error writing to local file" << endl;
            break;
        }
    }

    // 清理资源
    fclose(localFileStream);
    libssh2_channel_free(channel);
    libssh2_session_free(session);
    close(sock);  // 关闭套接字

    cout << "File transfer complete!" << endl;
}
