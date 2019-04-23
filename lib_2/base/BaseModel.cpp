class BaseModel
{
public:
    std::string dataDir = "../data/";
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
    
    void setFileName(std::string _filename)
    {
        filename = _filename;
    }

    void setAutoincrement()
    {
        AI ai(filename);
        autoincrement = ai.get_id();
    }
    
    //BaseModel() = delete; // model must be initializes by filename
    BaseModel(std::string _fn, bool _ithAI = true) : filename(_fn) 
    {
        if(withAI) setAutoincrement();
    }
    
    virtual void save();
    virtual void update();
    virtual void del();
    
    virtual std::vector<BaseModel> find();
    virtual std::vector<BaseModel> findById();
    virtual std::vector<BaseModel> findAll();

    //ToDo: find by field - make array from fields of struct, make enum list
    //find using emun field returning number of value we need in struct 
    //fields list 




};
