//
// Created by home on 09.04.23.
//

#pragma once
#include <vector>
#include<bitset>
#include <array>
unsigned long long max_number_with_given_bits(unsigned int bits);



class CNF
{
    unsigned int m_variables_number = 0;
    std::vector<std::vector<int>> m_expression;

public:
    unsigned int get_variables_number() const;
    [[nodiscard]] size_t get_clause_size() const;
    [[nodiscard]] size_t get_clauses_number() const;
    std::vector<std::vector<int>> get_expression() const;
    explicit CNF(const std::vector<std::vector<int>>& expr);
    explicit CNF(const std::vector<std::vector<int>>&expr, unsigned int variables_number);
    explicit CNF(const std::vector<int> &expr);
    std::vector<int> operator[](size_t index)const;
    bool clause_value(size_t clause_index, const std::vector<int>& variables)const;
    bool value(const std::vector<int>& variables)const;
    void reduce_variable(int variable_index);
    void remove_clause(size_t clause_index);
};
