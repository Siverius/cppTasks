#include <iostream>

class Stack
{
    struct Elem {
        int num;
        Elem * prev;
        Elem(int num, Elem * prev)
        {
            this->num = num;
            this->prev = prev;
        }
    };

    //pointer to last struct
    Elem * top;
    int counter = 0;
public:
    Stack();
    Stack(const Stack &donor);    
    
    Stack operator=(const Stack &stack);
    void push(int val);
    int pop();
    int getCountElems();
    
    ~Stack();
};

Stack::Stack():top(NULL) {
    std::cout << "Main Constructor" << std::endl;
}

Stack::Stack(const Stack &donor) {
    if(this != &donor) {
        top = NULL;
        Elem * item = donor.top;
        
        Stack temp;

        while(item)
        {
            temp.push(item->num);
            item = item->prev; 
        }
            
        Elem * tempItem = temp.top;
            
        while(tempItem)
        {
            push(tempItem->num);
            tempItem = tempItem->prev; 
        }
        
        std::cout << "Copy Constructor" << std::endl;
    }
}

Stack Stack::operator=(const Stack &stack)
{
    top = NULL;
    Elem * item = stack.top;
    
    Stack temp;

    while(item)
    {
        temp.push(item->num);
        item = item->prev; 
    }

    Elem * tempItem = temp.top;

    while(tempItem)
    {
        push(tempItem->num);
        tempItem = tempItem->prev; 
    }

    return *this;
}

void Stack::push(int val)
{
    Elem * temp = this->top;
    top = new Elem(val, temp);
    counter++;
}

int Stack::pop()
{
    if (!top) return -1;

    int out = top->num;
    Elem * temp = top;
    top = top->prev;
    delete temp;
    counter--;
    return out;
}

int Stack::getCountElems()
{
    return this->counter;
}

Stack::~Stack()
{
    while(top) pop();
    std::cout << "Destructor" << std::endl;
}

int main()
{
    Stack obj;
    obj.push(1);
    obj.push(2);
    obj.push(3);
    
    Stack obj2;
    obj2 = obj;
    
    obj2.push(10);
    obj2.push(11);
    obj2.push(12);
        
    std::cout << obj2.pop() << std::endl;     //12
    std::cout << obj2.pop() << std::endl;     //11
    std::cout << obj2.pop() << std::endl;     //10
    std::cout << obj2.pop() << std::endl;     //3
    std::cout << obj2.pop() << std::endl;     //2
    std::cout << obj2.pop() << std::endl;     //1
    std::cout << obj2.pop() << std::endl;     //-1
    std::cout << obj2.pop() << std::endl;     //-1

    return 0;
}
