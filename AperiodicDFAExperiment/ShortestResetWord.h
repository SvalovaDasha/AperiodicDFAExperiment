#pragma once

#include <set>
#include <vector>
#include "Constants.h"

namespace SRW{
    std::vector<int> GetShortestResetWord(const std::vector<int>& string_representation);
    void GetSubsetsGraph(const std::vector<int>& string_representation, std::vector<std::vector<int> >& graph);
    std::vector<int> GetLabelsOfPathToSingleton(const std::vector<std::vector<int> >& graph);
    std::vector<int> RecoverPathLabel(const std::vector<int>& parent, const std::vector<int> letters, int start);
    inline bool IsPowerOfTwo(int n);
}