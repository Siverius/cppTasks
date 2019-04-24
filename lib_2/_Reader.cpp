class Reader : public BaseModel
{
public:
    int id;
    std::string name;
    int age;
    
    Reader(std::string n, int a) : BaseModel("reader") { }
    Reader() : BaseModel("reader") {}

    void insert();
    bool save();  
    std::vector<Reader> find(std::string text, int field);
    std::vector<Reader> findById(int f_id);
    std::vector<Reader> findAll();
    void update(int id);
    void del(int id);
};

void Reader::insert()
{
    std::cout << "\t Insert name of reader(string): ";
    std::cin >> name;

    std::cout << "\t Insert readers age (int): ";
    std::cin >> age;

    save();
}

bool Reader::save()
{
    //get id
    setAutoincrement();
    id = autoincrement;
    
    //open file for std::ios::app
    std::ofstream infile(getFilepath(),std::ios::app);
    if(infile.is_open()) {    
        //write data
        infile << id << " " << name << " " << age << std::endl;
        
        //close file
        infile.close();
    }
    else
    {
        echo("file was not open");
    }
     
    return true;
}

std::vector<Reader> Reader::findById(int f_id)
{
    std::vector<Reader> allReaders = Reader::findAll();
    std::vector<Reader> foundedReaders;
    
    if(!allReaders.empty())
    {
        auto fnd = std::find_if(allReaders.begin(), allReaders.end(), [f_id](Reader & reader)->bool{
                return reader.id == f_id;
            });
        if(fnd != allReaders.end())
        {
            foundedReaders.push_back(*fnd);
        }
    }
    return foundedReaders;
}

//ToDo: redo using template
std::vector<Reader> Reader::find(std::string text, int field)
{
    std::vector<Reader> allReaders = Reader::findAll();
    std::vector<Reader> foundedReaders;

    if(!allReaders.empty())
    {
        std::vector<Reader>::iterator fnd = std::find_if(allReaders.begin(), allReaders.end(), [text](Reader & reader)->bool{
                return reader.name.find(text)!=std::string::npos;});
        if(fnd != allReaders.end())
        {
            foundedReaders.push_back(*fnd);
        }
    }
    
    if(foundedReaders.size() == 0) throw -1;
        
    return foundedReaders;
}

std::vector<Reader> Reader::findAll()
{
    std::ifstream file(getFilepath(),std::ios::app);
    std::vector<Reader> rv;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Reader reader;
            file >> reader.id >> reader.name >> reader.age;
            if(!file.eof())
            {
                rv.push_back(reader);
            }
        }
    }
    file.close(); 
    
    return rv;
}

//ToDo: make this usefull - change name and age, maybe by std::map
void Reader::update(int id)
{    
    std::vector<Reader> all = findAll();
    
    //findById
    std::vector<Reader>::iterator temp = std::find_if(all.begin(), all.end(), \
        [id](Reader & reader)->bool{
                return reader.id == id;
            }
    );
    if(temp != all.end())
    {
        //rewrite file 
        std::ofstream input(getFilepath());
        if(input.is_open())
        {
            input << temp->id << " " \
                  << temp->name << " " \
                  << temp->age << std::endl;
            
            all.erase(temp);

            std::vector<Reader>::iterator iter = all.begin();
            while(iter != all.end())
            {
                input << iter->id << " " \
                  << iter->name << " " \
                  << iter->age << std::endl;
                iter++;
            }

            input.close();  
        }     
    }
    
    return;
}

void Reader::del(int id)
{
    std::vector<Reader> all = findAll();
    std::vector<Reader>::iterator to_del = std::find_if(all.begin(), all.end(), \
        [id](Reader & reader)->bool{
                return reader.id == id;
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
        std::vector<Reader>::iterator iter = all.begin();
        while(iter != all.end())
        {
            input << iter->id << " " \
                << iter->name << " " \
                << iter->age << std::endl;
                iter++;
        }
        input.close(); 
    }
    return;
}

/*
std::vector<Inventory> Reader::Has_Many(Inventory inv)
{
    inv.findAll();
    if(inv.size() == 0) throw -1;
    std::vector<Inventory>::iterator it = inv.begin();
    std::vector<Inventory> result;
    
    while(it != inv.end())
    {
        std::vector<Inventory>::iterator fnd = std::find_if(inv.begin(), inv.end(), [id](Inventory & inv)->bool{
            return id == inv.reader_id;
            });
        if(fnd ! = inv.end())
        {
            result.push_back(*fnd);
        }
        ++it;
    }
    
    return result;
}
*/
void ReaderMenu()
{
    int ever = 1;
    int choice;
    Reader reader;
    while(ever)
    {
        std::cout << "Select something:" << std::endl;
        std::cout << "1. Add reader" << std::endl;
        std::cout << "2. Hello" << std::endl;
        std::cout << "3. Find reader by name" << std::endl;
        std::cout << "4. Find books user having" << std::endl;
        std::cout << "5. Show all Readers" << std::endl;
        std::cout << "6. DeleteReader" << std::endl;
        std::cout << "0. Exit " << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                reader.insert();
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
                std::cout << "Insert Reader name" << std::endl;
                std::cin >> piece;
                try
                {
                    Reader r;
                    std::vector<Reader> rdr = r.find(piece, 1);
                    std::vector<Reader>::iterator it = rdr.begin();
                    while(it != rdr.end())
                    {
                        std::cout << it->id << " " << it->name << " " << it->age << std::endl;
                        ++it;
                    }
                } 
                catch (int i)
                {
                    std::cout << "No readers has been founded" << std::endl;
                }
            }
                break;
            case 4:
            {
                std::cout << "Hello, I`ll find books. Just insert users id" << std::endl;
            }
                break;
            case 5:
            {
                Reader r;
                std::vector<Reader> rdr = r.findAll();
                std::vector<Reader>::iterator it = rdr.begin();
                while(it != rdr.end())
                {
                    std::cout << it->id << " " << it->name << " " << it->age << std::endl;
                    ++it;
                }
            }
                break;
            
            case 6:
            {
                Reader r;
                int r_id;
                echo("Input ID");
                std::cin >> r_id;
                r.del(r_id);
            }
            break;
            
            case 0:
            default:
                ever = 0;
        }
    }
}
