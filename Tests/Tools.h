#pragma once

#include <vector>

namespace Tools{
    std::vector<int> VectorFromArray(const int* a, int n);

   // template<class T>
    bool AreEqual(std::vector<int> a, std::vector<int> b);
    bool IsCorrect(std::vector<int> flag);
    std::vector<int> VectorFromString(const std::string& str);
    std::vector<bool> BoolVectorFromString(const std::string& str);
    std::vector<std::vector<int> > MatrixFromString(const std::string& str);
    std::vector<std::string> Split(const std::string& str, char delimiter);
}