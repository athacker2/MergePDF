#include <iostream>
#include <fstream>

// MACROS
#define _R 0x2052

// Functional declarations
void print_file(std::string);
std::fstream open_file(std::string);

int main(int argc, char** argv) {
    if(argc != 3) {
        std::cout<<"Pass in two file names"<<std::endl;
        return -1;
    }

    // Open files
    std::fstream file_one = open_file(argv[1]);

    std::fstream merged_file = open_file("merged_pdf.pdf");

    // Close files
    file_one.close();
    merged_file.close();
    return 0;
}

void print_file(std::string file_name) {
    std::ifstream ifs;
    ifs.open(file_name);
    if(!ifs.is_open()) {
        std::cout<<"Failed to open file"<<std::endl;
        exit(-1);
    }

    std::string file_line;
    while(std::getline(ifs, file_line)) {

        for(auto &c : file_line)
            std::cout<<std::hex<<int(c);
        std::cout<<std::endl;
    }   
}

std::fstream open_file(std::string file_name) {
    std::fstream file;
    file.open(file_name);
    if(file.is_open()) {
        return file;
    }
    else {
        std::cerr<<"Failed to open file " + file_name<<std::endl;
        exit(-1);
    }
}