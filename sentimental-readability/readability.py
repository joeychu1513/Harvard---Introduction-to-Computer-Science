# TODO


from cs50 import get_string


def main():

    to_test = get_string("to_test: ")

    n_of_letter = count_letter(to_test)
    n_of_word = count_word(to_test)
    n_of_sentense = count_sentense(to_test)

    L = 100 * n_of_letter / n_of_word
    S = 100 * n_of_sentense / n_of_word
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")


def count_letter(text):

    count = 0
    length = len(text)

    for i in range(length):
        if text[i].isalpha() is True:
            count += 1

    return count


def count_word(text):

    # depend on space
    count = 1
    length = len(text)

    for i in range(length):
        if text[i] == " ":
            count += 1

    return count


def count_sentense(text):

    count = 0
    length = len(text)

    for i in range(length):
        if text[i] in [".", "!", "?"]:
            count += 1
    return count


main()