//
// Created by home on 19.05.23.
//
#include "cnf.h"
unsigned long long max_number_with_given_bits(unsigned int bits)
{
    unsigned long long result = 1;
    for (unsigned int i = 0; i < bits; ++i)
    {
        result *= 2;
    }
    result -=1;
    return result;
}
unsigned int CNF::get_clause_size()const
{
    return m_clause_size;
}
unsigned int CNF::get_clauses_number() const
{
    return m_clauses_number;
}
unsigned long long CNF::get_repr_number() const
{
    return m_repr_number;
}
CNF::CNF(unsigned long long repr_number, unsigned int clause_size, unsigned int clauses_number)
{
    m_repr_number = repr_number;
    m_clause_size = clause_size;
    m_clauses_number = clauses_number;
}
unsigned long long CNF::operator[](size_t index) const
{
    unsigned long long cur_repr_number = m_repr_number;
    for(size_t cur_index = 0; cur_index < (m_clauses_number - index - 1); cur_index++)
    {
        cur_repr_number >>= m_clause_size;
    }
    return cur_repr_number & max_number_with_given_bits(m_clause_size);
}
bool CNF::value(unsigned long long values_repr_number)const
{
    for (size_t i = 0; i < m_clauses_number; ++i)
    {
        if (!(values_repr_number ^ (*this)[i]))
            return false;
    }
    return true;
}
template <size_t bitset_length>
bool CNF::value(const std::bitset<bitset_length>& values_bitset)const
{
    return get_value(values_bitset.to_ullong());
}
CNF CNF::remove_clause(size_t index)const
{
    unsigned long long result_repr_number = m_repr_number;
    unsigned long long tail = max_number_with_given_bits(index*m_clause_size) & result_repr_number;
    for(int cur_index = 0; cur_index <= index; ++cur_index)
    {
        result_repr_number >>=m_clause_size;
    }
    for(int cur_index = 0; cur_index <= index - 1; ++cur_index)
    {
        result_repr_number <<= m_clause_size;
    }
    result_repr_number |= tail;
    return {result_repr_number, m_clause_size, m_clauses_number - 1};
}
CNF CNF::reduce_last_variable()const
{
    unsigned long long result_repr_number = 0;
    unsigned long long subset_number = 0;
    for(int index = 0; index < m_clauses_number; ++index)
    {
        subset_number = (*this)[index];
        subset_number >>= 1;
        subset_number <<= (m_clause_size-1) * (m_clauses_number - index - 1);
        result_repr_number |= subset_number;
    }
    return {result_repr_number, m_clause_size-1, m_clauses_number};
}