#include <iostream>
#include <string>
#include <map>
#include <fstream>

class BaseModel
{
public:
    std::map<std::string, std::string> attr; //file structure
    std::map<std::string, std::string> data; //one row (tuple) data //{attr_name: attr_type}
    void validation(); // проверка на корректность
    void save(); //сохранение
};

class FileModel : public BaseModel
{
    const char GLUE = ';';
    std::fstream _data_file;
    
    void _openFile(std::string filename)
    {
        this->_data_file.open(filename, std::ios::app);

        if(!this->_data_file) 
        {
           std::cout << "Can`t open file " << filename << std::endl;
           exit(-1);
        }
    }
    
    void _makeRow()
    {
        for(auto piece : this->data)
        {
            auto end = FileModel::GLUE;
            this->dataRow += piece.second + end;
        }
    }
    
    void _closeFile()
    {
        if(this->_data_file.is_open())
        {
            this->_data_file.close();
        }
    }
public:
    std::string file; //relative path to file
    std::string dataRow = ""; //will be inserted in db-file
    std::fstream fileStream; 
    
    auto fileStreamOpen()
    {
        return this->_openFile(this->file);
    }
    
    auto fileStreamClose()
    {
        return this->_closeFile();
    }
    
    void save()
    {
        this->fileStreamOpen();
        
        this->_makeRow();
        
        this->_data_file << this->dataRow;
        this->_data_file << std::endl;
        
        this->fileStreamClose();
    }
};
class BookModel : public FileModel
{
    
public:
    const std::string WHEREIS_LIB = "lib";
    const std::string WHEREIS_RDR = "rdr";
    
    const std::string STATUS_DEL = "del";
    const std::string STATUS_ACTIVE = "act";
    
    void setSource()
    {
        this->file = "../db/books.txt";
    }
    
    BookModel () {
        this->setSource();
        attr.insert(std::pair<std::string,std::string>("name", "string"));
        attr.insert(std::pair<std::string,std::string>("author", "string"));
        attr.insert(std::pair<std::string,std::string>("whereis", "int")); //0 - lib, 1 - reader
        attr.insert(std::pair<std::string,std::string>("status", "int")); //0 - deleted, 1 - active
        
        data.insert(std::pair<std::string,std::string>("name", "string"));
        data.insert(std::pair<std::string,std::string>("author", "string"));
        data.insert(std::pair<std::string,std::string>("whereis", BookModel::WHEREIS_LIB)); //0 - lib, 1 - reader
        data.insert(std::pair<std::string,std::string>("status", BookModel::STATUS_ACTIVE)); //0 - deleted, 1 - active
    }
};
/*
class ReaderModel : public FileModel
{
public:    
    const int STATUS_DEL = 0;
    const int STATUS_ACTIVE = 1;
    
    void setSource()
    {
        this->file = "../db/readers.txt";
    }
    ReaderModel () {
        attr.insert(std::pair<std::string,std::string>("name", "string"));
        attr.insert(std::pair<std::string,std::string>("status", "int")); //0 - deleted, 1 - active
    }
};
* */
int main()
{
    BookModel fm;
    //fm.whereis{5};
    fm.save();
    
    std::cout << "---------------------------------------" << std::endl;
    
    //ReaderModel reader;
    //reader.save();
    
    std::cout << "---------------------------------------" << std::endl;
    
    return 0;
}
