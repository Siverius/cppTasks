#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "_Reader.cpp"

class Inventory
{
    std::string dataDir = "data/";
    std::string filename = "inventory";
    std::string ext = ".txt";
    
    std::string fn = dataDir + filename + ext;
public:
    int reader_id;
    int book_id;
    int delivered = 0;
    
    Reader(int r, int b): reader_id(r), book_id(b) { }
    Reader(){}

    void insert();
    bool save();  
    //template?  Maybe map <field_name: value>?
    std::vector<Inventory> find(int _id, int field);
    std::vector<Inventory> findAll(int whereis = 0);
    void update();
    void del();
};


void Inventory::insert()
{
    std::cout << "\t Insert name of reader(string): ";
    std::string t_name;
    std::cin >> t_name;
    
    std::cout << "\t Insert readers age (int): ";
    int t_age;
    std::cin >> t_age;
    
    Inventory inventory(t_name, t_age);
    reader.save();
}

bool Inventory::save()
{
    //get id
    AI ai(filename);
    id = ai.get_id();
    
    //open file for std::ios::app
    std::ofstream infile(fn,std::ios::app);
    
    //write data
    infile << id << " " << name << " " << age << std::endl;
    
    //close file
    infile.close();
    
    return true;
}

//ToDo: redo using template
std::vector<Inventory> Inventory::find(int value, int field)
{
    std::vector<Inventory> allRecords = Inventory::findAll();
    std::vector<Inventory> foundedInventory;

    if(!allRecords.empty())
    {
        if(field == 1) {
            auto fnd = std::find_if(allRecords.begin(), allRecords.end(), [value](Inventory & inventory)->bool{
                    return inventory.reader_id == value;
                });
        }
        if(field == 2) {
            auto fnd = std::find_if(allRecords.begin(), allRecords.end(), [value](Inventory & inventory)->bool{
                    return inventory.book_id == value;
                });
        }
        if(fnd != allRecords.end())
        {
            foundedInventory.push_back(*fnd);
        }
    }
    
    if(foundedInventory.size() == 0)
    {
        Inventory emptyInventory;
        foundedInventory.push_back(emptyInventory);
    }
    
    return foundedInventory;
}

std::vector<Inventory> Inventory::findAll(int whereis)
{
    std::ifstream file(fn,std::ios::app);
    std::vector<Inventory> allRecords;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Inventory inventory;
            file >> inventory.reader_id >> inventory.book_id >> inventory.delivered;
            allRecords.push_back(inventory);
        }
    }
    file.close(); 
    
    return allRecords;
}

//controller?
void InventoryMenu()
{
    int ever = 1;
    int choice;
    Inventory inventory;
    while(ever)
    {
        std::cout << "Select something:" << std::endl;
        std::cout << "1. Give Book to Reader" << std::endl;
        std::cout << "2. Take Book from Reader" << std::endl;
        std::cout << "3. Show all Books Reader have" << std::endl;
        std::cout << "0. Exit " << std::endl;
        
        std::cin >> choice;
        
        switch(choice)
        {
            case 1:
            {
                std::string r_name;
                std::cout << "Inser reader name" << std::endl;
                std::cin >> r_name;
                std::vector<Reader> rdr.find(r_name);
                //find reader
                //take his id
                
                
                //find book
                //set it into vector
                //create row in table inventory
                //change book status
            }
                break;
            case 2:
            {
                //find reader
                //take his id
                //show books he had
                //get back book by id (change book status, delete row in inventory)
                //show the rest of books reader has
            }
                break;
            case 3:
            {
                //find reader
                //take his id
                //show all books he had 
            }
                break;            
            case 0:
            default:
                ever = 0;
        }
    }
}
