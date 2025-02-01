#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "cat.h"

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
                cout << "Executing SCP command..." << endl;
            }
            else if (command == "cat") {
                if (args.size() == 1) {
                    std::cout << "Error: Please provide a valid file path." << std::endl;
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
