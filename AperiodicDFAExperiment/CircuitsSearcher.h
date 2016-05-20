#pragma once

#include <vector>
#include <stack>
#include <set>

// w called stable for some u if delta(u, w) = u
class StableWordsSearcher{
    const std::vector<std::vector<int> >& graph;

public:
    StableWordsSearcher(const std::vector<std::vector<int> >& graph_);
    std::vector<std::vector<int> > GetLabels(const std::vector<int>& circuit);
};

class ComponentsSearcher{
    const std::vector<std::vector<int> >& graph;
    std::vector<std::set<int> > transposed_graph;

    std::vector<int> getOrder(int border);
    void fillOrder(std::vector<int> &order, std::vector<bool> &used, int start, int border);
    void fillComponent(std::vector<int> &components, int component_number, int start, int border);

public:
    ComponentsSearcher(const std::vector<std::vector<int> >& graph_);
    //sub graph with vertices >= start
    void FindSubGraphComponents(std::vector<int>& components, int start = 0);
};

class IdentityChecker{
    StableWordsSearcher stable_word_searcher;
    const std::vector<int>& string_representation;

public:
    IdentityChecker(const std::vector<int>& string_representation, const std::vector<std::vector<int> >& graph_);
    bool operator()(const std::vector<int>& circuit);

    bool IsIdentity(const std::vector<int>& word, int state);
    std::vector<int> GetStatesInSubset(int subset, int set_size);
};

// www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson 75.PDF
class CircuitsSearcher{
    std::vector<std::vector<int> > graph;
    ComponentsSearcher components_searcher;

    bool no_circuits_last;
    std::vector<int> stack;
    std::vector<bool> blocked;
    std::vector<int> bordered_components;

    std::vector<int> GetCircuit(int start);
    bool CheckCircuits(int v, int start, const std::vector<int>& components, IdentityChecker& checker);
    int GetMinimalVertexFromNontrivialComponent(const std::vector<int>& components, int min_v);
    void Circuits(int v, int start, const std::vector<int>& components, std::vector<std::vector<int> >& circuits);

public:
    CircuitsSearcher(const std::vector<std::vector<int> >& graph_);
    std::vector<std::vector<int> > GetCircuitStartedAt(int s);
    bool CheckCircuitsStartedAt(int s, IdentityChecker& checker);
    bool ThereAreNoCircuitsLast();
};

std::vector<std::vector<int> > Clear(std::vector<std::vector<int> > graph);