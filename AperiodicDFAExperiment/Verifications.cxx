#include "Verifications.h"
#include "ShortestResetWord.h"
#include "CircuitsSearcher.h"
#include "Constants.h"
#include <algorithm>
#include <stack>

#include <iostream>

//It checks only initial state reachability, because all states are reached from initial state by default.
bool Verifications::IsStronglyConnected(const std::vector<int>& string_representation){
    std::vector<std::vector<int> > reversed_representation = GetReversed(string_representation);
    std::vector<bool> used = DFS(reversed_representation);
    
    return IsAllTrue(used);
}

std::vector<std::vector<int> > Verifications::GetReversed(const std::vector<int>& string_representation){
    int n = string_representation.size();
    std::vector<std::vector<int> > result(n / k, std::vector<int>());

    for(int i = 0; i < n; i++){
        result[string_representation[i]].push_back(i / k);
    }

    return std::move(result);
}

bool Verifications::IsAllTrue(const std::vector<bool>& list){
    for(bool value : list){
        if(!value)
            return false;
    }

    return true;
}

std::vector<bool> Verifications::DFS(const std::vector<std::vector<int> >& graph){
    std::vector<bool> used(graph.size(), false);
    std::stack<int> stack;

    used[0] = true;
    stack.push(0);
    while(!stack.empty()){
        int current = stack.top();
        stack.pop();
        for(int adjacent : graph[current]){
            if(!used[adjacent]){
                stack.push(adjacent);
                used[adjacent] = true;
            }
        }
    }

    return std::move(used);
}


bool Verifications::SymbolProducesNontrivialCycle(const std::vector<int>& string_representation){
    int n = string_representation.size();
    std::vector<int> tags(n / k);

    for(int a = 0; a < k; a++){
        tags.assign(n / k, -1);
        for(int current = 0, tag = 0;
            current >= 0;
            current = GetFirstUntaggedState(tags), tag++){

            int next = current;
            do{
                tags[next] = tag;
                current = next;
                next = string_representation[index(current, a)];
            } while(tags[next] < 0);

            if((tags[current] == tags[next]) && (next != current)) //cycle detected
                return true;
        }
    }

    return false;
}

int Verifications::GetFirstUntaggedState(const std::vector<int>& tags){
    for(size_t i = 0; i < tags.size(); i++){
        if(tags[i] < 0)
            return i;
    }

    return -1;
}


bool Verifications::PreservesNontrivialPartialOrder(const std::vector<int>& string_representation){
    int n = string_representation.size() / k;
    for(int p = 0; p < n; p++){
        for(int q = 0; q < n; q++){
            if(p != q && TryToOrder(string_representation, p, q))
                return true;
        }
    }

    return false;
}

bool Verifications::TryToOrder(const std::vector<int>& string_representation, int p, int q){
    unsigned int n = string_representation.size() / k;
    std::stack<std::pair<int, int> > stack;
    std::vector<std::vector<bool> > order(n, std::vector<bool>(n)); // std::vector<int> ? wich int bolean mask
    for(size_t u = 0; u < n; u++)
        order[u][u] = true;

    order[p][q] = true;
    stack.push(std::make_pair<>(p, q));
    while(!stack.empty()){
        auto current_pair = stack.top();
        stack.pop();

        for(int a = 0; a < k; a++){
            int u = string_representation[index(current_pair.first, a)];
            int v = string_representation[index(current_pair.second, a)];
            if(!order[u][v]){
                if(!Check(order, u, v))
                    return false;
                order[u][v] = true;
                stack.push(std::make_pair<>(u, v));
            }
        }
    }

    return true;
}

bool Verifications::Check(std::vector<std::vector<bool> >& order, int p, int q){
    if(order[q][p])
        return false;

    for(size_t u = 0, n = order.size(); u < n; u++){
        if(!order[u][p])
            continue;
        for(size_t v = 0; v < n; v++){
            if(!order[q][v])
                continue;
            if(order[v][u])
                return false;
            order[u][v] = true;
        }
    }

    return true;
}

// www-igm.univ-mlv.fr/~perrin/Enseignement/Master2013/CoursOption/synchronizedAutomata.pdf
bool Verifications::IsAperiodic(const std::vector<int>& string_representation){
    std::vector<std::vector<int> > graph;
    SRW::GetSubsetsGraph(string_representation, graph);
    RemoveSingletonStates(graph); // delta(q, a) < 0 !

    //check only achievable states
    std::stack<int> stack;
    std::vector<bool> used(graph.size(), false);
    used.push_back(true);

    IdentityChecker checker(string_representation, graph);
    CircuitsSearcher searcher(graph);
    int state_of_all_states = graph.size() - 1;
    stack.push(state_of_all_states);
    used[state_of_all_states] = true;
    while(!stack.empty()){
        int u = stack.top();
        stack.pop();

        if(!searcher.CheckCircuitsStartedAt(u, checker))
            return false;

        for(int v : graph[u]){
            if(!used[v]){
                stack.push(v);
                used[v] = true;
            }
        }
    }

    return true;
}

void Verifications::RemoveSingletonStates(std::vector<std::vector<int> >& graph){
    for(size_t i = 0; i < graph.size(); i++){
        if(SRW::IsPowerOfTwo(i))
            graph[i].clear();
        for(size_t j = 0; j < graph[i].size(); j++){
            if(SRW::IsPowerOfTwo(graph[i][j]))
                graph[i][j] = graph.size();
        }
    }
}
