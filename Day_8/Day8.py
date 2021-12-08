
def count1478(outputValues):
    # Num Unique Digits:
    # 1 -> 2, 4 -> 4, 7 -> 3, 8 -> 7
    count = 0
    for opVal in outputValues:
        for val in opVal:
            if len(val) in [2, 4, 3, 7]:
                count += 1
    return count


def decode(pattern):
    map = {}
    revMap = {}
    lenMap = {5: [], 6: []}

    for i in range(0, len(pattern)):
        pattern[i] = ''.join(sorted(pattern[i]))

    # For 1, 4, 7, 8
    for s in pattern:
        if len(s) == 2:
            map[s] = 1
            revMap[1] = set(s)
        elif len(s) == 4:
            map[s] = 4
            revMap[4] = set(s)
        elif len(s) == 3:
            map[s] = 7
            revMap[7] = set(s)
        elif len(s) == 7:
            map[s] = 8
            revMap[8] = set(s)

    for s in pattern:
        if len(s) in [5, 6]:
            lenMap[len(s)].append(s)

    # For Len 6 => 0, 6, 9
    for s in lenMap[6]:
        charset = set(s)
        if set.intersection(revMap[1], charset) != revMap[1]:
            map[s] = 6
            revMap[6] = charset
        elif set.intersection(revMap[4], charset) != revMap[4]:
            map[s] = 0
            revMap[0] = charset
        else:
            map[s] = 9
            revMap[9] = charset

    # For Len 5 => 2, 3, 5
    for s in lenMap[5]:
        charset = set(s)
        if set.intersection(revMap[1], charset) == revMap[1]:
            map[s] = 3
            revMap[3] = charset
        elif set.intersection(revMap[6], charset) == charset:
            map[s] = 5
            revMap[5] = charset
        else:
            map[s] = 2
            revMap[2] = charset

    return map


signalPatterns = []
outputValues = []
with open('./Day8_Input.txt', 'r') as f:
    for line in f:
        parts = line.strip().split(' | ')
        signalPatterns.append(parts[0].split(' '))
        outputValues.append(parts[1].split(' '))

# Part 1
print("Number of times 1, 4, 7 or 8 appears: " + str(count1478(outputValues)))

# Part 2
opSum = 0
for i in range(0, len(signalPatterns)):
    map = decode(signalPatterns[i])
    num = 0
    for output in outputValues[i]:
        num = num * 10 + map[''.join(sorted(output))]
    opSum += num

print("Sum of Output Values: " + str(opSum))
