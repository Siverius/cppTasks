class Reader 
{
public:
    std::string name;
    int age;
    Reader(std::string n, int a): name(n), age(a) { }
    Reader(){ }
};

std::ofstream& operator << (std::ofstream &os, const Reader &r)
{
    os << r.name << " " << r.age;
    return os;
}
std::istream& operator >> (std::istream& in, Reader& r)
{
    in >> r.name >> r.age;
    return in;
}


void fillReaders(std::vector<Reader> * reader);
void saveReaders(std::vector<Reader> * reader);
void ReaderMenu()
{
    const int EVER = 1;
    const int OUT = 0;
    
    int iter = EVER;
        
    std::vector<Reader> readers;
    
    while(iter)
    {
        int choice = 3;
        std::cout << "Insert number of your choice please: " << std::endl;
        std::cout << "1. Add reader " << std::endl;
        std::cout << "2. Save inserted readers and exit " << std::endl;
        std::cout << "3. test " << std::endl;
        std::cout << "0. Drop inserted data and exit " << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                fillReaders(&readers);
                break;
            }
            case 2:
            {
                saveReaders(&readers);
                iter = OUT;
                break;
            }
            case 3:
                //test();
                break;
            case 4:
            default:
                iter = OUT;
        }
    }
}

void fillReaders(std::vector<Reader> * reader)
{
    std::cout << "\t Insert name (string): ";
    std::string t_name;
    std::cin >> t_name;
    std::cout << "\t Insert age (int): ";
    int t_age;
    std::cin >> t_age;
    Reader r(t_name, t_age);
    reader->push_back(r);
}

void saveReaders(std::vector<Reader> * reader)
{
    std::ofstream out("data/readers.txt");
    if (out.is_open())
    {
        auto iter = reader->begin();
        while(iter!=reader->end())
        {
            out << *iter << std::endl;// получаем элементы через итератор
            ++iter;             // перемещаемся вперед на один элемент
        }
    }
    out.close();
}

std::vector<Reader> getReadersVector()
{
    std::ifstream in("data/readers.txt");
    std::vector<Reader> rv;
    if (in.is_open())
    {
        std::string name;
        int age;
        while (in >> name >> age)
        {
            rv.push_back(Reader(name, age));
        }
    }
    in.close();
    
    return rv;
}
