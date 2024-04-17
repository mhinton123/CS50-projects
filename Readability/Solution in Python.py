import cs50

# calculate the index


def get_index(str):
    length = 0
    letters = 0
    words = 1
    sentences = 0

    # get length of string
    length = len(str)

    # loop through all characters in string
    for i in range(0, length):

        # check if letter
        ch = str[i]
        if ord(ch) >= 65 and ord(ch) <= 90:
            letters = letters + 1

        if ord(ch) >= 97 and ord(ch) <= 122:
            letters = letters + 1

        # check if word
        if str[i] == " ":
            words = words + 1

        # check if sentence
        if str[i] == "!" or str[i] == "?" or str[i] == ".":
            sentences = sentences + 1

    # calculate L and S
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8

    index = round(index)

    return index

# main


# get string
str = cs50.get_string("Text: ")

# calculate index
index = get_index(str)

# print grade
if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade ", index)