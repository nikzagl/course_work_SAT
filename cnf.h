//
// Created by home on 09.04.23.
//

#ifndef UNTITLED16_MAX_SAT_H
#define UNTITLED16_MAX_SAT_H
#include<bitset>
class CNF
{
    unsigned long long m_repr_number;
    unsigned int m_clause_size;
    unsigned int m_clauses_number;
public:
    unsigned int clause_size();
    CNF(unsigned long long repr_number, unsigned int clause_size, unsigned int clauses_number);
    template<size_t bitset_length>
    CNF(std::bitset<bitset_length>& bitset_representation, unsigned int clause_size, unsigned int clauses_number);
    unsigned long long operator[](size_t index);
    bool get_value(unsigned long long values_repr_number);
    template<size_t bitset_length>
    bool get_value(std::bitset<bitset_length>& values_bitset);
    void remove_clause(size_t index);
    void reduce_last_variable();
};
#include "cnf.tpp"
#endif //UNTITLED16_MAX_SAT_H
