#include <iostream>
#include <fstream>

#include <cstring>

#include <vector>
#include <string>
#include <unordered_map>

using std::vector;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

typedef std::vector<char> alphabert;
typedef std::unordered_map<std::pair<char, char>, std::pair< std::pair<char, char>, char>, pair_hash> Table;

void print_table(alphabert & A, alphabert & Q,  Table & table)
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

int main()
{
    
    
    std::vector<char> A;
    std::vector<char> B;
    std::vector<char> Q;
    Table table;
    std::string file_path;
    std::fstream in_file;

    file_path = "in_file.txt";

    in_file.open(file_path, std::ios::out | std::ios::in);
    if(!in_file)
    {
        std::cerr << "Error: file could not be opened" << std::endl;
        exit(1);
    }
    vector<vector<char>*> vecs = {&A, &B, &Q}; 
    while (!in_file.eof())
    {
        char temp[255];
        char *str = nullptr;
        int counter = 0;
        while (counter < 3 && in_file.getline(temp, 255))
        {
            str = strtok(temp, ", ");
            while (str != NULL)
            {
                vecs[counter]->push_back(str[0]);
                str = strtok(NULL, ", ");
            }          
            ++counter;
            bzero(temp, 255);
        }
        bzero(temp, 255);
        counter = 0;
        while (in_file.getline(temp, 255))
        {
            int i = 0;
            if (temp[0] == '\0') 
            {
                continue;
            }
            str = strtok(temp, " | ");
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
                table.insert(std::make_pair(std::make_pair(Q[counter], A[i]), std::make_pair(std::make_pair(q, b), dir)));
                str = strtok(NULL, " | ");
                ++i;
            }
            ++counter;
            i = 0;
        }
    }

    print_table(A, Q, table);
    

}