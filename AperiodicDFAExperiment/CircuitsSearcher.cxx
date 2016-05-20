#include "CircuitsSearcher.h"
#include "Constants.h"
#include <algorithm>
#include <iostream>

ComponentsSearcher::ComponentsSearcher(const std::vector<std::vector<int> >& graph_) : graph(graph_){
    transposed_graph.resize(graph.size());
    for(int u = 0; u < int(graph.size()); u++){
        for(int v : graph[u])
            transposed_graph[v].insert(u);
    }
}

void ComponentsSearcher::fillOrder(std::vector<int> &order,
                                   std::vector<bool> &used,
                                   int start, int border){
    used[start] = true;
    for(auto u : graph[start]){
        if(!used[u] && u >= border)
            fillOrder(order, used, u, border);
    }
    order.push_back(start);
}

std::vector<int> ComponentsSearcher::getOrder(int border){
    std::vector<int> order;
    std::vector<bool> used(graph.size(), false);

    for(size_t v = border; v < graph.size(); v++){
        if(!used[v])
            fillOrder(order, used, v, border);
    }

    return order;
}

void ComponentsSearcher::fillComponent(std::vector<int> &components,
                                       int component_number,
                                       int start, int border){
    std::stack<int> component_stack;
    component_stack.push(start);
    components[start] = component_number;
    while(!component_stack.empty()){
        int v = component_stack.top();
        component_stack.pop();
        for(auto u : transposed_graph[v]){
            if(components[u] < 0 && u >= border){
                component_stack.push(u);
                components[u] = component_number;
            }
        }
    }
}

void ComponentsSearcher::FindSubGraphComponents(std::vector<int>& components, int start){
    components.assign(components.size(), -1);
    std::vector<int> reverse_order = getOrder(start);

    int current_component = 0;
    int v;
    int n = reverse_order.size();
    for(int i = 0; i < n; i++){
        v = reverse_order[n - i - 1];
        if(components[v] < 0){
            fillComponent(components, current_component, v, start);
            current_component++;
        }
    }
}


std::vector<int> CircuitsSearcher::GetCircuit(int start){
    std::vector<int> circuit;
    circuit.push_back(start);
    for(size_t i = stack.size() - 1; stack[i] != start; i--)
        circuit.push_back(stack[i]);
    circuit.push_back(start);
    std::reverse(circuit.begin(), circuit.end());

    return std::move(circuit);
}

void CircuitsSearcher::Circuits(int v, int start,
                                const std::vector<int>& components,
                                std::vector<std::vector<int> >& circuits){
    blocked[v] = true;
    stack.push_back(v);

    for(int u : graph[v]){
        if(components[u] != components[v])
            continue;

        if(u == start && v != u){
            circuits.push_back(GetCircuit(start));
        }else{
            if(!blocked[u])
                Circuits(u, start, components, circuits);
        }
    }

    blocked[stack.back()] = false;
    stack.pop_back();
}

int CircuitsSearcher::GetMinimalVertexFromNontrivialComponent(const std::vector<int>& components, int min_v){
    std::vector<int> components_sizes(components.size(), 0);
    for(size_t i = 0; i < components.size(); i++){
        if(components[i] >= 0)
            components_sizes[components[i]]++;
    }
    for(int i = min_v; i<int(components.size()); i++){
        if(components_sizes[components[i]] > 1)
            return i;
    }

    return -1;
}

CircuitsSearcher::CircuitsSearcher(const std::vector<std::vector<int> >& graph_) : graph(Clear(graph_)),
                                                                                   no_circuits_last(false),
                                                                                   components_searcher(graph){
    blocked.assign(graph.size(), false);
    bordered_components.assign(graph.size(), -1);
}

std::vector<std::vector<int> > Clear(std::vector<std::vector<int> > graph_){
    std::vector<bool> used(graph_.size());
    std::vector<std::vector<int> > graph;
    used.push_back(true);
    for(size_t u = 0; u < graph_.size(); u++){
        graph.push_back(std::vector<int>());
        used.assign(used.size(), false);
        used.back() = true;
        for(int v : graph_[u]){
            if(!used[v]){
                graph[u].push_back(v);
                used[v] = true;
            }
        }
    }
    return std::move(graph);
}

std::vector<std::vector<int> > CircuitsSearcher::GetCircuitStartedAt(int s){
    std::vector<std::vector<int> > result;

    if(s >= int(graph.size()) || s < 0)
        return result;

    for(int v : graph[s]){
        if(s == v)
            result.push_back(std::vector<int>(2, s));
    }

    components_searcher.FindSubGraphComponents(bordered_components, s);

    int min_s = GetMinimalVertexFromNontrivialComponent(bordered_components, s);
    no_circuits_last = (min_s < 0);
    if(min_s == s){
        for(size_t v = s; v < bordered_components.size(); v++){
            if(bordered_components[s] == bordered_components[v])
                blocked[v] = false;
        }
        Circuits(s, s, bordered_components, result);
    }else
        return result;

    return std::move(result);
}

bool CircuitsSearcher::CheckCircuitsStartedAt(int s, IdentityChecker& checker){
    if(s >= int(graph.size()) || s < 0)
        return true;

    for(int v : graph[s]){
        if(s == v){
            if(!checker(std::vector<int>(2, s)))
                return false;
        }
    }

    components_searcher.FindSubGraphComponents(bordered_components, s);

    int min_s = GetMinimalVertexFromNontrivialComponent(bordered_components, s);
    no_circuits_last = (min_s < 0);
    if(min_s == s){
        for(size_t v = s; v < bordered_components.size(); v++){
            if(bordered_components[s] == bordered_components[v])
                blocked[v] = false;
        }
        return CheckCircuits(s, s, bordered_components, checker);
    }
    
    return true;
}

bool CircuitsSearcher::CheckCircuits(int v, int start, const std::vector<int>& components, IdentityChecker& checker){
    blocked[v] = true;
    stack.push_back(v);

    for(int u : graph[v]){
        if(components[u] != components[v])
            continue;

        if(u == start && v != u){
            if(!checker(GetCircuit(start)))
                return false;
        }
        else{
            if(!blocked[u] && !CheckCircuits(u, start, components, checker))
                return false;
        }
    }

    blocked[stack.back()] = false;
    stack.pop_back();
    return true;
}

bool CircuitsSearcher::ThereAreNoCircuitsLast(){
    return no_circuits_last;
}

StableWordsSearcher::StableWordsSearcher(const std::vector<std::vector<int> >& graph_) : graph(graph_)/*,
                                                                                         searcher(graph_)*/{
}

unsigned long long TotalSizeOf(const std::vector<std::vector<int> >& result){ // MB
    unsigned long long total = 0;
    for(size_t i = 0; i < result.size(); i++)
        total += result[i].size() * sizeof(int) / 1024 / 1024;
    return total;
}

std::vector<std::vector<int> > StableWordsSearcher::GetLabels(const std::vector<int>& circuit){
    std::vector<std::vector<int> > result;
    size_t start = 0;
    result.push_back(std::vector<int>(circuit.size() - 1, k));
    for(size_t i = 0; i < circuit.size() - 1; i++){
        for(int a = 0; a < k; a++){
            if(graph[circuit[i]][a] == circuit[i + 1]){
                size_t j = start;
                if(result.back()[i] != k){
                    j = result.size();
                    std::vector<std::vector<int> > copy(result.begin() + start, result.end());
                    result.insert(result.end(), copy.begin(), copy.end());
                }

                /*if(result.size() > 1e6){
                    std::cout << "Stable set is too big: " << result.size() << std::endl;
                    result.push_back(std::vector<int>());
                    return (std::move(result));
                }*/

                for(; j < result.size(); j++)
                    result[j][i] = a;
            }
        }
    }
    return std::move(result);
}

IdentityChecker::IdentityChecker(const std::vector<int>& string_representation_,
                                 const std::vector<std::vector<int> >& graph_)
                                                      : stable_word_searcher(graph_),
    string_representation(string_representation_){
}

bool IdentityChecker::operator()(const std::vector<int>& circuit){
    for(int state : GetStatesInSubset(circuit[0], string_representation.size() / k)){
        for(auto& word : stable_word_searcher.GetLabels(circuit)){
            if(!IsIdentity(word, state))
                return false;
        }
    }
    return true;
}

bool IdentityChecker::IsIdentity(const std::vector<int>& word, int state){
    int current = state;
    for(size_t i = 0; i < word.size(); i++)
        current = string_representation[index(current, word[i])];
    return current == state;
}

std::vector<int> IdentityChecker::GetStatesInSubset(int subset, int set_size){
    std::vector<int> result;
    for(int i = 0; i < set_size; i++){
        int singleton = (1 << i);
        if((subset & singleton) == singleton)
            result.push_back(i);
    }

    return std::move(result);
}
