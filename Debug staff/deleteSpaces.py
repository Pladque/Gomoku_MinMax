f = open("boards with rpoblems.txt", 'r')
f2 = open("boards with rpoblems wtihout spaces.txt", 'w')

for line in f.readlines():
    f2.write(line.replace(" ", ""))