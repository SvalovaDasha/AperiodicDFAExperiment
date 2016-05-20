#include "stdafx.h"
#include "Tools.h"
#include <sstream>
#include "../AperiodicDFAExperiment/Constants.h"

std::vector<int> Tools::VectorFromArray(const int* a, int n){
    std::vector<int> result(n);
    result.assign(a, a + n);
    return result;
}

//template<class T>
bool Tools::AreEqual(std::vector<int> a, std::vector<int> b){
    if(a.size() != b.size())
        return false;

    for(size_t i = 0; i < a.size(); i++){
        if(a[i] != b[i])
            return false;
    }

    return true;
}

bool Tools::IsCorrect(std::vector<int> flag){
    for(int i = 0; i < int(flag.size()); i++){
        if(i != 0 && flag[i - 1] >= flag[i])
            return false;
        if(flag[i] >= (i + 1) * k)
            return false;
    }
    return true;
}

std::vector<int> Tools::VectorFromString(const std::string& str){
    std::vector<int> result;
    for(std::string& state : Split(str, ' ')){
        result.push_back(atoi(state.c_str()));
    }

    return std::move(result);
}

std::vector<bool> Tools::BoolVectorFromString(const std::string& str){
    std::vector<int> result_int = VectorFromString(str);
    std::vector<bool> result(result_int.size());
    for(size_t i = 0; i < result.size(); i++)
        result[i] = result_int[i] == 1;
    return std::move(result);
}

std::vector<std::vector<int> > Tools::MatrixFromString(const std::string& str){
    std::vector<std::vector<int> > result;
    for(std::string& list : Split(str, '|')){
        result.push_back(Tools::VectorFromString(list));
    }

    return std::move(result);
}

std::vector<std::string> Tools::Split(const std::string& str, char delimiter){
    std::vector<std::string> result;
    std::stringstream strstream(str);
    std::string token;
    while(std::getline(strstream, token, delimiter))
        result.push_back(token);
    return result;
}
