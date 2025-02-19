x = float(input())

while x != int(x):
    x = float(str(x)[:-1]) * int(str(x)[-1])

print(x)
