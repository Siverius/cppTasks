#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

class FileStructor
{
    std::fstream file;
    std::map<std::string, std::string> * tmpl;
    const char DELIMITER = ';';
    
    FileStructor() = delete;
    FileStructor(std::string filename, std::map<std::string, std::string> * tmpl)
    {
        //открыть файл
        this->file.open(filename, std::ios::in);
        if(!this->file)
        {
            std::cout << "Wrong file: " << filename << std::endl;
        }
        this->tmpl = tmpl;
    }
    
    void execute()
    {
        std::string tuple; // - считанная из файла строка
        
        while(getline(this->file, tuple))
        {
            std::istringstream iss(tuple);
            auto map_tmpl = this->tmpl;
            std::vector<std::string> v_tmp;
            for(std::string piece; std::getline(iss, piece, FileStructor::DELIMITER); )
            {
                v_tmp.push_back(piece);
                //создадим вектор
                //затем в цикле переберём мап. передадим в секонд значения из вектора
            }
            int i = 0;
            for(std::map<std::string, std::string>::iterator it = map_tmpl->begin(); \
                it!=map_tmpl->end(); \
                ++it)
            {
                map_tmpl.at(*(map_tmpl->first)) = v_tmp[i];
                ++i;
            }
        }
        
        
        std::string datafile;
        int id;
        
        while(getline(hlp, row)) {
            istringstream s(row);
            std::string temp_name;
            int id;
            s >> temp_name;
            if (temp_name == this->filename)
            {
                s >> id;
                return id;
            }
            //найти строку с названием файла, куда пишем
            //взять id, переписать его на инкрементированный
        }
        //прочитать строку
        //разобрать по delimiter
        //создать map из ntmplate
        //заполнить map
        //добавить map в вектор
        
        //вернуть вектор
    }
    ~FileStructor()
    {
        //закрыть файл если открыт
    }
};

class BaseModel
{
public:
    std::map<std::string, std::string> data;
    void save();
};

class FileModel : public BaseModel
{
    const char GLUE = ' '; //don`t change it or Baba Yaga will come to you
    const std::string _data_dir = "../db/";
    const std::string _data_ext = ".txt";
    const std::string _helper = ".helper";
    std::string _data_row;
    std::fstream _data_file;
    std::fstream _helper_file;
    
    void _openFile()
    {
        std::string fn = this->_data_dir + \
                         this->filename + \
                         this->_data_ext;
                         
        this->_data_file.open(fn, std::ios::app);
     
        if(!(this->_data_file)) 
        {
            this->_closeFile();
            std::cout << "Can`t open file " << fn << std::endl;
            exit(-1);
        }
    }
    
    void _makeRow()
    {
        std::string temp = "";
        for(auto piece : this->data)
        { 
            temp += piece.second + FileModel::GLUE;
        }
        this->_data_row = temp;
    }

    void _closeFile()
    {
        if(this->_data_file.is_open())
        {
            this->_data_file.close();
        }
    }
    
    int _getNewId()
    {
        //открыть файл helper
        std::string hlp = this->_data_dir + \
                          this->_helper;
        this->_helper_file.open(hlp, std::ios::ate);
        
        if(!this->_helper_file)
        {
            std::cout << "Can`t oper helper file" << std::endl;
            exit(-1);
        }
        
        std::string row;
        std::string datafile;
        int id;
        
        while(getline(hlp, row)) {
            istringstream s(row);
            std::string temp_name;
            int id;
            s >> temp_name;
            if (temp_name == this->filename)
            {
                s >> id;
                return id;
            }
            //найти строку с названием файла, куда пишем
            //взять id, переписать его на инкрементированный
        }
        //закрыть helper
        //вернуть id
        return 0;
    }
    
public:
    std::string filename;
    std::fstream fileStream;
    
    auto fileStreamOpen()
    {
        return this->_openFile();
    }
    
    auto fileStreamClose()
    {
        return this->_closeFile();
    }
    
    void save()
    {
        this->fileStreamOpen();
        this->_makeRow();
        this->_data_file << this->_data_row;
        this->_data_file << this->_getNewId();
        this->_data_file << std::endl;
        
        this->fileStreamClose();        
    }
};
class BookModel : public FileModel
{
    const std::string WHEREIS_LIB = "lib";
    const std::string WHEREIS_RDR = "rdr";

    void _setSource()
    {
        this->filename = "books";
    }

public:
    BookModel () {
        this->_setSource();
        this->data = {
                {"name", ""},
                {"author", ""},
                {"whereis", WHEREIS_LIB}, //default values
           };
    }
    
    void setName(std::string name)
    {
        this->data.at("name") = name;
    }
    
    void setAuthor(std::string author)
    {
        this->data.at("author") = author;
    }
    
    void changeWhereis()
    {
        this->data.at("whereis") = (this->data["whereis"] == BookModel::WHEREIS_LIB) ? \
            BookModel::WHEREIS_RDR : \
            BookModel::WHEREIS_LIB;
    }
};
int main()
{
    //books
        //insert book
        //find book
        //findAll books
    //readers
        //insert reader
        //find reader
        //findAll readers
    //work
        //find reader
            //find another reader
            //give him book
                //find book
            //show books he take
                //take back book
    
    BookModel fm;
    fm.setName("test_name");
    fm.setAuthor("test_author_");
    fm.save();
    
    return 0;
}
