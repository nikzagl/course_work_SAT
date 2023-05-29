//
// Created by home on 19.05.23.
//
#include "cnf.h"
#include <algorithm>
#include <cmath>
size_t CNF::get_clause_size()const
{
    if (m_expression.empty())
        return 0;
    return m_expression[0].size();
}
unsigned int CNF::get_variables_number() const
{
    return m_variables_number;
}
size_t CNF::get_clauses_number() const
{
    return m_expression.size();
}
CNF::CNF(const std::vector<std::vector<int>>& expr)
{
    bool abs_comp = [](int x, int y){return std::abs(x)>std::abs(y);};
    m_expression = expr;
    m_variables_number = 0;
    unsigned int max_abs = 0;
    for (std::vector<int>& clause: m_expression)
    {
        std::sort(clause.begin(), clause.end());
        max_abs = std::max(std::abs(clause.front()), std::abs(clause.back()));
        m_variables_number = std::max(max_abs, m_variables_number);
    }
}
CNF::CNF(const std::vector<std::vector<int>>& expr, unsigned int variables_number)
{
    m_expression = expr;
    m_variables_number = variables_number;
    for (std::vector<int>& clause: m_expression)
    {
        std::sort(clause.begin(), clause.end());
    }
}
CNF::CNF(const std::vector<int>& expr)
{
    m_expression.push_back(expr);
    std::sort(m_expression[0].begin(), m_expression[0].end());
    unsigned int max_abs = std::max(std::abs(m_expression[0].front()), std::abs(m_expression[0].back()));
    m_variables_number = std::max(max_abs, m_variables_number);
}
std::vector<std::vector<int>> CNF::get_expression() const {
    return m_expression;
}
std::vector<int> CNF::operator[](size_t index) const
{
    return m_expression[index];
}
bool CNF::clause_value(size_t clause_index, const std::vector<int>& variables)const
{
    auto are_equal = [this, &clause_index, &variables](size_t index){return m_expression[clause_index][index] == variables[index];};
    return std::any_of(variables.begin(), variables.end(), are_equal);
}
bool CNF::value(const std::vector<int> &variables) const
{
    auto is_true = [this, &variables](size_t index){return clause_value(index, variables);};
    return std::all_of(variables.begin(), variables.end(), is_true);
}
void CNF::remove_clause(size_t clause_index)
{
    m_expression.erase(m_expression.begin()+clause_index);
}
void CNF::reduce_variable(int variable_index) 
{
    unsigned int max_abs = 0;
    for (std::vector<int>& clause: m_expression)
    {
        clause.erase(std::remove(clause.begin(), clause.end(), variable_index), clause.end());
        clause.erase(std::remove(clause.begin(), clause.end(), -variable_index), clause.end());
        max_abs = std::max(std::abs(clause.front()), std::abs(clause.back()));
        m_variables_number = std::max(max_abs, m_variables_number);
    }

}

