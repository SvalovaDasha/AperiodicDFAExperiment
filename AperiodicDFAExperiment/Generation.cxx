#include "Generation.h"
#include "Constants.h"
#include <stack>

Generation::StringRepresentationGenerator::StringRepresentationGenerator(const std::vector<int> flag) : _current((flag.size() + 1) * k, 0),
                                                                                                        _is_immutable((flag.size() + 1) * k, false),
                                                                                                        _max((flag.size() + 1) * k, 0),
                                                                                                        _finished(false){
    for(size_t i = 0; i < flag.size(); i++){
        _current[flag[i]] = i + 1;
        int right_border = (i == flag.size() - 1 ? _max.size() : flag[i + 1]);
        _is_immutable[flag[i]] = true; // for skip immutable cells (cells with indexes from flag)
        for(int j = flag[i]; j < right_border; j++)
            _max[j] = i + 1;
    }
    _receiver = _current.size() - 1;
    _current[_current.size() - 1] = -1;
}

std::vector<int> Generation::StringRepresentationGenerator::Next(){
    if(_finished)
        return _max;

    _current[_receiver]++;
    if(_current[_receiver] > _max[_receiver]){
        do{
            _receiver--;
        } while(_receiver >= 0 && ((_current[_receiver] == _max[_receiver]) || _is_immutable[_receiver]));
            
        if(_receiver < 0){
            _finished = true;
            return _max;
        }

        _current[_receiver]++;
        for(size_t i = _receiver + 1; i < _current.size(); i++){
            if(!_is_immutable[i])
                _current[i] = 0;
        }
        _receiver = _current.size() - 1;
    }

    return _current;
}

bool Generation::StringRepresentationGenerator::Finished(){
    return _finished;
}

inline int Generation::max_value(int index_in_flag){
    return (index_in_flag + 1) * k - 1;
}

std::vector<std::vector<int> > Generation::GenerateAllFlags(int n){
    std::vector<int> current(n-1, 0);
    std::vector<std::vector<int> > all;
    int min = 0;
    int max = k-1;
    int receiver = 0;
    
    while(true){
        while(receiver != n-2){
            current[receiver] = min;
            min = min + 1;
            receiver++;
        }
        max = max_value(receiver);
        
        for(int i = min; i <= max; i++){
            current[receiver] = i; // flags
            all.push_back(current);
        }
        
        do{
            receiver--;
            max = max_value(receiver);
        }while(receiver >= 0 && current[receiver] == max);
        
        if(receiver < 0)
            break;
        
        current[receiver]++;
        min = current[receiver] + 1;
        receiver++;
        max = max_value(receiver);
    }
    return std::move(all);
}
