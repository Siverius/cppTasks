#include "library.h"

int main()
{    
    int ever = 1;
    int choice;
    while(ever)
    {
        system("cls");
        std::cout << "Select something: " << std::endl;
        std::cout << "1. Books " << std::endl;
        std::cout << "2. Readers " << std::endl;
        std::cout << "3. Inventory " << std::endl;
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
