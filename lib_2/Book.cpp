#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "base/BaseModel.cpp"
#include "_Book.cpp"
#include "_Reader.cpp"
#include "_Inventory.cpp"

int main()
{    
    int ever = 1;
    int choice;
    while(ever)
    {
        std::cout << "Select something: " << std::endl;
        std::cout << "1. Books " << std::endl;
        std::cout << "2. Readers " << std::endl;
        std::cout << "3. Issue some books " << std::endl;
        std::cout << "4. Pick up some book " << std::endl;
        std::cout << "0. Exit " << std::endl;
        
        std::cin >> choice;
        switch(choice)
        {
            case 1:
                BookMenu();
                break;
            case 2:
                ReaderMenu();
                break;
            case 3:
                InventoryMenu();
                break;
            default:
                ever = 0;
        }
    }
    
    return 0;
}
