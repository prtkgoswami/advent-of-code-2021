hexMap = {
    '0': '0000', '1': '0001', '2': '0010', '3': '0011', '4': '0100',
    '5': '0101', '6': '0110', '7': '0111', '8': '1000', '9': '1001',
    'A': '1010', 'B': '1011', 'C': '1100', 'D': '1101', 'E': '1110',
    'F': '1111'
}


def getVersionSum(str):
    if str == '' or list(str) == ['0' for x in range(len(str))]:
        return 0

    versionStr = str[:3]
    typeIdStr = str[3:6]
    newStr = ''
    if typeIdStr == '100':
        i = 6
        while str[i] != '0':
            i += 5
        i += 5
        newStr = str[i:]
    else:
        lenTypeId = str[6]
        if lenTypeId == '0':
            newStr = str[22:]
        elif lenTypeId == '1':
            newStr = str[18:]

    return int(versionStr, 2) + getVersionSum(newStr)


def evaluateExpression(str):
    operator = []
    literals = []
    if str == '' or list(str) == ['0' for x in range(len(str))]:
        return

    versionStr = str[: 3]
    typeIdStr = str[3: 6]
    typeId = int(typeIdStr, 2)

    if typeId != 4:
        lenTypeId = str[6]

        if typeId == 0:
            if lenTypeId == '0':
                pktSize = int(str[7: 22], 2)

            pass
        elif typeId == 1:
            # Product
            pass
        elif typeId == 2:
            # Minimum
            pass
        elif typeId == 3:
            # Maximum
            pass
        elif typeId == 5:
            # Greater Than
            pass
        elif typeId == 6:
            # Less Than
            pass
        elif typeId == 7:
            # Equal To
            pass

    else:
        literalStart = 6
        literal = ''
        while str[literalStart] != '0':
            literal += str[literalStart + 1:literalStart + 5]
            literalStart += 5
        return int(literal, 2)


transmissionStr = '""'
with open('./Day16_Input.txt') as InputFile:
    transmissionStr = next(InputFile).strip()

binaryStr = ''
for ch in transmissionStr:
    binaryStr += hexMap[ch]

# print(transmissionStr)
# print(binaryStr)
print(getVersionSum(binaryStr))
