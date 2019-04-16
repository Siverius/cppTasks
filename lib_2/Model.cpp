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

class Model
{
public:
    std::string dataDirectory = "data/";
    std::string fileName = "book";
    std::string ext = ".txt";
    
    
    std::string fullName;
    std::fstream fs;
    
    Model()
    {
        fullName = dataDirectory + fileName + ext;
    }
    
    void openFile()
    {
        std::cout << " << " << fullName << " >> " << std::endl;
        std::fstream fs(fullName, std::ios::in | std::ios::out | std::ios::ate);
        if(!fs.is_open())
        {
            std::cout << "We have problems with the service file opening" << std::endl;
            return;
        }
    }
    
    void closeFile()
    {
        if(this->fs.is_open())
        {
            this->fs.close();
        }
    }
    
    void setData(int value = 1)
    {
        this->fs << value;
        //записать инкрементированное значение
    }
    
    
    int getData()
    {
        int out;
        this->fs >> out;
        return out;
        //получить значение, если нет - 1
    }
    
    ~Model()
    {
        closeFile();
    }
};

int main()
{
    Model model;
    model.openFile();
    
    model.setData();
    std::cout << model.fullName << std::endl;
    model.closeFile();
}
