def countAfterFold(paper, folds, numFolds):
    for fold in folds[:numFolds]:
        if 'y' in fold[0]:
            top = int(fold[1]) - 1
            bottom = int(fold[1]) + 1
            while top >= 0 and bottom < len(paper):
                rowTop, rowBottom = paper[top], paper[bottom]
                top -= 1
                bottom += 1
                for i in range(0, len(rowBottom)):
                    if rowBottom[i] == '#':
                        rowTop[i] = '#'
            paper = paper[:int(fold[1])]

        elif 'x' in fold[0]:
            left = int(fold[1]) - 1
            right = int(fold[1]) + 1
            while left >= 0 and right < len(paper[0]):
                for row in paper:
                    if row[right] == '#':
                        row[left] = '#'
                left -= 1
                right += 1
            paper = [row[:int(fold[1])] for row in paper]

    return paper


def getInput():
    dots = []
    folds = []
    dotInput = True
    maxX = 0
    maxY = 0
    with open("./Day13_Input.txt") as inputFile:
        for line in inputFile:
            line = line.strip()
            if line == "":
                dotInput = False
                continue

            if dotInput:
                tokens = line.split(',')
                dots.append([int(tokens[0]), int(tokens[1])])
                maxX = max(maxX, int(tokens[0]))
                maxY = max(maxY, int(tokens[1]))
            else:
                tokens = line.split('=')
                folds.append([tokens[0], tokens[1]])
    return {"dots": dots, "folds": folds, "X-Limit": maxX, "Y-Limit": maxY}


input = getInput()
dots = input["dots"]
folds = input["folds"]
xLimit = input["X-Limit"]
yLimit = input["Y-Limit"]

paper = []
for r in range(0, yLimit + 1):
    paper.append(['.' for c in range(0, xLimit + 1)])

for dot in dots:
    paper[dot[1]][dot[0]] = '#'

# Part 1
paper = countAfterFold(paper, folds, 1)
numDots = 0
for row in paper:
    for data in row:
        if data == '#':
            numDots += 1
print("Number of Dots after 1st Fold: " + str(numDots))


# Part 2
paper = countAfterFold(paper, folds, len(folds))
print("After All Folds:")
for row in paper:
    for data in row:
        print(data, end="")
    print()
