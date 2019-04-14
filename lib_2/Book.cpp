#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
 
class Book 
{
    const int STATUS_LIB = 0;
    const int STATUS_READER = 1;
public:
    //int _id;
    std::string name;
    std::string author;
    int status = 0; //0 - lib, 1 - reader
    Book(std::string n, std::string a, int s): name(n), author(a), status(s) { }
    Book(){ }
};

std::ostream& operator << (std::ostream &os, const Book &b)
{
    return os << b.name << " " << b.author << b.status;
}
std::istream& operator >> (std::istream& in, Book& b)
{
    in >> b.name >> b.author >> b.status;
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

void fillBooks(std::vector<Book> * book)
{
    std::cout << "\t Insert name of book(string): ";
    std::string t_name;
    std::cin >> t_name;
    
    std::cout << "\t Insert author (string): ";
    std::string t_author;
    std::cin >> t_author;
    
    std::cout << "\t Insert status (int, default 0): ";
    int t_status;
    std::cin >> t_status;
    
    Book b(t_name, t_author, t_status);
    book->push_back(b);
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
        std::string author;
        int status;
        while (in >> name >> author >> status)
        {
            rv.push_back(Book(name, author, status));
        }
    }
    in.close();
    
    return rv;
}

std::vector<Book> findBookByName(std::string book_name, int status = 0)
{
    std::vector<Book> allBooks = getBooksVector();
    std::vector<Book> foundedBooks;
    if(!allBooks.empty()){
        
        auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [book_name](Book & book)->bool{
                return book.name.find(book_name)!=std::string::npos;
            });
        
        foundedBooks.push_back(*fnd);
    }
    return foundedBooks;
}

std::vector<Book> findBookByAuthor(std::string author, int status = 0)
{
    std::vector<Book> allBooks = getBooksVector();
    return allBooks;
}
/*
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
*/























void test()
{
    for (int i = 0; i < getBooksVector().size(); i++)
    {
        std::cout << getBooksVector()[i].name << " - " << getBooksVector()[i].author << std::endl;
    }
}


















