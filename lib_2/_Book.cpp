
class Book : public BaseModel
{
public:
    enum statuses {LIBRARY, READER, ALL};
    // fields
    int id;
    std::string name;
    std::string author;
    int status = LIBRARY; //0 - lib, 1 - reader
    // end fields

    Book(std::string n, std::string a, int status = LIBRARY) : BaseModel("book") { }
    Book() : BaseModel("book") { }

    void insert();
    void save();
    std::vector<Book> find(std::string text, int field);
    std::vector<Book> findById(int f_id);
    std::vector<Book> findAll(int whereis = LIBRARY);
    void update(int id);
    void del(int id);
    int anotherStatus();
};

void Book::insert()
{
    std::cout << "\t Insert name of book(string): ";
    std::cin >> name;
    
    std::cout << "\t Insert author (string): ";
    std::cin >> author;
    
    save();
}

void Book::save()
{
    //set id
    setAutoincrement();
    id = autoincrement;
    
    //open file for std::ios::app
    std::ofstream infile(getFilepath(),std::ios::app);
    if(infile.is_open()) {
        //write data
        infile << id << " " << name << " " << author << " " << status << std::endl;
        
        //close file
        infile.close();
    }
    else
    {
        echo("file was not open");
    }   
    return;
}

//maybe it`s not good idea to return vector here, object seems better 
std::vector<Book> Book::findById(int f_id)
{
    std::vector<Book> allBooks = Book::findAll();
    std::vector<Book> foundedBooks;
    
    if(!allBooks.empty())
    {
        auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [f_id](Book & book)->bool{
                //return book.id.find(f_id)!=std::string::npos;
                return (book.id == f_id); //will find all books
            });
        if(fnd != allBooks.end())
        {
            foundedBooks.push_back(*fnd);
        }
    }
    return foundedBooks;
}

//1704
std::vector<Book> Book::find(std::string text, int field)
{
    std::vector<Book> allBooks = Book::findAll();
    std::vector<Book> foundedBooks;

    if(!allBooks.empty())
    {    
        if(field == 1) {
            auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [text](Book & book)->bool{
                    return (book.name.find(text)!=std::string::npos && book.status == LIBRARY);
                });
            if(fnd != allBooks.end())
            {
                foundedBooks.push_back(*fnd);
            }
        }
        else if(field == 2) 
        {
            auto fnd = std::find_if(allBooks.begin(), allBooks.end(), [text](Book & book)->bool{
                    return (book.author.find(text)!=std::string::npos && book.status == LIBRARY);
                });
            if(fnd != allBooks.end())
            {
                foundedBooks.push_back(*fnd);
            }
        }
    }
    
    if(foundedBooks.size() == 0) throw -1;
    
    return foundedBooks;
}

std::vector<Book> Book::findAll(int whereis)
{
    std::ifstream file(getFilepath(),std::ios::app);
    std::vector<Book> rv;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Book book;
            file >> book.id >> book.name >> book.author >> book.status;
            if((whereis == ALL || book.status == whereis) && !file.eof()) {
                rv.push_back(book);
            }
        }
    }
    file.close(); 
    
    return rv;
}

int Book::anotherStatus()
{
    return status == LIBRARY ? READER : LIBRARY;
}

void Book::update(int id)
{    
    std::vector<Book> all = findAll(ALL);
    std::vector<Book>::iterator temp = std::find_if(all.begin(), all.end(), \
        [id](Book & book)->bool{
                return book.id == id;
            }
    );
    if(temp != all.end())
    {    
        //std::vector<Book>::iterator to_upd = temp;
        
        //rewrite file 
        std::ofstream input(getFilepath());
        if(input.is_open())
        {
            input << temp->id << " " \
                  << temp->name << " " \
                  << temp->author << " " \
                  << temp->anotherStatus() << std::endl;
            
            all.erase(temp);

            std::vector<Book>::iterator iter = all.begin();
            while(iter != all.end())
            {
                input << iter->id << " " \
                  << iter->name << " " \
                  << iter->author << " " \
                  << iter->status << std::endl;
                iter++;
            }

            input.close();  
        }     
    }
    
    return;
}

void Book::del(int id)
{
    std::vector<Book> all = findAll();
    std::vector<Book>::iterator to_del = std::find_if(all.begin(), all.end(), \
        [id](Book & book)->bool{
                return book.id == id;
            }
    );
    if(to_del != all.end())
    {
        all.erase(to_del);
    }
    
    //rewrite file 
    std::ofstream input(getFilepath());
    if(input.is_open())
    {
        std::vector<Book>::iterator iter = all.begin();
        while(iter != all.end())
        {
            input << iter->id << " " \
                << iter->name << " " \
                << iter->author << " " \
                << iter->status << std::endl;
                iter++;
        }
        input.close(); 
    }
    return;
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
        std::cout << "5. Show all books" << std::endl;
        std::cout << "6. Update book (change status)" << std::endl;
        std::cout << "7. Delete book" << std::endl;
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
                echo("==================================================");
            }
                break;
            case 6:
            {
                Book b;
                int b_id;
                echo("Input id");
                std::cin >> b_id;
                b.update(b_id);
            }
                break;
            case 7:
            {
                Book b;
                int b_id;
                echo("Input id");
                std::cin >> b_id;
                b.del(b_id);
                break;
            }
            case 0:
            default:
                ever = 0;
        }
    }
}

