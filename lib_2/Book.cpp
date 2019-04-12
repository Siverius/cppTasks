#include <iostream>
#include <fstream>
#include <string>
 
class Book 
{
    const int STATUS_LIB = 0;
    const int STATUS_READER = 1;
public:
    //int _id;
    std::string name;
    std::string author;
    int status = 0; //0 - lib, 1 - reader
    Reader(std::string n, std::string a, int s): name(n), author(a), status(s) { }
    Reader(){ }
};

std::ostream& operator << (std::ostream &os, const Book &b)
{
    return os /*<< r._id*/ << r.name << " " << r.author << r.status;
}
std::istream& operator >> (std::istream& in, Book& b)
{
    in /*>> r._id*/ >> r.name >> r.age >> r.status;
    return in;
}


void fillBooks(std::vector<Book> * book);
void saveBooks(std::vector<Book> * book);
void test();

int main()
{
    const int EVER = 1;
    const int OUT = 0;
    
    int iter = EVER;
        
    std::vector<Book> books;
    
    while(iter)
    {
        int choice = 3;
        std::cout << "Insert number of your choice please: " << std::endl;
        std::cout << "1. Add book " << std::endl;
        std::cout << "2. Save inserted books and exit " << std::endl;
        std::cout << "3. test " << std::endl;
        std::cout << "0. Drop inserted data and exit " << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                fillBooks(&books);
                break;
            }
            case 2:
            {
                saveBooks(&books);
                iter = OUT;
                break;
            }
            case 3:
                test();
                break;
            case 4:
            default:
                iter = OUT;
        }
    }
    
    return 0;
}

void fillBooks(std::vector<Reader> * book)
{
    std::cout << "\t Insert name (string): ";
    std::string t_name;
    std::cin >> t_name;
    std::cout << "\t Insert age (int): ";
    int t_age;
    std::cin >> t_age;
    Book r(t_name, t_age);
    book->push_back(r);
}

void saveBooks(std::vector<Book> * book)
{
    std::ofstream out("data/books.txt"); 
    if (out.is_open())
    {
        auto iter = book->begin();
        while(iter!=book->end())
        {
            out << *iter << std::endl;// получаем элементы через итератор
            ++iter;             // перемещаемся вперед на один элемент
        }
    }
    out.close();
}

std::vector<Book> getBooksVector()
{
    std::ifstream in("data/books.txt");
    std::vector<Book> rv;
    if (in.is_open())
    {
        std::string name;
        int age;
        while (in >> name >> age)
        {
            rv.push_back(Book(name, age));
        }
    }
    in.close();
    
    return rv;
}

template <typename T> 
T getDataVector() 
{
    std::string data_file = "books"; // <===========
    std::string data_dir = "data/";
    std::string file_ext = ".txt";
    
    std::ifstrean in(data_dir + data_file + file_ext);
    T rv;
    if(in.is_open())
    {
        std::string name; // <=======
        int age
    }
    
    
    
}
























void test()
{
    for (int i = 0; i < getReadersVector().size(); i++)
    {
        std::cout << getReadersVector()[i].name << " - " << getReadersVector()[i].age << std::endl;
    }
}


















