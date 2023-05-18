#include <iostream>
#include <string>
#include "cnf.h"
#include "heuristics.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::bitset<40> bool_bitset("001011100");
    std::bitset<3> values_bitset("000");
    CNF A = CNF(bool_bitset, 3, 3);
    CNF SAT_approx = max_sat_heuristic_7_8(A);
    for (int i = 0; i < SAT_approx.get_clauses_number(); i++)
    {
        std::cout<<SAT_approx[i]<<" ";
    }
    return 0;
}
