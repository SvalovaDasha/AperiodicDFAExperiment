#include "StableOrder.h"
#include "Constants.h"

StableOrder::Order StableOrder::GetMaxStableOrder(const std::vector<int>& string_representation){
    int n = string_representation.size() / k;
    unsigned int max_size = 0;
    Order max_order;

    for(int p = 0; p < n; p++){
        for(int q = 0; q < n; q++){
            if(p == q)
                continue;
            Order next = GetOrderStartsIn(p, q, string_representation);
            if(next.size() > max_size){
                max_size = next.size();
                max_order = next;
            }
        }
    }

    return max_order;
}

StableOrder::Order StableOrder::GetOrderStartsIn(int p, int q, const std::vector<int>& string_representation){
    Order trivial(1, std::make_pair<>(p, q));
    int n = string_representation.size() / k;
    std::stack<std::pair<int, int> > stack;
    std::vector<std::vector<bool> > order(n, std::vector<bool>(n));
    for(int u = 0; u < n; u++)
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
                    return trivial;
                order[u][v] = true;
                stack.push(std::make_pair<>(u, v));
            }
        }
    }

    Order result;
    for(int u = 0; u < n; u++){
        for(int v = 0; v < int(order[u].size()); v++)
            if(order[u][v])
                result.push_back(std::make_pair<>(u, v));
    }

    return result;
}

bool StableOrder::Check(std::vector<std::vector<bool> >& order, int p, int q){
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
