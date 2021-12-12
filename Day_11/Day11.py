from copy import deepcopy


def flash(board, row, col, flashboard):
    if row < 0 or row >= 10 or col < 0 or col >= 10 or flashboard[row][col]:
        return

    board[row][col] += 1
    if board[row][col] > 9:
        flashboard[row][col] = True
        board[row][col] = 0
        # Bottom
        flash(board, row + 1, col, flashboard)
        # Top
        flash(board, row - 1, col, flashboard)
        # Right
        flash(board, row, col + 1, flashboard)
        # Left
        flash(board, row, col - 1, flashboard)
        # Bottom - Right
        flash(board, row + 1, col + 1, flashboard)
        # Bottom - Left
        flash(board, row + 1, col - 1, flashboard)
        # Top - Left
        flash(board, row - 1, col + 1, flashboard)
        # Top - Left
        flash(board, row - 1, col - 1, flashboard)


def simulateFlashing(board):
    flashCount = 0
    for step in range(1, 101):
        flashboard = [[False for _ in range(0, 10)] for _ in range(0, 10)]
        for row in range(0, 10):
            for col in range(0, 10):
                flash(board, row, col, flashboard)

        currFlashCount = 0
        for row in range(0, 10):
            for col in range(0, 10):
                if board[row][col] == 0:
                    currFlashCount += 1
        flashCount += currFlashCount
    return flashCount


def simultaneousFlashStep(board):
    step = 0
    while True:
        step += 1
        flashboard = [[False for _ in range(0, 10)] for _ in range(0, 10)]
        for row in range(0, 10):
            for col in range(0, 10):
                flash(board, row, col, flashboard)

        currFlashCount = 0
        for row in range(0, 10):
            for col in range(0, 10):
                if board[row][col] == 0:
                    currFlashCount += 1

        if currFlashCount == 100:
            return step


def getInput():
    board = []
    with open("./Day11_input.txt") as inputFile:
        for line in inputFile:
            if '\n' in line:
                line = line.strip()
            board.append([int(x) for x in line])
    return board


board = getInput()
copyBoard = deepcopy(board)

# Part 1
print("Number of Flashes in 100 Steps: " + str(simulateFlashing(board)))

# Part 2
print("First Synchronous Flash occurs at: " +
      str(simultaneousFlashStep(copyBoard)))
