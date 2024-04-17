import csv
import sys


def main():

    # check the cmd args = 2
    if len(sys.argv) != 3:
        print("Please enter correct args!")

    # Read database file into a variable
    f = open(str(sys.argv[1]), 'r')
    reader = csv.DictReader(f)

    # create dict
    people = []

    # read csv into dict
    for row in reader:
        people.append(row)

    # Read DNA sequence file into a variable
    s = open(str(sys.argv[2]), 'r')
    sequence = s.read()
    # print(sequence[1])

    # read first row into a list
    f.seek(0)
    str_reader = csv.reader(f)
    data = list(str_reader)

    # get longest run for all str's in csv file

    # get length of list of first row
    str_count = len(data[0])

    # create list for logest run results
    results = []

    # loop through all str's in csv file and create of longest run count in str order
    for i in range(1, str_count):
        current_str = data[0][i]
        results.append(longest_match(sequence, current_str))

    # TODO: Check database for matching profiles
    # loop through  all str's for lavender and return true
    for i in range(0, len(people)):
        # reset bool to true for each row
        match = True

        # check if all str counts match
        for j in range(1, str_count):
            if int(results[j - 1]) != int(people[i][data[0][j]]):
                match = False

        # check if we have a match, if TRUE, print name of person
        if match == True:
            print(people[i]['name'])
            break

    # if no match found, print "No Match"
    if match == False:
        print("No Match")

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
