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

class AI //not real AI
{
public:
    std::string dataDirectory = "data/";
    std::string ext = ".txt";
    
    
    std::string fullName;
    std::ofstream ofs;
    std::ifstream ifs;
    
    int autoincrement = 1;
    
    AI(std::string fileName)
    {
        fullName = dataDirectory + fileName + "_ai" + ext;
        //check if file exists
        //if not - create it
        //if exists - open for reading, get value, close and open for writing
        
        std::ifstream dataFile(fullName);//open to read
        if(!dataFile.is_open()) //if can`t open to read (not exist)
        {
            std::ofstream dataFile(fullName); //open to write
            if(!dataFile.is_open()) //if can`t open to write
            {
                std::cout << "Something is wrong (Model.cpp::Model())" << std::endl;
            } else { //if opened to write - write
                dataFile << autoincrement << std::endl;
                dataFile.close(); //close file
            }
        }
        else // file is opened to read
        {
            //read in val autoincrement value
            dataFile >> autoincrement;
            //close file
            dataFile.close();
            //open to write
            std::ofstream dataFile(fullName);
            //output ai in file
            dataFile << ++autoincrement;
            //close file
            dataFile.close();
            //scream!!! For every book it will open file one more time.
        }
    }
    
    int openFileToRead(std::string * filename)
    {
        std::ifstream ifs(*filename, std::ios::in);
        if(!ifs.is_open()) return 0;
        return 1;        
    }
    
    int createFile(std::string * filename)
    {
        std::ofstream ofs(*filename, std::ios::out);
        if(!ofs.is_open()) return 0;
        return 1;
    }
    
    //during main file saving we will rewrite file with autoincrement
    int openFileToWrite(std::string * filename)
    {
        std::ofstream ofs(*filename, std::ios::out);
        if(!ofs.is_open()) return 0;
        return 1;
    }
    
    void increment_it()
    {
        std::ifstream inDataFile(fullName);
        inDataFile >> autoincrement;
        inDataFile.close();
        
        std::ofstream outDataFile(fullName);
        outDataFile << ++autoincrement;
        outDataFile.close();
    }
    
    int get_id()
    {
        int id = autoincrement;
        increment_it();
        return id;
    }
    
    ~AI()
    {
        if(ifs.is_open()) ifs.close();
        if(ofs.is_open()) ofs.close();
    }
};
