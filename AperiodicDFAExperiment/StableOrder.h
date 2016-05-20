#include <vector>
#include <stack>

namespace StableOrder{
    typedef std::vector<std::pair<int, int> > Order;

    Order GetMaxStableOrder(const std::vector<int>& string_representation);
    Order GetOrderStartsIn(int p, int q, const std::vector<int>& string_representation);
    bool Check(std::vector<std::vector<bool> >& order, int p, int q);
}