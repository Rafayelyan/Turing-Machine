#include "turing_machine.h"

using std::pair;
using std::vector;
using std::string;
using std::unordered_map;

#include <iostream>
#include <fstream>
#include <cstring>

TuringMachine::TuringMachine(const std::string & file_path)
{
    /*
        do some parsing from file and get result
        A = {   } vector of input alphabet
        B = {   } vector of output alphabet
        Q = {   } vector of states
        
        and table discribing lambda and delta functions
            unordered_map<pair<state, data>, pair<pair<state, data>, dir>>
     */

    std::fstream in_file;
    char*   temp_str;

    in_file.exceptions(std::ifstream::badbit);
    try
    {
        in_file.open(file_path, std::ios::out | std::ios::in);
    }
    catch (const std::ifstream::failure& e)
    {
        std::cerr << "Exception opening/reading file";
    }
    while (!in_file.eof())
    {
        char *str = nullptr;
        std::string temp;

        /* reading symbols for alphabet A, B, Q */
        getline(in_file, temp);
        if (temp == "")
        {
            continue;
        }
        temp_str = const_cast<char *>(temp.c_str());
        if (temp == "")
        {
            continue;
        }
        str = strtok(temp_str, ", ");
        while (str != NULL)
        {
            A.push_back(str[0]);
            str = strtok(NULL, ", ");
        }
        getline(in_file, temp);
        if (temp == "")
        {
            continue;
        }
        temp_str = const_cast<char *>(temp.c_str());
        str = strtok(temp_str, ", ");
        while (str != NULL)
        {
            B.push_back(str[0]);
            str = strtok(NULL, ", ");
        }

        getline(in_file, temp);
        if (temp == "")
        {
            continue;
        }
        temp_str = const_cast<char *>(temp.c_str());
        str = strtok(temp_str, ", ");
        while (str != NULL)
        {
            Q.push_back(str[0]);
            str = strtok(NULL, ", ");
        }

        int counter = 0;
        while (getline(in_file, temp))
        {
            int i = 0;
            if (temp[0] == '\0') 
            {
                continue;
            }
            temp_str = const_cast<char*>(temp.c_str());
            if (temp_str[0] == '\0') 
            {
                continue;
            }
            str = strtok(temp_str, " | ");
            char b;
            char q;
            char dir;
            std::string tempStr;
            while (str != NULL)
            {
                tempStr = str;
                b = tempStr.substr(0, tempStr.find(','))[0];
                tempStr = tempStr.substr(tempStr.find(',') + 1, tempStr.size() - 1);
                q = tempStr.substr(0, tempStr.find(','))[0];
                tempStr = tempStr.substr(tempStr.find(',') + 1, tempStr.size() - 1);
                dir = tempStr[0];
                if (q == '\0' || b == '\0' || dir == '\0' ||
                 (dir != '0' && dir != '1' && dir != '2'))
                {
                    throw std::invalid_argument("invalid argument in table");
                }
                table.insert(std::make_pair(std::make_pair(Q[counter], A[i]), std::make_pair(std::make_pair(q, b), dir)));
                str = strtok(NULL, " | ");
                ++i;
            }
            ++counter;
            i = 0;
        }
    }
}

/*
    dir:
        0 - do nothing
        1 - right
        2 - left
*/
void TuringMachine::run_turing_machine(std::string & input_line)
{
    char state = Q[0];
    char data;
    int i = 0;
    int dir;

    while (i < (int)input_line.size())
    {
        char temp = input_line[i];
        auto next_step = table.find(std::make_pair(state, temp));
        #ifdef DEBUG
        char prev_step = state;
        #endif
        state = next_step->second.first.first;
        data = next_step->second.first.second;
        dir = next_step->second.second - '0';
        #ifdef DEBUG
        std::cout<<"("<<input_line[i]<<", "<<prev_step<<") -> ("<<data<<", "<<state<<", "<<dir<<")"<<std::endl;
        #endif

        input_line[i] = data;
        if (dir == 0)
        {
            continue;
        }
        else if (dir == 1)
        {
            i += 1;
        }
        else if (dir == 2)
        {
            i -= 1;
        }
    }
}

void TuringMachine::print_table(alphabert & A, alphabert & Q,  Table & table)
{
    for (auto q_it : Q)
    {
        for (auto a_it : A)
        {
            auto res = table.find(std::make_pair(q_it, a_it));
            std::cout<<res->second.first.second<<", "<<res->second.first.first<<", "<<res->second.second<<" | ";
        }
        std::cout<<std::endl;
    }
}