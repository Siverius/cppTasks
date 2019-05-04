#include <iostream>
#include <string>

template<typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    
    void push_back(T data);
    
private:
    //класс Node реализован в private секции для того, чтобы
    //доступ к нему был невозможен кроме как через класс Stack
    //template<typename T>
    class Node
    {
    public:
        Node * pNext; //указатель на сл.элемент
        T data;
        
        //когда добавляем последний элемент, в указатель
        //ничего не передаётся. Необходимо добавить значение 
        //по умолчанию.
        
        //если при создании элемента не передаётся data
        //нужно тоже это обработать
        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node *head;
    //Node<T> *head;
    //количество элементов для корректного прохода по стеку
    int size;
};

template<typename T>
Stack<T>::Stack()
{
    size = 0;
    head = nullptr;
}
template<typename T>
Stack<T>::~Stack(){}

template<typename T>
void Stack<T>::push_back(T data)
{
	if (head == nullptr) 
	{
		head = new Node<T>(data);
	}
	else
	{
	}
}

int main()
{
	Stack<int> stck;
	stck.push_back(5);
	return 0;
}
