
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "AI.cpp"
#include "_Reader.cpp"
#include "_Book.cpp"
#include "_Inventory.cpp"



class InventoryActions
{
    std::vector<Book> bookVector;
    Reader reader;
    
    //find book, add to booksVector
    void makeBooksVector()
    {
        std::cout << "Insert Book name: " << std::endl;
        std::string bookName;
        std::cin >> bookName;
        std::vector<Book> bookList;
        //find book
        Book book;
        std::vector<Book> findBook = book.find(bookName, 1);
        std::vector<Book>::iterator b_it = findBook.begin();
        if(b_it != findBook.end()) //some book is finded
        {
            //show book name
            std::cout << b_it->name << std::endl;
        }
        int bookAddChoice = 1;
        while(bookAddChoice)
        {
            int tmp;
            std::cout << "1. Add book to list" << std::endl;
            //std::cout << "2. Find another book" << std::endl;
            std::cout << "3. Make action (and exit)" << std::endl;
            std::cout << "0. Exit (skip)" << std::endl;
            std::cin >> tmp;
            
            switch(tmp)
            {
                case 1:
                    bookList.push_back(*b_it);
                    break;
                case 2:
                    bookAddChoice = 0;
                    break;
                case 3:
                    addBooks(bookList);
                    break;
                case 0:
                default:
                    bookAddChoice = 0;
            }
        }
    }
    
    void addBooks(std::vector<Book> bookList)
    {
        if(bookList.size() == 0) throw -1;
        std::vector<Book>::iterator it = bookList.begin();
        while(it != bookList.end())
        {
            //create row in inventory
            Inventory inventory(reader.id, it->id);
            //make book status STATUS_READER
            it->changeStatus();
        }
    }
    
    void getBackBook()
    {
        //show books reader has
        Reader reader;
        //find reader
        std::cout << "Insert Reader name" << std::endl;
        std::string name;
        std::cin >> name;
        
        std::vector<Reader> findReader = reader.find(name);
        std::vector<Reader>::iterator r_it = findReader.begin();
        if(r_it != findReader.end()) //some book is finded
        {
            //show readers id and name
            std::cout << r_it->id << " " << r_it->name << std::endl;
        }
        
        std::cout << "Insert Reader id" << std::endl;
        int reader_id;
        std::cin >> reader_id;
        readerModel = reader.findById(reader_id);
        
        //show books 
        
        
        //insert id of book
        //change book status
        //delete row in inventory 
    }
};
