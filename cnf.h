//
// Created by home on 09.04.23.
//

#pragma once
#include<bitset>
class CNF
{
    unsigned long long m_repr_number;
    unsigned int m_clause_size;
    unsigned int m_clauses_number;
public:
    unsigned int get_clause_size() const;
    unsigned int get_clauses_number() const;
    unsigned long long get_repr_number() const;
    CNF(unsigned long long repr_number, unsigned int clause_size, unsigned int clauses_number);
    template<size_t bitset_length>
    CNF(std::bitset<bitset_length>& bitset_representation, unsigned int clause_size, unsigned int clauses_number);
    unsigned long long operator[](size_t index) const;
    bool value(unsigned long long values_repr_number) const;
    template<size_t bitset_length>
    bool value(const std::bitset<bitset_length>& values_bitset) const;
    CNF remove_clause(size_t index) const;
    CNF reduce_last_variable() const;
};
#include "cnf.tpp"