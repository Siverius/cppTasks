#include <iostream>
#include <string>
#include <fstream>
#include <map>

//get tablename
//connect to "data/_service.txt"
//make map from it`s data
//return int (last number)
//if int is user - increment it in file
//close file after save main .txt file

class _Service
{
    std::string file = "data/_service.txt";
    std::fstream fs;
    std::map<std::string, int> data;
    
    _Service()
    {
        openFile();
    }
    
    void openFile()
    {
        this->fs.open(this->file);
        if(!this->fs.is_open())
        {
            std::cout << "We have problems with the _service file opening" << std::endl;
        }
    }
    
    void closeFile()
    {
        if(this->fs.is_open())
        {
            this->fs.close();
        }
    }
    
    void setData()
    {
        while (!this->fs.eof())
        {
            this->fs >> Tuple tuple;
            this->data.insert(tuple); 
        }
    }
    
    int getCounter(std::string key)
    {
        std::map<std::string, int>::iterator it;
        it = this->data.find(key);
        if(it == this->data.end()) {
            std::cout << "I can`t read data!!";
            return 0;
        } 
        
        return it->second;
    }
    
    ~_Service()
    {
        closeFile();
    }
public:
    class Tuple
    {
    public:
        std::string name;
        int counter;
        Tuple(std::string n, int c)
        {
            this->name = n;
            this->counter = c;
        }
        std::pair<std::string, int> pair()
        {
            return std::pair<std::string, int>(this->name, this->counter);
        }
    };
    
};

std::fstream& operator >>(std::fstream & in, _Service::Tuple & t)
{
    in >> t.name >> t.counter;
    return in;
}

int main()
{

}
