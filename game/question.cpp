#include <iostream>

class Helper
{
public:
    void insert_string(char * name, int length)
    {
        std::cout << "Insert string. " << length << " characters maximum: " << std::endl;
        std::cin >> name;
    }
};

class GreatClass
{
public:
    char my_string[10];
    
    void insert_string()
    {
        Helper helper;
        helper.insert_string(this->my_string, 10);
    }
};

int main()
{
    GreatClass gc;
    gc.insert_string();
    
    std::cout << "inserted value >> " << gc.my_string << std::endl;
    
    return 0;
}
