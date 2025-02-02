#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <winsock2.h>
#include <ws2tcpip.h>
// 文档：https://libssh2.org/
#include <libssh2.h>

#pragma comment(lib, "ws2_32.lib") // 链接 Winsock 库
#pragma comment(lib, "libssh2.lib") // 链接 libssh2 库

using namespace std;

// https://cloud.tencent.com/developer/article/2474039
// https://cloud.tencent.com/developer/article/2474032?from_column=20421&from=20421

void showSCPUsage() {
    std::cout << "Usage" << std::endl;
    std::cout << "    scp <username>@<IP>:<remote_path> <local_path>\n\n" << std::endl;
    std::cout << "Arguments:\n";
    std::cout << "    <username>     : The username for the remote host.\n";
    std::cout << "    <IP>           : The IP address of the remote host.\n";
    std::cout << "    <remote_path>  : The full path to the file or directory on the remote machine.\n";
    std::cout << "    <local_path>   : The destination path on the local machine.\n\n";
    std::cout << "Example:\n";
    std::cout << "    scp user@192.168.1.10:/home/user/file.txt /local/destination/\n\n";
}

// 初始化 Winsock
int init_winsock() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        cerr << "Failed to initialize Winsock: " << result << endl;
        return 1;
    }
    return 0;
}

// SSH 连接方法
int ssh_connect(const string &remoteHost, int port, const string &username, const string &password, const string &keyFile, LIBSSH2_SESSION **session, SOCKET *sock) {
    // 初始化 Winsock
    if (init_winsock() != 0) {
        return 1;
    }

    // 创建套接字
    *sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (*sock == INVALID_SOCKET) {
        cerr << "Failed to create socket: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // 远程主机信息
    struct sockaddr_in remoteAddr;
    memset(&remoteAddr, 0, sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(port); // 指定端口
    remoteAddr.sin_addr.s_addr = inet_addr(remoteHost.c_str()); // 解析远程主机 IP 地址

    // 连接到远程主机
    if (connect(*sock, (struct sockaddr*)&remoteAddr, sizeof(remoteAddr)) == SOCKET_ERROR) {
        cerr << "Failed to connect to remote host: " << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
        return 1;
    }

    // 初始化 SSH2 会话
    *session = libssh2_session_init();
    if (!*session) {
        cerr << "Failed to initialize SSH session" << endl;
        closesocket(*sock);
        WSACleanup();
        return 1;
    }

    // 使用套接字进行握手
    if (libssh2_session_handshake(*session, *sock) != 0) {
        cerr << "Failed to handshake with the server" << endl;
        libssh2_session_free(*session);
        closesocket(*sock);
        WSACleanup();
        return 1;
    }

    // 身份验证
    if (!keyFile.empty()) {
        // 使用密钥文件进行身份验证
        if (libssh2_userauth_publickey_fromfile(*session, username.c_str(), keyFile.c_str(), NULL, password.c_str()) != 0) {
            cerr << "Authentication failed using key!" << endl;
            libssh2_session_free(*session);
            closesocket(*sock);
            WSACleanup();
            return 1;
        }
    } else {
        // 使用密码进行身份验证
        if (libssh2_userauth_password(*session, username.c_str(), password.c_str()) != 0) {
            cerr << "Authentication failed using password!" << endl;
            libssh2_session_free(*session);
            closesocket(*sock);
            WSACleanup();
            return 1;
        }
    }

    return 0; // 成功
}

void SCP(const std::string &remoteHost, const std::string &remoteFile, const std::string &localFile, const std::string &username, const std::string &password, const std::string &keyFile) {
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    FILE *localFileStream;
    char buffer[1024];
    int bytesRead, bytesWritten;
    SOCKET sock;

    // 尝试使用 SSH 连接
    if (ssh_connect(remoteHost, 22, username, password, keyFile, &session, &sock) != 0) {
        std::cerr << "Failed to establish SSH connection" << std::endl;
        return;
    }

    // 打开 SCP 通道接收文件
    channel = libssh2_scp_recv2(session, remoteFile.c_str(), NULL);
    if (!channel) {
        std::cerr << "Failed to open SCP channel" << std::endl;
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return;
    }

    // 打开本地文件以写入内容
    localFileStream = fopen(localFile.c_str(), "wb");
    if (!localFileStream) {
        std::cerr << "Failed to open local file" << std::endl;
        libssh2_channel_free(channel);
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return;
    }

    // 从远程读取并写入本地文件
    while ((bytesRead = libssh2_channel_read(channel, buffer, sizeof(buffer))) > 0) {
        bytesWritten = fwrite(buffer, 1, bytesRead, localFileStream);
        if (bytesWritten != bytesRead) {
            std::cerr << "Error writing to local file" << std::endl;
            break;
        }
    }

    // 清理资源
    fclose(localFileStream);
    libssh2_channel_free(channel);
    libssh2_session_free(session);
    closesocket(sock);  // 关闭套接字
    WSACleanup();       // 清理 Winsock

    std::cout << "File transfer complete!" << std::endl;
}
