pairs = []


def createList(line):
    pairs = []
    level = 0
    for ch in line:
        if ch == "[":
            level += 1
        elif ch == "]":
            level -= 1
        elif ch != ",":
            pairs.append([int(ch), level])
    return pairs


def add(pair1, pair2):
    sum = []

    for item in pair1:
        item[1] += 1
        sum.append(item)

    for item in pair2:
        item[1] += 1
        sum.append(item)

    return sum


def reducePair(pair):
    loopFlag = True
    while loopFlag:
        loopFlag = False
        length = len(pair)
        hasExploded = False
        for i in range(length):
            if pair[i][1] > 4:
                if i > 0:
                    pair[i - 1][0] += pair[i][0]
                if i + 1 < length - 1:
                    pair[i + 2][0] += pair[i + 1][0]
                pair.pop(i)
                pair[i][0] = 0
                pair[i][1] -= 1
                hasExploded = True
                loopFlag = True
                break
        if not(hasExploded):
            for i in range(length):
                if pair[i][0] > 9:
                    NewL = pair[i][0]//2
                    NewR = pair[i][0]//2 + pair[i][0] % 2
                    pair[i][0] = NewL
                    pair[i][1] += 1
                    pair.insert(i + 1, [NewR, pair[i][1]])
                    loopFlag = True
                    break
    return pair


def calculateSumMagnitude(pairs):
    sumPairs = []
    for pair in pairs:
        sumPairs.append(pair)
    for l in range(4):
        newPairs = []
        level = 4 - l
        i = 0
        while i < len(sumPairs) - 1:
            if sumPairs[i][1] == level and sumPairs[i + 1][1] == level:
                newPairs.append(
                    [(3 * sumPairs[i][0] + 2 * sumPairs[i + 1][0]), level - 1])
                i += 2
            else:
                newPairs.append(sumPairs[i])
                i += 1
        if i == len(sumPairs) - 1:
            newPairs.append(sumPairs[i])
        sumPairs = newPairs
    return sumPairs[0][0]


def createPairs():
    pairs.clear()
    # Take Input & Cretae Pairs
    with open('./Day18_Input.txt') as InputFile:
        for line in InputFile:
            pairs.append(createList(line.strip()))


# Part 1
createPairs()
# Add & Reduce Pairs
sumPair = pairs[0]
for pair in pairs[1:]:
    # Add Pairs
    sumPair = add(pair1=sumPair, pair2=pair)

    # Reduce Pairs
    sumPair = reducePair(pair=sumPair)

# Calculate Magnitude of Sum
print("Sum Magnitude of all Pairs: " + str(calculateSumMagnitude(sumPair)))

# Part 2
createPairs()
maxSum = 0
for i in range(len(pairs)):
    for j in range(len(pairs)):
        createPairs()
        if i != j:
            # Add Pairs
            sumPair = add(pair1=pairs[i], pair2=pairs[j])

            # Reduce Pairs
            sumPair = reducePair(pair=sumPair)

            sumMag = calculateSumMagnitude(sumPair)

            maxSum = max(maxSum, sumMag)
print('Max Sum Magnitude of 2 Pairs: ' + str(maxSum))
