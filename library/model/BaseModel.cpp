#include <iostream>

class BaseModel()
{
    struct BaseTuple
    {
        int id;
    }

    BaseTuple attributes;
    std::string data;
    void validation(); // проверка на корректность
    void save(); //сохранение
}
