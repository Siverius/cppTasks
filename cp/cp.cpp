#include <iostream>
#include <fstream>

int main(int argc, char * argv[])
{
    if(argc < 3) {
        std::cerr << "Incorrect args";
        return 1;
    }
    std::ifstream in_file(argv[1],std::ios::binary);
    if(!in_file) {
        std::cerr << "Wrong input file";
        return 1;
    }
    std::ofstream out_file(argv[2],std::ios::binary);
    if(!out_file) {
        std::cerr << "Wrong output file";
        return 1;
    }
    
    const int max_buffer_size = 80;
    char buffer[max_buffer_size] = {};
    
    in_file.seekg(0,std::ios::end); 
    int file_size = in_file.tellg();
    in_file.seekg(0,std::ios::beg);
    
    while(!in_file.eof())
    {        
        in_file.read(buffer, max_buffer_size);
        int buffer_size = (file_size >= buffer_size) ? 
                                            max_buffer_size : file_size;
        out_file.write(buffer, buffer_size);
        
        file_size -= buffer_size;
    }
    
    in_file.close();
    out_file.close();
    return 0;
}
