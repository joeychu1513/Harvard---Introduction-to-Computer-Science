# TODO

from cs50 import get_int


def print_hash(remaining_height, original_height):

    # first case
    if remaining_height == 1:
        print(" " * (original_height - 1), end="")
        print("#")
        return

    else:

        print_hash(remaining_height - 1, original_height)
        print(" " * (original_height - remaining_height), end="")
        print("#" * remaining_height)


while True:

    height = get_int("what is the height? ")
    if height in range(1, 9):
        break

print_hash(height, height)

