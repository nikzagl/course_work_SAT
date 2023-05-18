//
// Created by home on 09.04.23.
//
#pragma once
#include <string>

template <size_t bitset_length>
CNF::CNF(std::bitset<bitset_length>& bitset_representation, unsigned int clause_size, unsigned int clauses_number)
{
    m_repr_number = bitset_representation.to_ullong();
    m_clause_size = clause_size;
    m_clauses_number = clauses_number;
}
