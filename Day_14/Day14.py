def calculateScore(pairMap):
    countMap = {}
    maxCount, minCount = 0, 0
    for pair, val in pairMap.items():
        if pair[0] in countMap:
            countMap[pair[0]] += val
        else:
            countMap[pair[0]] = val
        if pair[1] in countMap:
            countMap[pair[1]] += val
        else:
            countMap[pair[1]] = val

    countMap[polymerTemplate[0]] -= 1
    countMap[polymerTemplate[-1]] -= 1

    for key in countMap.keys():
        countMap[key] = int(countMap[key] / 2)

    countMap[polymerTemplate[0]] += 1
    countMap[polymerTemplate[-1]] += 1

    for val in countMap.values():
        if minCount == 0:
            minCount = val
        else:
            minCount = min(minCount, val)
        maxCount = max(maxCount, val)

    return maxCount - minCount


def polymerize(templateMap, pairInsertions, maxSteps):
    for _ in range(maxSteps):
        newTemplateMap = {}
        for pair, val in templateMap.items():
            if pair in pairInsertions:
                p1 = pair[0] + pairInsertions[pair]
                p2 = pairInsertions[pair] + pair[1]
                if p1 in newTemplateMap:
                    newTemplateMap[p1] += val
                else:
                    newTemplateMap[p1] = val
                if p2 in newTemplateMap:
                    newTemplateMap[p2] += val
                else:
                    newTemplateMap[p2] = val
        templateMap = newTemplateMap
    score = calculateScore(templateMap)
    return score


pairInsertions = {}
templateMap = {}

with open("./Day14_Input.txt") as InputFile:
    polymerTemplate = next(InputFile).strip()
    for i in range(0, len(polymerTemplate) - 1):
        pat = polymerTemplate[i:i+2]
        if pat in templateMap:
            templateMap[pat] += 1
        else:
            templateMap[pat] = 1

    next(InputFile)

    for line in InputFile:
        line = line.strip()
        tokens = line.split(' -> ')
        pairInsertions[tokens[0]] = tokens[1]

# Part 1
diffMaxMin = polymerize(templateMap=templateMap,
                        pairInsertions=pairInsertions, maxSteps=10)
print("Difference between Max Frequency & Min Frequency after 10 Steps: " + str(diffMaxMin))

# Part 2
diffMaxMin = polymerize(templateMap=templateMap,
                        pairInsertions=pairInsertions, maxSteps=40)
print("Difference between Max Frequency & Min Frequency after 40 Steps: " + str(diffMaxMin))
