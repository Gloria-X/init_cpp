#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "cat.h"
#include "scp.h"

using namespace std;

int main() {
    string input;

    while (true) {
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
                        string scpCommand = args[1];  //<username>@<IP>:<remote_path>
                        string localFile = args[2];

                        // 解析端口号（如果存在）
                        int port = 22; // 默认端口号
                        string username, remoteHost, remoteFile;

                        for (size_t i = 0; i < args.size(); ++i) {
                            if (args[i] == "-p" && i + 1 < args.size()) { // 确保 -p 后面有值
                                port = std::stoi(args[i + 1]);
                                scpCommand = args[i + 2];  //-p abc <username>@<IP>:<remote_path>
                                localFile = args[i + 3];
                                break;
                            }
                        }

                        // 解析用户名和远程路径
                        size_t atPos = scpCommand.find('@'); // 返回 @ 在字符串中的位置（从0开始计数）
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

                        string privateKeyFile = "C:\\Users\\Gloria_X\\.ssh\\id_ed25519";
                        string publicKeyFile = "C:\\Users\\Gloria_X\\.ssh\\id_ed25519.pub";
                        string password = "init";

                        cout << "Username: " << username << endl;
                        cout << "Remote Host: " << remoteHost << endl;
                        cout << "Port: " << port << endl;
                        cout << "Remote File: " << remoteFile << endl;
                        cout << "Local File: " << localFile << endl;

                        if (ssh_connect(remoteHost, port, username, "", privateKeyFile, publicKeyFile) == 0) {
                            // 如果使用密钥文件连接成功，直接调用 SCP
                            SCP(remoteHost, port, username, "", privateKeyFile, publicKeyFile, remoteFile, localFile);
                            cout << "SCP transfer completed successfully." << endl;
                        } else {
                            // 如果使用密钥文件连接失败，提示用户输入密码
                            cout << "SSH connection failed. Please enter password:" << endl;
                            cin >> password;

                            // 使用密码重新尝试连接
                            if (ssh_connect(remoteHost, port, username, password, "", "") == 0) {
                                // 如果使用密码连接成功，调用 SCP
                                SCP(remoteHost, port, username, password, "", "", remoteFile, localFile);
                                cout << "SCP transfer completed successfully." << endl;
                            } else {
                                // 如果密码连接失败，输出错误信息并退出
                                cerr << "Failed to connect using password" << endl;
                                std::cin.get();
                                return 1;
                            }
                        }

                        std::cin.get();
                    };
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
                    return 0;
                } 
                else {
                    cout << "Invalid command! Please enter a valid command." << endl;
                }
                
                cout << "init_linux> ";
            }
        } 
        else if (input == "exit") {
            cout << "Exiting program." << endl;
            return 0;
        } else {
            cout << "Invalid initial command! Please try again." << endl;
        }
    }

    return 0;
}

// cmake --build .
// .\init_cpp.exe > output.log 2>&1
// scp -p 45239 xusunyue@106.14.28.85:/home/xusunyue/.ssh/authorized_keys C:\\code\\\xsy\\init_cpp\\authorized_keys
// C:\code\xsy\init_cpp\authorized_keys