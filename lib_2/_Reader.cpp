class Reader 
{
    std::string dataDir = "data/";
    std::string filename = "reader";
    std::string ext = ".txt";
    
    std::string fn = dataDir + filename + ext;
public:
    int id;
    std::string name;
    int age;
    
    Reader(std::string n, int a): name(n), age(a) { }
    Reader(){}

    void insert();
    bool save();  
    //template?  
    std::vector<Reader> find(std::string text, int field, int whereis = 0);
    std::vector<Reader> findById(int f_id, int whereis = 0);
    std::vector<Reader> findAll(int whereis = 0);
    void update();
    void del();
};

void Reader::insert()
{
    std::cout << "\t Insert name of reader(string): ";
    std::string t_name;
    std::cin >> t_name;
    
    std::cout << "\t Insert readers age (int): ";
    int t_age;
    std::cin >> t_age;
    
    Reader reader(t_name, t_age);
    reader.save();
}

bool Reader::save()
{
    //get id
    AI ai(filename);
    id = ai.get_id();
    
    //open file for std::ios::app
    std::ofstream infile(fn,std::ios::app);
    
    //write data
    infile << id << " " << name << " " << age << std::endl;
    
    //close file
    infile.close();
    
    return true;
}

std::vector<Reader> Reader::findById(int f_id, int status)
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
std::vector<Reader> Reader::find(std::string text, int field, int status)
{
    std::vector<Reader> allReaders = Reader::findAll();
    std::vector<Reader> foundedReaders;

    if(!allReaders.empty())
    {
        auto fnd = std::find_if(allReaders.begin(), allReaders.end(), [text](Reader & reader)->bool{
                return reader.name.find(text)!=std::string::npos;});
        if(fnd != allReaders.end())
        {
            foundedReaders.push_back(*fnd);
        }
    }
    
    if(foundedReaders.size() == 0)
    {
        Reader emptyReader;
        foundedReaders.push_back(emptyReader);
    }
    
    return foundedReaders;
}

std::vector<Reader> Reader::findAll(int whereis)
{
    std::ifstream file(fn,std::ios::app);
    std::vector<Reader> rv;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Reader reader;
            file >> reader.id >> reader.name >> reader.age;
            rv.push_back(reader);
        }
    }
    file.close(); 
    
    return rv;
}

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
                Reader r;
                std::vector<Reader> rdr = r.find(piece, 1); //<-
                std::vector<Reader>::iterator it = rdr.begin();
                while(it != rdr.end())
                {
                    std::cout << it->id << " " << it->name << " " << it->age << std::endl;
                    ++it;
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
            
            case 0:
            default:
                ever = 0;
        }
    }
}
