def getPaths(adjList, path, src):
    if src.islower() and src in path[:-1]:
        return 0

    if src == 'end':
        return 1

    count = 0
    for dst in adjList[src]:
        path.append(dst)
        count += getPaths(adjList, path, dst)
        path.pop()
    return count


def getModifiedPaths(adjList, path, src, smallTwiceVisited):
    if src.islower() and smallTwiceVisited and src in path[:-1]:
        return 0

    if src == 'end':
        return 1

    if src.islower() and src in path[:-1]:
        smallTwiceVisited = True

    count = 0
    for dst in adjList[src]:
        path.append(dst)
        if dst != 'start':
            count += getModifiedPaths(adjList, path, dst, smallTwiceVisited)
        path.pop()
    return count


def getInput():
    adjList = {}
    with open('./Day12_Input.txt') as InputFile:
        for line in InputFile:
            if '\n' in line:
                line = line.strip()
            token = line.split('-')

            if token[0] in adjList.keys():
                adjList[token[0]].append(token[1])
            else:
                adjList[token[0]] = [token[1]]

            if token[1] in adjList.keys():
                adjList[token[1]].append(token[0])
            else:
                adjList[token[1]] = [token[0]]
    return adjList


adjList = getInput()

# part 1
countPath = getPaths(adjList, ['start'], 'start')
print('Number of Paths from start -> end = ' + str(countPath))

# part 2
countPath = getModifiedPaths(adjList, ['start'], 'start', False)
print('Number of Paths from start -> end visiting any 1 small cave twice = ' + str(countPath))
