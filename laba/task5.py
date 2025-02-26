def SumList(mass: list[list[float]]) -> float:
    res = 0 
    for line in mass: 
        for i in line: 
            res += i * i 
    return res 

print(SumList([[1, 2], [3, 4]]))
