#include <string>

template<typename T>
void echo(T val)
{
    std::cout << val << std::endl;
}

class BaseModel
{
public:
    std::string dataDir = "data/";
    std::string filename;
    std::string ext = ".txt";
    
    bool withAI;
    
    int autoincrement;
    
    //struct Fields{};

    std::string getFilepath()
    {
        if(filename.length() == 0) throw -1;
        return dataDir + filename + ext;
    }

    void setAutoincrement()
    {
        AI ai(filename);
        autoincrement = ai.get_id();
    }
    
    //BaseModel() = delete; // model must be initializes by filename
    BaseModel(std::string _fn, bool _withAI = true)
    {
        filename = _fn;
        withAI = _withAI;
        if(withAI) setAutoincrement();
    }
    
    void save();
    void update();
    void del(int id);
        
    template<typename T>
    T find(std::string text, int a, int b);
    
    template<typename T>
    T findById(int a, int b);
    
    template<typename T>
    T findAll(int a);

    //ToDo: find by field - make array from fields of struct, make enum list
    //find using emun field returning number of value we need in struct 
    //fields list 
};
