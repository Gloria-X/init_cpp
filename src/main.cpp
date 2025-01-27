// 预处理语句
#include <iostream>
// #include <fstream>

// 声明 decoration
// void Log(const char* message);
// int Multiply(int a , int b);

int main (int argc, char *argv[])
{

    // 记录程序运行日志到文件
    // std::ofstream log("output.log");
    // log << "Hello world" << std::endl;
    // log.close();

    // << 重载运算符，实际是个函数，相当于 std::cout.print("Hello world").print(std::endl); 
    // endl 告诉终端跳到下一行
    // std::cout << "Hello world" << std::endl; 

    // // 等待按回车
    // std::cin.get();

    // 等待按任意键继续
    // std::system("pause");

    // main function 可以没有返回值，此时默认返回 0;
    // return 0;

    // Log("Hello world");

    int variable = 8; // -2^31 - 2^31(int 存储为 4B, 即 32 位，其中 1 位为符号位，即 -2^31 到 2^31-1, 即 -2.147e9 到 2.147e)
    unsigned variable_always_positive = 8; // 0 - 2^32-1, 即 0 到 4.295e

    std::cout << variable << std::endl;
    std::cout << variable_always_positive << std::endl;
    std::cin.get();
}

// cmake --build .