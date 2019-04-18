class Book 
{
    const int STATUS_LIB = 0;
    const int STATUS_READER = 1;
    
    std::string dataDir = "data/";
    std::string filename = "book";
    std::string ext = ".txt";
    
    std::string fn = dataDir + filename + ext;
public:
    int id;
    std::string name;
    std::string author;
    int status = 0; //0 - lib, 1 - reader
    
    Book(std::string n, std::string a): name(n), author(a) { }
    Book(){}

    void insert();
    bool save();  //  
    std::vector<Book> find(std::string text, int field, int whereis = 0);
    std::vector<Book> findById(int f_id, int whereis = 0);
    std::vector<Book> findAll(int whereis = 0);
    void update();
    void del();
};

//1704
void Book::insert()
{
    std::cout << "\t Insert name of book(string): ";
    std::string t_name;
    std::cin >> t_name;
    
    std::cout << "\t Insert author (string): ";
    std::string t_author;
    std::cin >> t_author;
    
    Book book(t_name, t_author);
    book.save();
}

//1704
bool Book::save()
{
    //get id
    AI ai(filename);
    id = ai.get_id();
    
    //open file for std::ios::app
    std::ofstream infile(fn,std::ios::app);
    
    //write data
    infile << id << " " << name << " " << author << " " << status << std::endl;
    
    //close file
    infile.close();
    
    return true;
}

std::vector<Book> Book::findById(int f_id, int status)
{
    std::vector<Book> allBooks = Book::findAll();
    std::vector<Book> foundedBooks;
    
    if(!allBooks.empty())
    {
        auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [f_id](Book & book)->bool{
                //return book.id.find(f_id)!=std::string::npos;
                return book.id == f_id;
            });
        if(fnd != allBooks.end())
        {
            foundedBooks.push_back(*fnd);
        }
    }
    return foundedBooks;
}

//1704
std::vector<Book> Book::find(std::string text, int field, int status)
{
    std::vector<Book> allBooks = Book::findAll();
    std::vector<Book> foundedBooks;

    if(!allBooks.empty())
    {    
        if(field == 1) {
            auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [text](Book & book)->bool{
                    return book.name.find(text)!=std::string::npos;
                });
            if(fnd != allBooks.end())
            {
                foundedBooks.push_back(*fnd);
            }
        }
        else if(field == 2) 
        {
            auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [text](Book & book)->bool{
                    return book.author.find(text)!=std::string::npos;
                });
            if(fnd != allBooks.end())
            {
                foundedBooks.push_back(*fnd);
            }
        }
    }
    
    if(foundedBooks.size() == 0)
    {
        Book emptyBook;
        foundedBooks.push_back(emptyBook);
    }
    
    return foundedBooks;
}

std::vector<Book> Book::findAll(int whereis)
{
    std::ifstream file(fn,std::ios::app);
    std::vector<Book> rv;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Book book;
            file >> book.id >> book.name >> book.author >> book.status;
            rv.push_back(book);
        }
    }
    file.close(); 
    
    return rv;
}

void BookMenu()
{
    int ever = 1;
    int choice;
    Book book;
    while(ever)
    {
        std::cout << "Select something:" << std::endl;
        std::cout << "1. Add book" << std::endl;
        std::cout << "2. Hello" << std::endl;
        std::cout << "3. Find book by name" << std::endl;
        std::cout << "4. Find book by author" << std::endl;
        std::cout << "0. Exit " << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                book.insert();
                break;
            }
            case 2:
            {
                std::cout << "Hello :)" << std::endl;
                break;
            }
            case 3:
            {
                std::string piece;
                std::cout << "Insert Book name" << std::endl;
                std::cin >> piece;
                Book b;
                std::vector<Book> bks = b.find(piece, 1); //<-
                std::vector<Book>::iterator it = bks.begin();
                while(it != bks.end())
                {
                    std::cout << it->id << " " << it->name << " " << it->author << std::endl;
                    ++it;
                }
            }
                break;
            case 4:
            {
                std::string piece;
                std::cout << "Insert Author name" << std::endl;
                std::cin >> piece;
                Book b;
                std::vector<Book> bks = b.find(piece, 2);
                std::vector<Book>::iterator it = bks.begin();
                while(it != bks.end())
                {
                    std::cout << it->id << " " << it->name << " " << it->author << std::endl;
                    ++it;
                }
            }
                break;
            case 5:
            {
                Book b;
                std::vector<Book> bks = b.findAll();
                std::vector<Book>::iterator it = bks.begin();
                while(it != bks.end())
                {
                    std::cout << it->id << " " << it->name << " " << it->author << std::endl;
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
