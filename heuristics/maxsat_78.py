from typing import Callable, Any

from cnf import CNF
from copy import copy,deepcopy
import numpy as np


def _altered_expectation(evaluated_cnf: CNF, variable_num: int, value: int) -> float:
    result: float = 0
    for clause_number, curr_value in enumerate(evaluated_cnf[:, variable_num]):
        clause_size = np.sum(evaluated_cnf[clause_number] != 0)
        if curr_value == value:
            result += 1
        elif curr_value == -value:
            result += 1 - 1 / (2 ** (clause_size - 1))
        else:
            result += 1 - 1 / (2 ** clause_size)
    return result


def solve(cnf: CNF):
    variables_number: int = cnf.get_variables_number()
    curr_cnf = deepcopy(cnf)
    expectations = [0, 0]
    multiplier: Callable[[bool], int] = lambda x: 1 if x else -1
    result: np.array = np.ones(variables_number)
    for i in range(variables_number):
        if curr_cnf.clauses_number() == 0:
            break
        expectations[0]: float = _altered_expectation(curr_cnf, i, -1)
        expectations[1]: float = _altered_expectation(curr_cnf, i, 1)
        if expectations[0] >= expectations[1]:
            result[i] = -1
        for clause_number in range(curr_cnf.get_expression().shape[0]):
            if curr_cnf.get_expression()[clause_number][i] == result[i]:
                curr_cnf.remove_clause(clause_number)
        curr_cnf.reduce_variable(i)
    return result
