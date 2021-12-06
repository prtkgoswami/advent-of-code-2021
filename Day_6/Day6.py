from functools import lru_cache


@lru_cache(None)
def recursiveCount(population, day, remaining):
    if day == 0:
        return population

    if remaining == 0:
        current = recursiveCount(population, day - 1, 6)
        newchild = recursiveCount(population, day - 1, 8)
        return current + newchild

    return recursiveCount(population, day - 1, remaining - 1)


with open("./Day6_Input.txt", "r") as f:
    line = f.readline()
school = list(map(int, line.split(',')))

numFishes = sum(recursiveCount(1, 80, fish) for fish in school)
print("# of fishes after 80 Days: " + str(numFishes))

numFishes = sum(recursiveCount(1, 256, fish) for fish in school)
print("# of fishes after 256 Days: " + str(numFishes))
