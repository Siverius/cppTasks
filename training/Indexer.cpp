#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    std::string folder_from;
    std::string folder_to;

    folder_from = (argc > 1) ? argv[1] : "in/";

    if(folder_from == "-h" || folder_from == "-help")
    {
        std::cout << "Usage: Indexer [path_from [path_to]]" << std::endl << std::endl;
        std::cout << "If `path_from` is not determined folder `in/` in the current directory will be used" << std::endl << std::endl;
        std::cout << "If `path_to` is not determined folder `out/` in the current directory will be used" << std::endl << std::endl;
        std::cout << "Each path must be an absolute path" << std::endl;
        exit(0);
    }

    if(!fs::exists(fs::status(folder_from))) 
    {
        std::cout << "directory doesn`t exist";
        return 0;
    }
    
    std::map<std::string, std::map<std::string, std::vector<std::string>>> words_pack;

    for(auto it = fs::directory_iterator(folder_from); it != fs::directory_iterator(); ++it)
    {
        if(fs::is_regular_file(fs::status(it->path())))
        {
            std::ifstream ifs(fs::absolute(it->path()));
            
            if(!ifs.is_open())
            {
                std::cout << "Cant`t open file " << fs::absolute(it->path()) << std::endl;
            }
            
            std::string filename = fs::path(it->path()).filename().string();
            std::string line;
            std::vector<std::string> sent_v;
            while(std::getline(ifs, line, '.'))
            {
                if (line.empty()) continue;

                sent_v.push_back(line + " ");
            }
            
            std::vector<std::string>::iterator it = sent_v.begin();
            int sent_counter = 0;
            while(it != sent_v.end())
            {
                std::transform(std::begin(*it), std::end(*it), std::begin(*it),
                    [](char c){ if(c == '\n' || c == '\r') return ' '; return c; });
                
                std::string sent_num = "Sent#" + std::to_string(sent_counter++);
                
                size_t offset = 0;
                size_t next = 0;
                std::string delimiter(" ");
                size_t del_length = delimiter.length();
                
                std::multimap<std::string, std::string> row_pack;
                while((next = (*it).find(delimiter, offset)) != std::string::npos)
                {
                    std::string word = (*it).substr(offset, next - offset);
                    std::string m_row = sent_num + ", offset = " + std::to_string(offset);
                    offset = next + del_length;
                    
                    if(word.empty()) continue;
                    
                    for(size_t i = 0; i < word.length(); ++i)
                    {
                        if(ispunct(word[i]))
                        {
                            word.erase(i--, 1);
                        }
                    }
                    
                    words_pack[word][filename].push_back(m_row);
                }
                
                it++;
            }
            
        }
    }
    
    folder_to = (argc > 2) ? argv[2] : "out/";
    if(!fs::exists(fs::status(folder_to))) 
    {
        std::cout << "directory for inputing data doesn`t exist";
        return 0;
    }
    if(folder_to[folder_to.size() - 1] != '/' || folder_to[folder_to.size() - 1] != '\\')
    {
        folder_to += "\\";
    }
    
    std::ofstream ofs(folder_to + "indexed.txt");

    if(!ofs.is_open())
    {
        std::cout << "Cant`t open file " << folder_to + "indexed.txt" << std::endl;
    }
    
    for(const auto &word : words_pack)
    {
        ofs << word.first << std::endl;
        
        for(const auto &row : word.second)
        {
            ofs << "filename" << std::endl;
            ofs << row.first << std::endl;
            for(const auto &piece : row.second)
            {
                ofs << piece << std::endl;
            }
        }
        
        ofs << std::endl;
    }
    
    std::cout << "Something has been indexed" << std::endl;
}
