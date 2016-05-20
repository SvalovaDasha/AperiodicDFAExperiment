#include <sstream>
#include "Tools.h"

std::vector<std::string> Tools::Split(const std::string& str, char delimiter){
    std::vector<std::string> result;
    std::stringstream strstream(str);
    std::string token;
    while(std::getline(strstream, token, delimiter))
        result.push_back(token);
    return result;
}

std::vector<int> Tools::VectorFromString(const std::string& str){
    std::vector<int> result;
    for(std::string& state : Split(str, ' ')){
        result.push_back(atoi(state.c_str()));
    }

    return std::move(result);
}

std::vector<std::vector<int> > Tools::MatrixFromString(const std::string& str){
    std::vector<std::vector<int> > result;
    for(std::string& list : Split(str, '|')){
        result.push_back(Tools::VectorFromString(list));
    }

    return std::move(result);
}
