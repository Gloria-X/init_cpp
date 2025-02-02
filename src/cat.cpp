#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void showCatUsage() {
    std::cout << "Usage" << std::endl;
    std::cout << "    cat <path>" << std::endl;
}

void ReadFile(const string& path) {
    ifstream file(path);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file " << path << "! Please check the file path or permissions." << endl;
    }
}
