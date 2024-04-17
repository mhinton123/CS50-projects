# check input function
def get_card_num(card_num):

    # get first two chars
    first_2 = card_num[0] + card_num[1]

    # check if a valid number

    # check card is AMEX
    if len(card_num) == 15:
        if first_2 == "34" or first_2 == "37":
            type = "AMEX"
            return type

    # check if card is MASTERCARD
    if len(card_num) == 16:
        if first_2 == "51" or first_2 == "52" or first_2 == "53" or first_2 == "54" or first_2 == "55":
            type = "MASTERCARD"
            return type

    # check if VISA
    if len(card_num) == 13 or len(card_num) == 16:
        if first_2[0] == "4":
            type = "VISA"
            return type

    type = "INVALID"
    return type

# check sum function


def check_sum(card_num):

    # 1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
    # find second from last
    length = len(card_num) - 2
    digit = card_num[length]
    digit = int(digit)
    sum1 = 0

    # loop until at the start of the number
    while length >= 0:

        # mutiply digit by 2
        digit = digit * 2

        # check if digit is greater than 9
        if int(digit) > 9:
            # if so, split digit and add them together  - i.e (12 -> 1 + 2)
            temp = str(digit)
            digit = int(temp[1]) + 1
        # add number to sum
        sum1 = sum1 + digit

        # move digit -2 elements
        length = length - 2
        digit = card_num[length]
        digit = int(digit)

    # 2.Add the sum to the sum of the digits that weren’t multiplied by 2.
    length = len(card_num) - 1
    digit = card_num[length]
    digit = int(digit)
    sum2 = 0

    # loop until at the start of the number
    while length >= 0:

        # add number to sum
        sum2 = sum2 + digit

        # move digit -2 elements
        length = length - 2
        digit = card_num[length]
        digit = int(digit)

    # add boith sums together
    res = sum1 + sum2

    # check if num ends in 0
    if res % 10 == 0:
        return True
    else:
        return False


# main
card_num = input("Number: ")

# check input
type = get_card_num(card_num)

if get_card_num(card_num) == "INVALID":
    print("INVALID")
else:
    # check sum
    if check_sum(card_num) == True:
        print(type)
    else:
        print("INVALID")