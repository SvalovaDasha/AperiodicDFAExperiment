#include "../AperiodicDFAExperiment/Verifications.h"
#include "../AperiodicDFAExperiment/ShortestResetWord.h"
#include "../AperiodicDFAExperiment/Generation.h"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <math.h>
#include <ctime>
#include "mpi.h"


enum StatType{
    Total,
    Aperiodic,
    NoOneSymbolCyrcles,
    StronglyConnected,
    PreserveNonTrivialOrder,
    ShortResetWord,
    STAT_TYPE_NUM
};

double Percent(long long total, long long part){
    return 100.0 * part / total;
}

template<class T>
void Print(const std::vector<T>& vector){//, std::ofstream& fs){
    for(T v : vector)
        std::cout << v << " ";
    std::cout << std::endl;
}

void PrintArray(long long* counter, unsigned int size, std::ofstream& fs){
    for(size_t i = 0; i < size; i++){
        if(counter[i] > 0)
            fs << i << "\t";
    }
    fs << std::endl;

    for(size_t i = 0; i < size; i++){
        if(counter[i] > 0)
            fs << counter[i] << "\t";
    }
    fs << std::endl;
}

std::string GetFileName(unsigned int n, long long start_i = 0){
    char buffer[10];
    sprintf(buffer, "%d_%d", n, start_i);
    return "MPI_" + std::string(buffer) + "_states.txt";
}

void PrintProgress(int id, unsigned long long start_i, unsigned long long finished_i){
    std::cout << id << ": From " << start_i << " to " << finished_i << " flags have been done." << std::endl;
}

void PrintPart(std::ofstream& fs, const std::string& label, long long part, long long total){
    fs << label.c_str() << part << "(" << Percent(total, part) << "%)" << std::endl;
}

void PrintStat(long long* stat, std::ofstream& fs){
    fs << "Total:\t\t" << stat[StatType::Total] << std::endl;
    PrintPart(fs, " From them no one cyrcles:\t", stat[StatType::NoOneSymbolCyrcles], stat[StatType::Total]);
    PrintPart(fs, "  From them strongly connected:\t", stat[StatType::StronglyConnected], stat[StatType::NoOneSymbolCyrcles]);
    PrintPart(fs, "   From them preserve pertial order:\t", stat[StatType::PreserveNonTrivialOrder], stat[StatType::StronglyConnected]);
    PrintPart(fs, "    From them with short reset word:\t", stat[StatType::ShortResetWord], stat[StatType::PreserveNonTrivialOrder]);
    PrintPart(fs, "For checking aperiodicity: ", stat[StatType::ShortResetWord], stat[StatType::Total]);
    PrintPart(fs, "Aperiodic:\t", stat[StatType::Aperiodic], stat[StatType::Total]);
}

inline long long GetStart_i(int id, int process_num,
                            double bunch_size,
                            long long flags_number){
    return ceil(id * bunch_size);
}

inline long long GetEnd_i(int id, int process_num,
                          double bunch_size,
                          long long flags_number){
    if(id == (process_num - 1))
        return flags_number;
    return std::min(GetStart_i(id + 1, process_num, bunch_size, flags_number), flags_number);
}

std::vector<unsigned int> RangeIt(unsigned int a, unsigned int b){
    std::vector<unsigned int> result(b - a);
    for(size_t i = 0; i < (b - a); i++)
        result[i] = a + i;
    return std::move(result);
}

bool CheckAutomaton(const std::vector<int>& string_representation,
                    std::vector<int>& reset_word,
                    long long* stat){
    reset_word.clear();
    unsigned int n = string_representation.size() / k;
    if(!Verifications::SymbolProducesNontrivialCycle(string_representation)){
        stat[StatType::NoOneSymbolCyrcles]++;
        if(Verifications::IsStronglyConnected(string_representation)){
            stat[StatType::StronglyConnected]++;
            if(Verifications::PreservesNontrivialPartialOrder(string_representation)){
                stat[StatType::PreserveNonTrivialOrder]++;
                reset_word = SRW::GetShortestResetWord(string_representation);
                if(/*reset_word.size() >= n && */reset_word.size() <= (n*(n + 1) / 6)){
                    stat[StatType::ShortResetWord]++;
                    if(Verifications::IsAperiodic(string_representation)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void CheckAutomatons(unsigned int n, int argc, char* argv[]){
    auto start_time = clock();
    auto flags = Generation::GenerateAllFlags(n);
    long long from = 0;
    long long to = flags.size();
    if(argc > 2)
        from = strtoll(argv[2], NULL, 0);
    if(argc > 3)
        to = strtoll(argv[3], NULL, 0);
    flags = std::vector<std::vector<int>>(flags.begin() + from, flags.begin() +  to);


    std::vector<unsigned int> order = RangeIt(0, flags.size());
    std::random_shuffle(order.begin(), order.end());

    int id;
    int process_num;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &process_num);
    
    long long* global_stat;
    long long* global_sync_threshold_stat;
    unsigned int sync_threshold_border = n * (n + 1) / 6 + 1;
    if(0 == id){
        std::cout << "Total part: [" << from << ", " << to << "]" << std::endl;
        global_stat = new long long[StatType::STAT_TYPE_NUM]();
        global_sync_threshold_stat = new long long[sync_threshold_border]();
    }

    std::vector<int> reset_word;
    long long* stat = new long long[StatType::STAT_TYPE_NUM]();
    long long* sync_threshold_stat = new long long[sync_threshold_border]();

    long long flags_to_check_number = flags.size();
    double bunch_size = 1.0 * flags_to_check_number / process_num;
    long long start_i = GetStart_i(id, process_num, bunch_size, flags_to_check_number);
    long long end_i = GetEnd_i(id, process_num, bunch_size, flags_to_check_number);

    for(long long i = start_i; i < end_i; i++){
        Generation::StringRepresentationGenerator generator(flags[order[i]]);
        std::vector<int> string_representation = generator.Next();
        while(!generator.Finished()){
            stat[StatType::Total]++;
            if(CheckAutomaton(string_representation, reset_word, stat)){
                stat[StatType::Aperiodic]++;
                sync_threshold_stat[reset_word.size()]++;
            }

            /*if(stat[StatType::Total] % 1000000 == 0)
                std::cout << stat[StatType::Total] << std::endl;*/
            string_representation = generator.Next();
        }
    }
    std::cout << id << ": Finished [" << start_i + from << ", " << end_i + from << ") flags, " << stat[StatType::Total] << " automata" << std::endl;

    MPI_Reduce(stat, global_stat, StatType::STAT_TYPE_NUM, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(sync_threshold_stat, global_sync_threshold_stat, sync_threshold_border, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(0 == id){
        std::ofstream fs(GetFileName(n, start_i + from), std::fstream::out);
        fs << "N = " << n << std::endl;
        fs << "Time: " << double(clock() - start_time) / CLOCKS_PER_SEC << std::endl;
        fs << "Flags number: " << flags.size() << std::endl;
        PrintStat(global_stat, fs);
        fs << "Reset thresholds:" << std::endl;
        PrintArray(global_sync_threshold_stat, sync_threshold_border, fs);

        delete[] global_sync_threshold_stat;
        delete[] global_stat;
    }
    delete[] sync_threshold_stat;
    delete[] stat;

    MPI_Finalize();
}

int main(int argc, char* argv[]){
    unsigned int n;
    if(argc < 2){
        std::cout << "Usage: MPI n [from] [to]" << std::endl;
    }
    
    n = atoi(argv[1]);
    CheckAutomatons(n, argc, argv);

    return 0;
}