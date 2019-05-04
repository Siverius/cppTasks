#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct Sent
{
    int num;
    std::string filename;
    std::string sent;
    
    Sent(){}
    Sent(int _num, std::string _filename, std::string _sent)
    {
        num = _num;
        filename = _filename;
        sent = _sent;
    }
    
    std::string getSlug()
    {
        return "Sent#" + std::to_string(num); 
    }
};

int main(int argc, char* argv[])
{
    std::string folder;

    folder = (argc > 1) ? argv[1] : "in/";

    if(!fs::exists(fs::status(folder))) 
    {
        std::cout << "directory doesn`t exist";
        return 0;
    }

    for(auto it = fs::directory_iterator(folder); it != fs::directory_iterator(); ++it)
    {
        if(fs::is_regular_file(fs::status(it->path())))
        {
            std::ifstream ifs(fs::absolute(it->path()));
            if(!ifs.is_open())
            {
                std::cout << "Cant`t open file " << fs::absolute(it->path()) << std::endl;
            }
            
            std::string line;
            std::getline(ifs, line, '.');
            std::cout << line << std::endl;
            //std::vector<Sent> sent_v;
            //sent_v.push_back();
            //получить данные из файла, собрать вектор предложений
            //в цикле пройтись по вектору, собрать вектор мапов данных
            //multimap ??? Круто будет искать данные!!
            //записать в файл
            
            //std::cout << fs::absolute(it->path()) << std::endl;
        }
    }
}
