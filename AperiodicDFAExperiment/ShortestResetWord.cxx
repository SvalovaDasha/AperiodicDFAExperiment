#include "ShortestResetWord.h"
#include <queue>

std::vector<int> SRW::GetShortestResetWord(const std::vector<int>& string_representation){
    std::vector<std::vector<int> > graph;
    GetSubsetsGraph(string_representation, graph);
    return std::move(GetLabelsOfPathToSingleton(graph));
}

// state 2^n-1 is set of all states
void SRW::GetSubsetsGraph(const std::vector<int>& string_representation,
                          std::vector<std::vector<int> >& graph){
    unsigned int n = string_representation.size() / k;
    if(n > std::numeric_limits<unsigned int>::digits)
        return;

    unsigned int ui2_n = unsigned int(std::pow(2.0, n));
    graph.resize(ui2_n, std::vector<int>(k, 0));
    graph[0].clear();
    for(size_t u = 1; u < ui2_n; u++){
        for(int a = 0; a < k; a++){
            for(size_t i = 0; i < n; i++){
                if(u & (1 << i))
                    graph[u][a] |= (1 << string_representation[index(i, a)]);
            }
        }
    }
}

std::vector<int> SRW::GetLabelsOfPathToSingleton(const std::vector<std::vector<int> >& graph){
    std::vector<int> parent(graph.size(), -1);
    std::vector<int> letter(graph.size(), k);
    std::queue<int> queue;

    int start = graph.size() - 1;// because it's state of all states
    parent[start] = start;
    queue.push(start);
    while(!queue.empty()){
        int current = queue.front();
        queue.pop();
        for(int a = 0; a < k; a++){
            if(parent[graph[current][a]] < 0){
                queue.push(graph[current][a]);
                parent[graph[current][a]] = current;
                letter[graph[current][a]] = a;

                if(IsPowerOfTwo(graph[current][a]))
                    return std::move(RecoverPathLabel(parent, letter, graph[current][a]));
            }
        }
    }

    return std::vector<int>();
}

std::vector<int> SRW::RecoverPathLabel(const std::vector<int>& parent,
                                       const std::vector<int> letter,
                                       int start){
    std::vector<int> path;
    int current = start;
    while(parent[current] != current){
        path.push_back(letter[current]);
        current = parent[current];
    }

    std::reverse(path.begin(), path.end());
    return std::move(path);
}

inline bool SRW::IsPowerOfTwo(int n){
    return (n != 0) && ((n & (n - 1)) == 0);
}