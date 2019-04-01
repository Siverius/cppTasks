#include <iostream>
using namespace std;
 
class SomeClass
{  
public:
    int field = 0; // указатель на какой-либо участок памяти
    SomeClass()
    {
        std::cout << "Common constructor. field = " << this->field << std::endl;
    }
    SomeClass(const SomeClass &obj)
    {      
        std::cout << "Address of this obj is: " << &obj << 
        " field = " << this->field <<
        std::endl;
    }
    ~SomeClass()   
    {
        std::cout << "Destructor" << std::endl;
    }
};




    void funcShow(SomeClass object)
    {
        std::cout << "Take object as parameter" << std::endl;
    }
 
    SomeClass funcReturnObject()
    {  
        SomeClass object;      
        std::cout << "Give out object" << std::endl;
        return object;
    }
 
int main()
{
	setlocale(LC_ALL, "Rus");
 
    std::cout << "1 -------------------------------------" << std::endl;
    SomeClass obj1; // создаем объект класса

 
    std::cout << "2 -------------------------------------" << std::endl;
    funcShow(obj1); // передаем объект в функцию
 
    std::cout << "3 - 4 ---------------------------------" << std::endl;
    funcReturnObject(); // эта функция возвращает объект
 
    std::cout << "5 -------------------------------------" << std::endl;
    SomeClass obj2 = obj1;  // инициализация объекта при создании
 
}
