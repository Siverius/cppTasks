#include <iostream>
#include <fstream>

int createFile()
{
    std::ofstream file;
    file.open("test.txt");
    if(!file.is_open())
    {
        std::cout << "bad" << std::endl;
        return -1;
    }
    
    std::cout << "good" << std::endl;
    file.close();
    return 0;
}

int main()
{
    int ever = 1;
    int choise;
    while(ever) {
        std::cout << "insert your choice ";
        std::cin >> choise;
        if (choise)
        {
            createFile();
        }
        return 0;
        ever = 0;
    }
}
