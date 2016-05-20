#include <Windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#define k 2

inline int index(int i, int a){
    return i * k + a;
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

std::vector<std::vector<int> > MatrixFromString(const std::string& str){
    std::vector<std::vector<int> > result;
    for(std::string& list : Split(str, '|')){
        result.push_back(VectorFromString(list));
    }

    return std::move(result);
}

std::string GetOrderString(const std::vector<std::vector<int>>& max_order){
    std::string result;
    result += "\ndigraph G2{\nedge [dir=none]\n";

    for(size_t i = 0; i < max_order.size(); i++){
        for(int u : max_order[i]){
            std::string edgeLabel = "";
            result += " " + std::to_string(u) + "->" + std::to_string(i) + ";\n";
        }
    }
    result += "}";
    return result;
}

std::string GetStringRepresentationString(const std::vector<int> &string_representation){
    int n = string_representation.size() / k;
    std::string result;
    result += "\nString representation:\n0";
    for(int i = 1; i < n; i++)
        result += "     " + std::to_string(i);

    result += "\n " + std::to_string(string_representation[index(0, 0)]) + ' ' + std::to_string(string_representation[index(0, 1)]);
    for(int i = 1; i < n; i++)
        result += " | " + std::to_string(string_representation[index(i, 0)]) + ' ' + std::to_string(string_representation[index(i, 1)]);

    return result;
}

void PrintInGraphViz(const std::vector<int> &string_representation,
                     const std::vector<int> &reset_word,
                     const std::string& fileName){
    std::string dot = "digraph G{\n";

    dot += " label = \"Reset word: ";
    for(int a : reset_word)
        dot += (a + 'a');

    dot += GetStringRepresentationString(string_representation);

    dot += "\";\n";

    int n = string_representation.size() / k;
    for(int i = 0; i < n; i++){
        for(int a = 0; a < k; a++){
            std::string edgeLabel = "";
            edgeLabel += (a + 'a');

            dot += " " + std::to_string(i) + "->" + std::to_string(string_representation[index(i, a)]) + "[label=" + edgeLabel + "]" + ";\n";
        }
    }
    dot += "}";

    std::ofstream out(fileName.c_str());
    out << dot;
    out.close();

    ShellExecuteA(NULL, "open", "C:\\Program Files\\Graphviz2.38\\bin\\dot.exe", (fileName + " + -Tjpg -O").c_str(), NULL, SW_SHOWDEFAULT);
}

int main(int argc, const char* argv[]){
    if(argc < 3){
        std::cout << "Usage: DrawAutomaton source output_dir\n\nSource format (all numbers are separated by a space):\n  string_representation\n  shortest_reset_word" << std::endl;
        return 0;
    }
    const std::string source(argv[1]);
    const std::string fileName(argv[2]);

    std::ifstream fn(source, std::ifstream::in);
    if(fn.fail()){
        std::cerr << "ERROR: can't open file " << source << std::endl;
        return 1;
    }

    std::string line;
    std::vector<int> reset_word;
    std::vector<int> string_representation;
    std::vector<std::vector<int>> max_order;
    unsigned int counter = 0;
    while(std::getline(fn, line)){
        counter++;
        string_representation = VectorFromString(line);
        std::getline(fn, line);
        reset_word = VectorFromString(line);
        /*std::getline(fn, line);
        max_order = MatrixFromString(line);*/
        PrintInGraphViz(string_representation, reset_word, fileName + std::to_string(counter) + ".gv");
    }
    fn.close();

    return 0;
}