#pragma once

#include <vector>

namespace Tools{
    std::vector<int> VectorFromString(const std::string& str);
    std::vector<std::vector<int> > MatrixFromString(const std::string& str);
    std::vector<std::string> Split(const std::string& str, char delimiter);
}