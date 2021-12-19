
def launchProbe(initialVelocity, target):
    # return Has Reached Target, max Y Position
    posX, posY = [0, 0]
    velX, velY = initialVelocity
    maxY = 0
    while posX <= max(target['x']) \
            and not (velX == 0 and posX < min(target['x'])) \
            and not (posX > min(target['x']) and posY < min(target['y'])):
        posX += velX
        posY += velY

        if velX > 0:
            velX -= 1
        elif velX < 0:
            velX += 1
        velY -= 1

        maxY = max(posY, maxY)

        if posX in range(min(target['x']), max(target['x']) + 1) \
                and posY in range(min(target['y']), max(target['y']) + 1):
            return True, maxY

    return False, maxY


targetLimits = {}
with open('./Day17_Input.txt') as InputFile:
    str = next(InputFile).strip().split(': ')[1]
    limits = [lims[2:].split('..') for lims in str.split(', ')]
    xLimits = [int(x) for x in limits[0]]
    yLimits = [int(x) for x in limits[1]]
    targetLimits['x'] = xLimits
    targetLimits['y'] = yLimits

# print(targetLimits)

maxYPos = 0
velocityForMaxY = []
validVelocityCount = 0
for x in range(1, max(targetLimits['x']) * 2):
    for y in range(min(targetLimits['y']), max(targetLimits['x'])):
        hasReachedTarget, currMaxYPos = launchProbe(
            [x, y], target=targetLimits)

        if hasReachedTarget:
            validVelocityCount += 1
            if currMaxYPos > maxYPos:
                maxYPos = currMaxYPos

print(maxYPos)
print(validVelocityCount)
