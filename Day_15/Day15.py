import sys

# def findMinPath(row, col):
#     # Recursive
#     if row >= len(map) or col >= len(map[0]):
#         return sys.maxsize

#     if row == len(map) - 1 and col == len(map[0]) - 1:
#         return map[-1][-1]

#     c1 = findMinPath(row + 1, col)
#     c2 = findMinPath(row, col + 1)
#     return min(c1, c2) + map[row][col]


def findMinPath(map):
    queue = [(0, 0, 0)]  # (x, y, Cost)
    costs = {}  # {x, y}: Cost
    while True:
        x, y, cost = queue[0]
        if x == len(map) - 1 and y == len(map[0]) - 1:
            return costs[(x, y)]

        queue = queue[1:]

        for newX, newY in [(x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1)]:
            if newX in range(len(map)) and newY in range(len(map[0])):
                newCost = cost + map[newX][newY]
                if (newX, newY) in costs and costs[(newX, newY)] <= newCost:
                    continue
                costs[(newX, newY)] = newCost
                queue.append((newX, newY, newCost))
        queue = sorted(queue)


originalMap = []
with open('./Day15_Input.txt') as inputFile:
    for line in inputFile:
        originalMap.append([int(x) for x in line.strip()])

numNodes = len(originalMap)

# Part 1
print("Minimum Risk Cost: " + str(findMinPath(map=originalMap)))

# Part 2
extendedMap = [[0 for x in range(len(originalMap[0]) * 5)]
               for y in range(len(originalMap) * 5)]
for y in range(len(extendedMap)):
    for x in range(len(extendedMap[0])):
        dist = x // len(originalMap[0]) + y // len(originalMap)
        newval = originalMap[x % len(originalMap[0])][y % len(originalMap)]
        for i in range(dist):
            newval += 1
            if newval == 10:
                newval = 1
        extendedMap[x][y] = newval
print("Minimum Risk Cost: " + str(findMinPath(map=extendedMap)))
