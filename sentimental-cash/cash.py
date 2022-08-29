# TODO

from cs50 import get_float
from math import floor


while True:

    owed = get_float("owed: ") * 100
    if owed >= 0:
        break

n_of_25 = floor(owed / 25)
n_of_10 = floor((owed - n_of_25 * 25) / 10)
n_of_5 = floor((owed - n_of_25 * 25 - n_of_10 * 10) / 5)
n_of_1 = floor((owed - n_of_25 * 25 - n_of_10 * 10 - n_of_5 * 5) / 1)

print(n_of_25 + n_of_10 + n_of_5 + n_of_1)