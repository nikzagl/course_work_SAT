from cnf import CNF as MyCNF
from pysat.examples.lsu import LSU
from approximations import maxsat_12
from time import time
import numpy as np
from pysat.examples.rc2 import RC2
from pysat.formula import CNF, WCNF
from copy import copy
from random import sample, choice
from threading import Timer


def read_cnf(path: str) -> MyCNF:
    with open(path) as f:
        lines = f.readlines()
        i = 0
        while(lines[i].split()[0] == "c"):
            i += 1
        clauses_number = int(lines[i].split()[3])
        variables_number = int(lines[i].split()[2])
        expression = np.zeros((clauses_number, variables_number))
        for clause_number, line in enumerate(lines[i+1:]):
            expression_line = list(map(int, line.split()))
            for variable_number in expression_line:
                if variable_number > 0:
                    expression[clause_number][variable_number-1] = 1
                elif variable_number < 0:
                    expression[clause_number][-variable_number-1] = -1
        return MyCNF(expression, variables_number)


def generate(filename: str, clauses_number=200, variables_number=30, clause_size=3):
    f = open("benchmarks/" + filename, "w")
    mult = [-1, 1]
    population = list(range(1, variables_number + 1))
    f.write(f"p cnf {variables_number} {clauses_number}\n")
    for i in range(clauses_number):
        smpl = sample(population, clause_size)
        for variable in range(clause_size):
            f.write(f"{choice(mult) * smpl[variable]} ")
        f.write("0\n")
    f.close()


def generate_all():
    for v in range(5, 80):
        for c in range(100, 1000, 100):
            for number in range(1, 6):
                generate(f"bench{v}v{c}c3-{number}.cnf", variables_number=v, clauses_number=c)



def main():

    def interrupt(s):
        return s.interrupt()
    generate_all()
    f = open("logs_MAX_3_SAT_LSU_approx.csv", "w")
    sign = lambda x: 1 if x > 0 else -1
    f.write("Number of variables,Number of clauses,result 1/2,time 1/2,result LSU interrupted\n")
    for v in range(5, 80, 2):
        for c in range(100, 1000, 100):
            for number in range(1, 6):
                start = time()
                a = read_cnf(f"benchmarks/bench{v}v{c}c3-{number}.cnf")
                sat_approx = maxsat_12.solve(a)
                result_approx = a.count_values(sat_approx)
                end = time()
                time_12 = end - start
                cnf = CNF(from_file=f"benchmarks/bench{v}v{c}c3-{number}.cnf")
                lsu_interrupted = LSU(cnf.weighted(), expect_interrupt=True)
                timer = Timer(time_12, interrupt, [lsu_interrupted])
                timer.start()
                lsu_interrupted.solve()
                lsu_interrupted.clear_interrupt()
                sat_interrupted = np.array([sign(x) for x in lsu_interrupted.model])
                result_interrupted = a.count_values(sat_interrupted)
                f.write(f"{v},{c},{result_approx},{time_12},{result_interrupted}\n")
                print(f"{v},{c},{result_approx},{time_12},{result_interrupted}")
    f.close()


if __name__ == "__main__":
    main()
