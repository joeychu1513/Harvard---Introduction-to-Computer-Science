import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable

    # DNA list, each item is a dict
    dna_database = []
    combination = []

    database_cd = sys.argv[1]

    with open(database_cd, "r") as d:
        database = csv.DictReader(d)
        for row in database:
            dna_database.append(row)

    with open(database_cd, "r") as d:
        combination_read = csv.reader(d)
        row1 = next(combination_read)
        for item in row1:
            if item == "name":
                continue
            else:
                combination.append(item)

    # TODO: Read DNA sequence file into a variable

    test_dna_cd = sys.argv[2]

    with open(test_dna_cd, "r") as t:
        # test_dna = []
        read = csv.reader(t)
        row1 = next(read)
        test_dna = row1[0]
        # for row in read:
        #     test_dna.append(row)

    # TODO: Find longest match of each STR in DNA sequence

    suspect = {}

    for item in combination:
        longest = longest_match(test_dna, item)
        suspect[item] = longest

    # TODO: Check database for matching profiles

    found = 0

    for person in dna_database:

        count_of_same = 0

        for item in combination:

            if int(person[item]) == int(suspect[item]):
                count_of_same += 1
                if count_of_same < len(combination):
                    continue
                else:
                    print(person["name"])
                    found += 1
                    break
            else:
                break

    if found == 0:
        print("No match")
    
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
