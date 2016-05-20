#pragma once

#include "ShortestResetWord.h"
#include "CircuitsSearcher.h"
#include "Verifications.h"
#include "StableOrder.h"
#include "Generation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Tools.h"
#include <time.h>
#include <ctime>

double Percent(long long total, long long part){
    return 100.0 * part / total;
}

template<class T>
void Print(const std::vector<T>& vector, std::ofstream& fs){
    for(T v : vector)
        fs << v << " ";
    fs << std::endl << std::endl;
}

void PrintCounter(const std::vector<unsigned int>& counter, std::ofstream& fs){
    for(size_t i = 0; i < counter.size(); i++){
        if(counter[i] > 0)
            fs << i << "\t";
    }
    fs << std::endl;

    for(size_t i = 0; i < counter.size(); i++){
        if(counter[i] > 0)
            fs << counter[i] << "\t";
    }
    fs << std::endl;
}

std::string GetFileName(unsigned int n){
    char buffer[10];
    sprintf(buffer, "%d", n);
    return std::string(buffer) + "_states.txt";
}

bool CheckAutomaton(const std::vector<int>& string_representation,
                    std::vector<int>& reset_word){
    unsigned int n = string_representation.size() / k;
    reset_word.clear();
    if(Verifications::IsStronglyConnected(string_representation)){
        if(!Verifications::SymbolProducesNontrivialCycle(string_representation)){
            if(Verifications::PreservesNontrivialPartialOrder(string_representation)){
                reset_word = SRW::GetShortestResetWord(string_representation);
                if(/*reset_word.size() >= n && */reset_word.size() <= (n*(n + 1) / 6)){
                    bool is_aperiodic = Verifications::IsAperiodic(string_representation);
                    if(is_aperiodic){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void CheckAutomatons(unsigned int n, int argc, const char* argv[]){
    auto start_time = clock();

    std::vector<int> reset_word;
    unsigned long long total = 0;
    unsigned long long suitable = 0;
    unsigned long long aperiodic_candidate = 0;
    std::vector<unsigned int> sync_threshold_stat(n * (n + 1) / 6 + 1, 0);

    auto flags = Generation::GenerateAllFlags(n);
    long long flags_to_check_number = flags.size();
    std::cout << n << ": " << flags.size() << std::endl;
    int j = 0;
    long long counter = 0;
    long long last_total = 0;
    for(long long i = flags.size()-1; i < flags_to_check_number; i += 800){
        counter = 0;
        Generation::StringRepresentationGenerator generator(flags[i]);
        std::vector<int> string_representation = generator.Next();
        while(!generator.Finished()){
            total++;
            counter++;
           /* if(CheckAutomaton(string_representation, reset_word)){
                suitable++;
                sync_threshold_stat[reset_word.size()]++;
            }
            if(reset_word.size() > 0)
                aperiodic_candidate++;*/

            string_representation = generator.Next();
        }
        std::cout << i << ": ";
        for(size_t j = 0; j < flags[i].size(); j++)
            std::cout << flags[i][j] << " ";
        std::cout << std::endl << counter << std::endl;

        /*if((i + 1) % 20 == 0)
            std::cout << i + 1 << " of " << flags_to_check_number << " flags" << std::endl;*/
    }

    std::ofstream fs(GetFileName(n), std::fstream::out);
    fs << "N = " << n << std::endl;
    fs << "Time: " << double(clock() - start_time) / CLOCKS_PER_SEC << std::endl;
    fs << "Flags number: " << flags.size() << std::endl;
    fs << "Total:\t\t" << total << std::endl;
    fs << "Canditates:\t" << aperiodic_candidate << std::endl;
    fs << "Aperiodic:\t" << suitable << std::endl;
    
    fs << "Reset thresholds:" << std::endl;
    PrintCounter(sync_threshold_stat, fs);
    
}

std::vector<std::string> Split(const std::string& str, char delimiter){
    std::vector<std::string> result;
    std::stringstream strstream(str);
    std::string token;
    while(std::getline(strstream, token, delimiter))
        result.push_back(token);
    return result;
}

std::vector<int> VectorFromString(const std::string& str){
    std::vector<int> result;
    for(std::string& state : Split(str, ' ')){
        result.push_back(atoi(state.c_str()));
    }

    return std::move(result);
}

int main(int argc, const char* argv[]){
    unsigned int min_n = 6;
    unsigned int max_n = 6;
    if(argc > 1){
        min_n = atoi(argv[1]);
        max_n = min_n;
    }
    if(argc > 2)
        max_n = atoi(argv[2]);

    for(unsigned int n = min_n; n <= max_n; n++)
        CheckAutomatons(n, argc, argv);

    return 0;
}