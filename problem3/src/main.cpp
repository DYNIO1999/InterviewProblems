#include <iostream>
#include <string>
#include <vector>
#include <cassert>
/*
std::string readDataFromFileCFile(const std::string &path)
{
    FILE *file = fopen(path.c_str(), "r");
    if (!file)
    {
        throw std::runtime_error("Couldnt open file!");
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    char *buffer = new char[size];
    rewind(file);
    if (fread(buffer, sizeof(char), size, file) == 0)
    {
        throw std::runtime_error("Couldnt read file!");
    }
    std::string data;
    data = buffer;
    delete[] buffer;
    return data;
}
*/

std::string readDataFromFile(const std::string path){
    FILE *file = fopen(path.c_str(), "r");
    
    assert(file != nullptr &&"Cant open file!");
    
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    char *buffer = new char[size];
    rewind(file);
    if (fread(buffer, sizeof(char), size, file) == 0)
    {   
        delete[] buffer;
        assert( false && "Cant read file!");
    }
    std::string data;
    data = buffer;
    delete[] buffer;
    assert(false && "Cant read file!");
    
    return data;
}


int main(int argc, char const *argv[])
{
    std::string data = readDataFromFile("data.txt");
    return 0;
}
