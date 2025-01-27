// 预处理语句
#include <iostream>
// #include <fstream>

// 声明 decoration
void Log(const char* message);
int Multiply(int a , int b);

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
    std::cout << Multiply(2, 3) << std::endl;
    std::cin.get();
}

// cmake --build .