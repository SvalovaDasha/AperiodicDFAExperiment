#pragma once

#define k 2

inline int index(int state, int a){
    return state * k + a;
}
