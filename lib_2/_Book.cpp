class Book 
{
    const int STATUS_LIB = 0;
    const int STATUS_READER = 1;
public:
    int id;
    std::string name;
    std::string author;
    int status = 0; //0 - lib, 1 - reader
    Book(std::string n, std::string a, int s): name(n), author(a), status(s) { }
    Book(){ }
};

std::ostream& operator << (std::ostream &os, const Book &b)
{
    return os << b.id << " " << b.name << " " << b.author << " " << b.status;
}

std::istream& operator >> (std::istream& in, Book& b)
{
    in >> b.id >> b.name >> b.author >> b.status;
    return in;
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
    std::ifstream datafile("data/books.txt");
    std::vector<Book> rv;
    if (datafile.is_open())
    {
        Book f_book;
        while (datafile >> f_book)
        {
            rv.push_back(f_book);
        }
    }
    datafile.close(); 
    
    return rv;
}

std::vector<Book> findBookByName(std::string book_name, int status = 0)
{
    std::vector<Book> allBooks = getBooksVector();    
    std::vector<Book> foundedBooks;
    
    if(!allBooks.empty())
    {
        auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [book_name](Book & book)->bool{
                return book.name.find(book_name)!=std::string::npos;
            });
        
        foundedBooks.push_back(*fnd);
    }
    return foundedBooks;
}

std::vector<Book> findBookByAuthor(std::string book_author, int status = 0)
{
    std::vector<Book> allBooks = getBooksVector();    
    std::vector<Book> foundedBooks;
    
    if(!allBooks.empty())
    {
        auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [book_author](Book & book)->bool{
                return book.author.find(book_author)!=std::string::npos;
            });
        
        foundedBooks.push_back(*fnd);
    }
    return foundedBooks;
}

void BookMenu()
{
    int ever = 1;
    int choice;
    std::vector<Book> books;
    while(ever)
    {
        std::cout << "Select something: " << std::endl;
        std::cout << "1. Add book " << std::endl;
        std::cout << "2. Save inserted books and exit " << std::endl;
        std::cout << "3. Find book by name " << std::endl;
        std::cout << "4. Find book by author " << std::endl;
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
                choice = 0;
                break;
            }
            case 3:
            {
                std::string piece;
                std::cout << "Insert Book name" << std::endl;
                std::cin >> piece;
                std::vector<Book> bks = findBookByName(piece);
                std::vector<Book>::iterator it = bks.begin();
                while(it != bks.end())
                {
                    std::cout << *it << std::endl;
                    ++it;
                }
            }
                break;
            case 4:
            {
                std::string piece;
                std::cout << "Insert author name" << std::endl;
                std::cin >> piece;
                std::vector<Book> bks = findBookByAuthor(piece);
                std::vector<Book>::iterator it = bks.begin();
                while(it != bks.end())
                {
                    std::cout << *it << std::endl;
                    ++it;
                }
            }
                break;
            
            case 0:
            default:
                ever = 0;
        }
    }
}
