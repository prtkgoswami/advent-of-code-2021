_errorScoreMap = {')': 3, ']': 57, '}': 1197, '>': 25137}
_completionScoreMap = {'(': 1, '[': 2, '{': 3, '<': 4}


def getErrorScore(line):
    stack = []
    for ch in line:
        if ch in ['(', '[', '{', '<']:
            stack.append(ch)
        elif (len(stack) == 0 and ch in [')', ']', '}', '>'])\
                or (ch == ')' and len(stack) > 0 and stack[-1] != '(')\
                or (ch == ']' and len(stack) > 0 and stack[-1] != '[')\
                or (ch == '}' and len(stack) > 0 and stack[-1] != '{')\
                or (ch == '>' and len(stack) > 0 and stack[-1] != '<'):
            return _errorScoreMap[ch]
        else:
            stack.pop()
    return 0


def getCompletionScore(line):
    stack = []
    for ch in line:
        if ch in ['(', '[', '{', '<']:
            stack.append(ch)
        else:
            stack.pop()
    score = 0
    while len(stack) > 0:
        score = score * 5 + _completionScoreMap[stack[-1]]
        stack.pop()
    return score


def getInput():
    lines = []
    with open('./Day10_Input.txt') as inputFile:
        for line in inputFile:
            line = line.rstrip()
            lines.append(line)
    return lines


lines = getInput()
incompleteLines = []

# Part 1
errorScore = 0
for line in lines:
    score = getErrorScore(line)
    if score == 0:
        incompleteLines.append(line)
    errorScore += score
print("Corruption Score: " + str(errorScore))

# part 2
completionScores = []
for line in incompleteLines:
    completionScores.append(getCompletionScore(line))
completionScores.sort()
midIndex = (len(completionScores) - 1) / 2
print("Middle Completion Score: " + str(completionScores[int(midIndex)]))
