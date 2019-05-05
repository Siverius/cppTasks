#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{    
    std::string file = (argc > 1) ? argv[1] : "out/indexed.txt";
    
    if(file == "-h" || file == "-help")
    {
        std::cout << "Usage: Searcher [data_file]" << std::endl << std::endl;
        std::cout << "If `data_file` is not determined file `indexed.txt` in the directory `out/` will be used " << std::endl << std::endl;
        std::cout << "It must be an absolute path to data file if determined" << std::endl << std::endl;
        exit(0);
    }
    std::ifstream ifs(file);
    if(!ifs.is_open())
    {
        std::cout << "Can`t open data file" << std::endl;
    }
    
    std::string needle;
    std::string haystack;
    std::cout << "Input word:" << std::endl;
    std::cin >> needle;
    std::cout << std::endl;
    
    int print = 0;
    std::string tabs = "";
    
    while(getline(ifs, haystack))
    {
        if(needle == haystack) print = 1;
        
        if(!print) continue;
        if("filename" == haystack)
        {
            tabs = "\t";
            continue;
        }
        
        std::cout << tabs << haystack << std::endl;
        
        if("\t" == tabs)
        {
            tabs += "\t";
        }
        
        if(haystack.empty()) break;
    }
    
}
