#include <iostream>
#include <string>
#include<fstream>
#include <cmath>
#include "cnf.h"
#include "heuristics.h"
#include <chrono>
#include <limits>
#include <sstream>
constexpr auto max_size = std::numeric_limits<std::streamsize>::max();
CNF read_cnf(const std::string& filename)
{
    std::ifstream file_in;
    file_in.open(filename);
    if (!file_in.is_open())
        std::cout<<"Error";
    for(int i = 0; i < 2; i++)
    {
        file_in.ignore(max_size, '\n');
    }
    std::string line;
    std::getline(file_in, line);
    std::stringstream ss;
    std::cout<<line;
    ss << line;
    int variable;
    for (int i = 0; i < 2; i++)
    {
        ss.ignore(max_size, ' ');
    }
    unsigned int variables_number = 0;
    ss >> variables_number;
    ss.ignore(max_size, ' ');
    std::vector<std::vector<int>> expression;
    std::vector<int> expression_line;
    for(size_t i = 0; i < variables_number; ++i) {
        expression_line.clear();
        ss.clear();
        std::getline(file_in, line);
        ss<<line;
        while(ss >>variable)
        {
            if(variable != 0)
                expression_line.push_back(variable);
        }
        expression.push_back(expression_line);
    }

    return CNF{expression, variables_number};
}
int main()
{
    auto A = read_cnf("max3sat_benchmarks_70v/s3v70c800-1.cnf");
    std::vector<int> SAT_approx = max_sat_heuristic_7_8(A);
    for(int elem: SAT_approx)
    {
        std::cout<<elem<<" ";
    }
    std::cout<<"\n";
    return 0;
}
