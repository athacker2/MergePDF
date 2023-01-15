#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

// MACROS
#define _R 0x2052

// Function declarations
void print_file(std::string);
std::fstream open_file(std::string);
std::unordered_map<int, std::string> parse_objs(std::fstream&);


int main(int argc, char** argv) {
    if(argc != 3) {
        std::cout<<"Pass in two file names"<<std::endl;
        return -1;
    }

    // Open files
    std::fstream file_one = open_file(argv[1]);

    // Parse Objects in file
    std::unordered_map<int, std::string> obj_map = parse_objs(file_one);

    std::cout<<"There are "<<obj_map.size()<<" objects."<<std::endl;


    // Close files
    file_one.close();
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

std::unordered_map<int, std::string> parse_objs(std::fstream& pdf_file) {
    std::unordered_map<int, std::string> obj_map;

    std::string file_line;
    while(std::getline(pdf_file, file_line)) {
        if(file_line.find("obj") != std::string::npos) { // Found an object
            std::string line_segment;
            std::istringstream file_line_stream(file_line);
            
            std::getline(std::istringstream(file_line), line_segment, ' ');
            int obj_num = std::stoi(line_segment);

            
            std::string obj_contents;
            while(std::getline(pdf_file, file_line)) { // Extract until end of object
                if(file_line == "endobj") {
                    break;
                }
                obj_contents += file_line + '\n';
            }

            // Store object in map
            obj_map[obj_num] = obj_contents;
            std::cout<<obj_num<<std::endl<<obj_contents;
        }
    }

    return obj_map;
}