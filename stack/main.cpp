#include <iostream>

struct Elem {
    int num;
    Elem * prev;
    Elem(int num, Elem * prev)
    {
        this->num = num;
        this->prev = prev;
    }
};

class Stack
{
    //pointer to last struct
    Elem * top = NULL;
    int counter = 0;
public:
    Stack() {
        top = NULL;
    }
    ~Stack()
    {
        while(top) pop();
    }
    
    void push(int val)
    {
        Elem * temp = this->top;
        top = new Elem(val, temp);
        counter++;
    }
    
    int pop()
    {
        if (!top)
        {
            return -1;
        }
        int out = top->num;
        Elem * temp = top;
        top = top->prev;
        delete temp;
        counter--;
        return out;
    }
};

int main()
{
    Stack obj;
    obj.push(1);
    obj.push(2);
    obj.push(3);
    std::cout << obj.pop() << std::endl;    //3
    std::cout << obj.pop() << std::endl;    //2
    std::cout << obj.pop() << std::endl;     //1
    std::cout << obj.pop() << std::endl;     //0
    std::cout << obj.pop() << std::endl;     //0
    std::cout << obj.pop() << std::endl;     //0
    std::cout << obj.pop() << std::endl;     //0
    return 0;
}
