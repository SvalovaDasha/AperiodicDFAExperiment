#pragma once

#include <vector>
#include <set>

namespace Verifications{
    bool IsStronglyConnected(const std::vector<int>& string_representation);
    std::vector<std::vector<int> > GetReversed(const std::vector<int>& string_representation);
    bool IsAllTrue(const std::vector<bool>& list);

    bool SymbolProducesNontrivialCycle(const std::vector<int>& string_representation);
    int GetFirstUntaggedState(const std::vector<int>& tags);
    std::vector<bool> DFS(const std::vector<std::vector<int> >& graph);

    bool PreservesNontrivialPartialOrder(const std::vector<int>& string_representation);
    bool TryToOrder(const std::vector<int>& string_representation, int p, int q);
    bool Check(std::vector<std::vector<bool> >& order, int p, int q);

    bool IsAperiodic(const std::vector<int>& string_representation);
    void RemoveSingletonStates(std::vector<std::vector<int> >& graph);
}