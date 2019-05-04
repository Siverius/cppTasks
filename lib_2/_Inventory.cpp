class Inventory : public BaseModel
{
public:
    enum statuses {CLOSED, ACTIVE, ALL};

    int id;
    int reader_id;
    int book_id;
    int delivered = ACTIVE;
    
    Inventory(int r, int b, int delivered = ACTIVE) : BaseModel("inventory") { }
    Inventory() : BaseModel("inventory") {}

    void insert();
    bool save();  
    //template?  Maybe map <field_name: value>?
    std::vector<Inventory> find(int id, int field);
    std::vector<Inventory> findById(int id, int field);
    std::vector<Inventory> findAll(int status = 0);
    void update(int id);
    void del(int id);
    int anotherStatus();
};


void Inventory::insert()
{    
    return;
}

bool Inventory::save()
{    
    //set id
    setAutoincrement();
    id = autoincrement;
    
    //open file for std::ios::app
    std::ofstream infile(getFilepath(),std::ios::app);
    if(infile.is_open()) {
        //write data
        infile << id << " " << reader_id << " " << book_id << std::endl;
        
        //close file
        infile.close();
    }
    else
    {
        echo("file was not open");
    }   
    return true;
}

//ToDo: redo using template
std::vector<Inventory> Inventory::find(int value, int field)
{
    std::vector<Inventory> allRecords = Inventory::findAll();
    std::vector<Inventory> foundedInventory;

    if(!allRecords.empty())
    {
        std::vector<Inventory>::iterator fnd;
        if(field == 1)//ToDo: enum list
        {
            fnd = std::find_if(allRecords.begin(), allRecords.end(), [value](Inventory & inventory)->bool{
                    return inventory.reader_id == value;
                });
        }
        else if(field == 2)
        {
            fnd = std::find_if(allRecords.begin(), allRecords.end(), [value](Inventory & inventory)->bool{
                    return inventory.book_id == value;
                });
        }
        else
        {
            fnd = allRecords.end();
        }
        if(fnd != allRecords.end())
        {
            foundedInventory.push_back(*fnd);
        }
    }
    
    if(foundedInventory.size() == 0) throw -1;
    
    return foundedInventory;
}

std::vector<Inventory> Inventory::findAll(int whereis)
{
    std::ifstream file(getFilepath(),std::ios::app);
    std::vector<Inventory> rv;
    if (file.is_open())
    {
        while(!file.eof())
        {
            Inventory inventory;
            file >> inventory.reader_id >> inventory.book_id >> inventory.delivered;
            if((whereis == ALL || inventory.delivered == whereis) && !file.eof()){
                rv.push_back(inventory);
            }
        }
    }
    file.close(); 
    
    return rv;
}

int Inventory::anotherStatus()
{
    return delivered == ACTIVE ? CLOSED : ACTIVE;
}

void Inventory::update(int id)
{
    std::vector<Inventory> all = findAll(ALL);
    std::vector<Inventory>::iterator temp = std::find_if(all.begin(), all.end(), \
        [id](Inventory & inventory)->bool{
                return inventory.id == id;
            }
    );
    if(temp != all.end())
    {    
        //std::vector<Book>::iterator to_upd = temp;
        
        //rewrite file 
        std::ofstream input(getFilepath());
        if(input.is_open())
        {
            input << temp->id << " " \
                  << temp->reader_id << " " \
                  << temp->book_id << " " \
                  << temp->anotherStatus() << std::endl;
            
            all.erase(temp);

            std::vector<Inventory>::iterator iter = all.begin();
            while(iter != all.end())
            {
                input << iter->id << " " \
                  << iter->reader_id << " " \
                  << iter->book_id << " " \
                  << iter->delivered << std::endl;
                iter++;
            }

            input.close();  
        }     
    }
    
    return;
}

void Inventory::del(int id)
{
    std::vector<Inventory> all = findAll();
    std::vector<Inventory>::iterator to_del = std::find_if(all.begin(), all.end(), \
        [id](Inventory & inventory)->bool{
                return inventory.id == id;
            }
    );
    if(to_del != all.end())
    {
        all.erase(to_del);
    }
    
    //rewrite file 
    std::ofstream input(getFilepath());
    if(input.is_open())
    {
        std::vector<Inventory>::iterator iter = all.begin();
        while(iter != all.end())
        {
            input << iter->id << " " \
                << iter->reader_id << " " \
                << iter->book_id << " " \
                << iter->delivered << std::endl;
                iter++;
        }
        input.close(); 
    }
    return;
}

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
            case 1: //Give Book to Reader
            {
                std::string r_name;
                std::cout << "Insert reader name" << std::endl;
                std::cin >> r_name;
                try
                {
                    Reader r;
                    std::vector<Reader> rdr = r.find(r_name, 1);
                    std::vector<Reader>::iterator r_it = rdr.begin();
                    while(r_it != rdr.end())
                    {
                        std::cout << r_it->id << " " << r_it->name << " " << r_it->age << std::endl;
                        ++r_it;
                    }
                    std::cout << "Insert Readers ID or type 0 to go back" << std::endl;
                    int rdr_id;
                    std::cin >> rdr_id;
                    
                    if(rdr_id == 0)
                    {
                        choice = 0;
                    }
                    
                    //проверка существования читателя
                    std::vector<Reader> rdr_if = r.findById(rdr_id);
                    if(rdr_if.size() == 0) throw -1;
                    
                    
                    std::vector<Book> bookPack;
                    
                    int ever_2 = 1;
                    while(ever_2)
                    {
                        std::cout << "Select something:" << std::endl;
                        std::cout << "1. Find Book (by name)" << std::endl;
                        std::cout << "2. Add Book" << std::endl;
                        std::cout << "3. Give Books to Reader" << std::endl;
                        std::cout << "0. Exit" << std::endl;
                        
                        int choise_2;
                        std::cin >> choise_2;
                        
                        switch(choise_2)
                        {
                            case 1:
                            {
                                std::string piece;
                                std::cout << "Insert Book name" << std::endl;
                                std::cin >> piece;
                                Book book;
                                std::vector<Book> bks = book.find(piece, 1); //<-
                                std::vector<Book>::iterator it = bks.begin();
                                while(it != bks.end())
                                {
                                    std::cout << it->id << " " << it->name << " " << it->author << std::endl;
                                    ++it;
                                }
                            }
                                break;
                            case 2:
                            {
                                //ask for book id
                                //find book by id
                                //push it back to vector
                                int b_id;
                                std::cout << "Insert Book id: ";
                                std::cin >> b_id;
                                
                                Book book;
                                auto fnd = book.findById(b_id);
                                
                                if(fnd.begin() == fnd.end()) throw -1;

                                bookPack.push_back(*fnd.begin());
                             }
                                break;
                            case 3: 
                            {
                                //if vector is not empty
                                //insert in cicle rows in inventory
                                //change status to every book
                                if(bookPack.size() == 0) throw -1;
                                std::vector<Book>::iterator biter = bookPack.begin();
                                while(biter != bookPack.end())
                                {
                                    Inventory inv;
                                    inv.reader_id = rdr_id;
                                    inv.book_id = biter->id;
                                    inv.save();
                                    
                                    //find book by id
                                    //change its status
                                    //be happy
                                    Book bk;
                                    auto fnd_bk = bk.findById(biter->id);
                                    std::vector<Book>::iterator some_name = fnd_bk.begin();
                                    some_name->anotherStatus();
                                    some_name->save();
                                    //I hope it works
                                    
                                    biter++;
                                }
                            }
                                break;
                            default: 
                                ever_2 = 0;
                        }
                        
                    }
                } 
                catch (int i)
                {
                    std::cout << "No readers has been founded" << std::endl;
                }
            }
                break;
            case 2:
            {
                //find reader
                //take his id
                //show books he had
                std::string r_name;
                std::cout << "Insert reader name" << std::endl;
                std::cin >> r_name;
                Reader r;
                std::vector<Reader> rdr = r.find(r_name, 1);
                std::vector<Reader>::iterator r_it = rdr.begin();
                while(r_it != rdr.end())
                {
                    std::cout << r_it->id << " " << r_it->name << " " << r_it->age << std::endl;
                    ++r_it;
                }
                std::cout << "Insert Readers ID or type 0 to go back" << std::endl;
                int rdr_id;
                std::cin >> rdr_id;
                
                if(rdr_id == 0)
                {
                    choice = 0;
                }
                
                //проверка существования читателя
                std::vector<Reader> rdr_if = r.findById(rdr_id);
                if(rdr_if.size() == 0) throw -1;
                Inventory inv;
                std::vector<Inventory> bp = inv.find(rdr_id, 1);
                
                std::vector<Inventory>::iterator bp_iter = bp.begin();
                while(bp_iter != bp.end())
                {
                    int book_id = bp_iter->book_id;
                    //we have book id. Let find book and show it
                    Book book; //yes, it`s very stupid code, I know((
                    auto book_vector = book.findById(book_id);
                    auto book_object = book_vector.begin();
                    std::cout << book_object->id << " " << book_object->name << " " << book_object->author << std::endl;
                    
                    bp_iter++;
                }
                //ask for inventory id
                std::cout << "Insert Inventory ID!" << std::endl;
                int inv_id;
                std::cin >> inv_id;
                
                //find row
                
                
                
                //del(inv_id);
                //delete row in inventory
                
                
                //book.anotherStatus()

            }
                break;
            case 3:
            {
                //find reader
                //take his id
                std::string r_name;
                std::cout << "Insert reader name" << std::endl;
                std::cin >> r_name;
                Reader r;
                std::vector<Reader> rdr = r.find(r_name, 1);
                std::vector<Reader>::iterator r_it = rdr.begin();
                while(r_it != rdr.end())
                {
                    std::cout << r_it->id << " " << r_it->name << " " << r_it->age << std::endl;
                    ++r_it;
                }
                std::cout << "Insert Readers ID or type 0 to go back" << std::endl;
                int rdr_id;
                std::cin >> rdr_id;
                
                if(rdr_id == 0)
                {
                    choice = 0;
                }
                
                //проверка существования читателя
                std::vector<Reader> rdr_if = r.findById(rdr_id);
                if(rdr_if.size() == 0) throw -1;
                
                Inventory inv;
                std::vector<Inventory> bp = inv.find(rdr_id, 1);
                
                std::vector<Inventory>::iterator bp_iter = bp.begin();
                while(bp_iter != bp.end())
                {
                    int book_id = bp_iter->book_id;
                    //we have book id. Let find book and show it
                    Book book; //yes, it`s very stupid code, I know((
                    auto book_vector = book.findById(book_id);
                    auto book_object = book_vector.begin();
                    std::cout << book_object->id << " " << book_object->name << " " << book_object->author << std::endl;
                    
                    bp_iter++;
                }
            }
                break;            
            case 0:
            default:
                ever = 0;
        }
    }
}
