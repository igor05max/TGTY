line = input()

letters = dict()

for let in line:
    if let not in letters.keys():
        letters[let] = 0
    letters[let] += 1

for let in letters:
    if letters[let] == 1:
        print(let, end=" ")
