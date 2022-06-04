#ifndef TURING_MASHINE
# define TURING_MASHINE

#include <iostream>
#include <fstream>
#include <cstring>

#include <vector>
#include <string>
#include <unordered_map>

// unordered_map<pair<state, data>, pair<pair<state, data>, dir>>
class TuringMachine
{
    private:
    typedef std::vector<char> alphabert;
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2> &pair) const {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        }
    };
    typedef std::unordered_map<std::pair<char, char>, std::pair< std::pair<char, char>, char>, pair_hash> Table;
    public:
    TuringMachine(const std::string &);
    void run_turing_machine(std::string & input_line);
    void print_table(alphabert & A, alphabert & Q,  Table & table);
    private:
    alphabert A;
    alphabert B;
    alphabert Q;
    Table table;
};

# endif