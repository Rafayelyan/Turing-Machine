#include <iostream>
#include "turing_machine.h"

// ToDo: add hult option

int main()
{
    /*
    std::string input;
    int test_cnt;
    int test_pass_cnt;
    std::vector<std::pair<std::string, std::string>> test;

    test.push_back(std::make_pair("12332112", "abccbaab"));
    test.push_back(std::make_pair("abbaab", "*1"));
    test.push_back(std::make_pair("abbaab", "*0"));

    test_cnt = 3;
    test_pass_cnt = 0;
    for (int i = 0; i < test_cnt; ++i)
    {
        TuringMachine turing_machine("test_files/" + std::to_string(i + 1));
        turing_machine.run_turing_machine(test[i].first);
        std::string res = test[i].first;
        if (test[i].second[0] == '*')
        {
            if (test[i].second.back() == res.back())
            {
                std::cout<<"[OK]"<<std::endl;
                ++test_pass_cnt;
            }
            else
            {
                std::cout<<"[KO]"<<std::endl;
            }
        }
        else
        {
            if (test[i].second == res)
            {
                std::cout<<"[OK]"<<std::endl;
                ++test_pass_cnt;
            }
            else
            {
                std::cout<<"[KO]"<<std::endl;
            }
        }
    }

    if (test_pass_cnt == test_cnt)
    {
        std::cout<<"PASSED..."<<std::endl;
    }
    else
    {
        std::cout<<"FAILED!!!"<<std::endl;
    }
    */
    
    std::string in_file_path = "in_file.txt";
    std::string input_line = "123333322211111";
    TuringMachine machine(in_file_path);
    try
    {
        machine.run_turing_machine(input_line);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
    std::cout<<input_line<<std::endl;


    return (0);
}
