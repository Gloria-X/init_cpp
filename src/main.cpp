#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "cat.h"
#include "scp.h"

using namespace std;

int main() {
    string input;
    
    cout << "Please enter a command (e.g., init linux):" << endl;
    getline(cin, input);

    if (input == "init linux") {
        cout << "Entering init_linux environment..." << endl;
        cout << "init_linux> ";
        
        while (true) {
            getline(cin, input);

            stringstream ss(input); // 将字符串视为流对象
            vector<string> args; // 动态数组，用来存储分割后的字符串
            string temproray_storage; // 临时存储拆分后的字符串

            while (ss >> temproray_storage) {
                args.push_back(temproray_storage);  // 按空格拆分命令
            }

            if (args.empty()) continue;

            string command = args[0];

            if (command == "scp") {
                if (args.size() < 3) {
                    showSCPUsage();
                } else {
                    cout << "herre..." << endl;
                    string scpCommand = args[1];  //<username>@<IP>:<remote_path>
                    string localFile = args[2];

                    // // TODO: 解析端口号（如果存在）- 解析失败
                    // size_t portPos = scpCommand.find("-p");
                    int port = 22; // 默认端口号
                    string username, remoteHost, remoteFile;

                    // if (portPos != string::npos) {
                    //     // 提取端口号
                    //     size_t colonPos = scpCommand.find(':', portPos + 2); // 查找端口号后的冒号
                    //     if (colonPos == string::npos) {
                    //         cerr << "Invalid format for port specification." << endl;
                    //         showSCPUsage();
                    //         return 1; // 如果格式错误，退出程序
                    //     }
                    //     string portStr = scpCommand.substr(portPos + 2, colonPos - portPos - 2);
                    //     port = stoi(portStr);

                    //     // 提取用户名和远程路径
                    //     scpCommand = scpCommand.substr(colonPos + 1); // 去掉端口号部分
                    // }

                    // 解析用户名和远程路径
                    size_t atPos = scpCommand.find('@');
                    if (atPos == string::npos) {
                        cerr << "Invalid format for remote host and user." << endl;
                        showSCPUsage();
                    }

                     // 获取用户名
                    username = scpCommand.substr(0, atPos);

                    // 获取 IP 和 remote path
                    string remoteHostAndFile = scpCommand.substr(atPos + 1);
                    size_t colonPos = remoteHostAndFile.find(':');
                    if (colonPos == string::npos) {
                        cerr << "Invalid format for remote host and file path." << endl;
                        showSCPUsage();
                    }

                    remoteHost = remoteHostAndFile.substr(0, colonPos);
                    remoteFile = remoteHostAndFile.substr(colonPos + 1);

                    string keyFile = "C:\\Users\\Gloria_X\\.ssh\\id_ed25519.ppk";
                    string password = "your_password"; // 初始密码

                    cout << "Username: " << username << endl;
                    cout << "Remote Host: " << remoteHost << endl;
                    cout << "Port: " << port << endl;
                    cout << "Remote File: " << remoteFile << endl;
                    cout << "Local File: " << localFile << endl;

                    // // 尝试使用密钥文件进行连接
                    // if (ssh_connect(remoteHost, port, username, "", keyFile, NULL, NULL) != 0) {
                    //     cout << "SSH connection failed. Please enter password:" << endl;
                    //     cin >> password; // 用户重新输入密码
                    //     if (ssh_connect(remoteHost, 22, username, password, "", NULL, NULL) != 0) {
                    //         cerr << "Failed to connect using password" << endl;
                    //         return 1;
                    //     }
                    // }

                    // // 调用 SCP 方法
                    // SCP(remoteHost, remoteFile, localFile, username, password);
                }
            }
            else if (command == "cat") {
                if (args.size() == 1) {
                    cout << "Error: Please provide a valid file path." << endl;
                    showCatUsage();
                } else {
                    ReadFile(args[1]);
                }
            }
            else if (command == "exit") {
                cout << "Exiting init_linux environment..." << endl;
            } 
            else {
                cout << "Invalid command! Please enter a valid command." << endl;
            }
            
            cout << "init_linux> ";
        }
    } 
    else {
        cout << "Invalid initial command!" << endl;
    }

    return 0;
}

// cmake --build .
