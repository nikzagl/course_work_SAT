from copy import copy, deepcopy
import numpy as np


class CNF:
    def __init__(self, expression: np.array, variables_number: int):
        self.__expression = expression
        self.__variables_number = variables_number

    def get_expression(self):
        return self.__expression

    def get_variables_number(self):
        return self.__variables_number

    def clauses_number(self):
        return self.__expression.shape[0]

    def __getitem__(self, index) -> list[int]:
        return self.__expression[index]

    def clause_value(self, clause_index: int, variables: np.array) -> bool:
        return any(self.__expression[clause_index][variable_index] * variables[variable_index] == 1 for variable_index in range(variables.shape[0]))

    def value(self, variables: np.array) -> bool:
        return all(self.clause_value(clause_index, variables) for clause_index in range(variables.shape[0]))

    def count_values(self, variables: np.array) -> int:
        return sum(self.clause_value(clause_index, variables) for clause_index in range(self.__expression.shape[0]))

    def remove_clause(self, clause_index: int) -> None:
        self.__expression[clause_index] = np.zeros(self.__expression.shape[1])

    def reduce_variable(self, variable_index) -> None:
        self.__expression[:, variable_index] = np.zeros(self.__expression.shape[0])