#include <iostream>
#include <string>
#include <vector>
#include <cassert>

std::string readDataFromFile(const std::string path)
{
    FILE *file = fopen(path.c_str(), "r");

    assert(file != nullptr && "Cant open file!");

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    char *buffer = new char[size];
    rewind(file);
    if (fread(buffer, sizeof(char), size, file) == 0)
    {
        delete[] buffer;
        assert(false && "Cant read file!");
    }
    std::string data;
    data = buffer;
    delete[] buffer;
    return data;
}

std::string solveProblem(const std::string& data){
    std::string result = data;
    int size = result.size();
    int startIndex =0;
    int endIndex =size-1;;
    for (auto it = (result.end()-1); it != (result.begin() + startIndex);)
    {
        if(*it!=' '){
            break;
        }
        if (((*it) == ' ')){
            it = result.erase(it);
            endIndex--;
        }
        else{
            --it;
        }
    }
    for (auto it = result.begin(); it != (result.end() + endIndex);)
    {
        if (*it != ' ')
        {
            break;
        }
        if (((*it) == ' '))
        {
            it = result.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return result;
}
int main(int argc, char const *argv[])
{
    std::string data = readDataFromFile("../../src/data.txt");
    std::string result = solveProblem(data);
    std::cout<<"RESULT:\n";
    std::cout<<result<<'\n';
    return 0;
}
