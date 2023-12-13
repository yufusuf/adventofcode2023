import re
from time import sleep
def check(currs):
    for c in currs:
        if c[2] != 'Z':
            return False
    return True
def check_l(loops):
    for l in loops:
        if l == -1:
            return False
    return True
def gcd(num1, num2):
    res = num1;
    if num2 < num1:
        res = num2
    while res > 0:
        if num1 % res == 0 and num2 % res == 0:
            break
        res -= 1
    return res



with open("input") as f:
    lines = f.readlines()
    rlseq = lines[0].strip()
    nodes = {}

    starters = []

    for line in lines[1:]:
        nodes_list = re.findall("[A-Z]{3}", line)
        nodes[nodes_list[0]] = (nodes_list[1], nodes_list[2])
        if nodes_list[0][2] == 'A':
            starters.append(nodes_list[0])


    steps = 0
    curr  = 'AAA'
    running = True
    while running:
        for s in rlseq:
            if curr == 'ZZZ':
                running = False
                break
            if s == 'R':
                curr = nodes[curr][1]
            else:
                curr = nodes[curr][0]
            steps += 1

    print("part1 ", steps)

    curs = starters.copy()
    steps = 0
    running = True
    loops = [-1]*len(starters)
    while running:
        for s in rlseq:
            if check_l(loops):
                running = False
                break
            if steps > 0:
                for i,c in enumerate(curs):
                    if c[2] == 'Z' :
                        if loops[i] == -1:
                            loops[i] = steps
            if s == 'R':
                for i,c in enumerate(curs):
                    curs[i] = nodes[c][1]
            else:
                for i,c in enumerate(curs):
                    curs[i] = nodes[c][0]

            steps += 1
    res = loops[0] * loops[1] / gcd(loops[0], loops[1]) 
    for num in loops[2:]:
        res = res * num / gcd(res, num)
    print(res)










