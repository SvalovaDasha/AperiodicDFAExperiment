#pragma once

#include <vector>

namespace Generation{

    class StringRepresentationGenerator{
        std::vector<int> _max;
        std::vector<bool> _is_immutable;
        std::vector<int> _current;
        int _receiver;
        bool _finished;

    public:
        StringRepresentationGenerator(const std::vector<int> flag);
        std::vector<int> Next();
        bool Finished();
    };

    inline int max_value(int index_in_flag);
    std::vector<std::vector<int> > GenerateAllFlags(int n);
}