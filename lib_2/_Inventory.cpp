#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
//#include "AI.cpp"

class Inventory
{
    std::string dataDir = "data/";
    std::string filename = "inventory";
    std::string ext = ".txt";
    
    std::string fn = dataDir + filename + ext;
public:
    int reader_id;
    int book_id;
    
    Reader(int r, int b): reader(r), book_id(b) { }
    Reader(){}

    void insert();
    bool save();  
    //template?  
    std::vector<Inventory> find(int _id, int field);
    std::vector<Inventory> findById(int f_id, int whereis = 0);
    std::vector<Inventory> findAll(int whereis = 0);
    void update();
    void del();
};
