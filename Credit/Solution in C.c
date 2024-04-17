#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define MAX 8

//prototypes
long getNumber(int *ptype);
int checkSum1(long cardNumber);
int checkSum2(long cardNumber, int sum);
void printResult(int sum, int *ptype);

int main(void)
{
    int type = 0;
    int *ptype = &type;
    int sum = 0;

    //get card number
    long cardNumber = getNumber(ptype);
    //if number = invalid, end program
    if (cardNumber == -1)
    {
        printf("INVALID\n");
        return 0;
    }

    //do checksum
    sum = checkSum1(cardNumber);
    sum = checkSum2(cardNumber, sum);

    //print result
    printResult(sum, ptype);
}

long getNumber(int *ptype)
{
    //this function get a valid card number from the user

    int checkNumber = 0;
    long cardNumber = 0;
    char temp[256];

    //ask user for number until cardNumber is valid

    //get input
    checkNumber = 0;     //reset check
    cardNumber = get_long("Card Number: ");

    sprintf(temp, "%lu", cardNumber);

    //check if American express
    if ((cardNumber / 10000000000000) == 37 || (cardNumber / 10000000000000) == 34)
    {
        *ptype = 1;
        return cardNumber;
    }
    else
    //check if Master Card
    if ((cardNumber / 100000000000000) == 51 || (cardNumber / 100000000000000) == 52 || (cardNumber / 100000000000000) == 53 || (cardNumber / 100000000000000) == 54 || (cardNumber / 100000000000000) == 55)
    {
        *ptype = 2;
        return cardNumber;
    }
    else
    //check if 13 digit visa
    if((cardNumber / 1000000000000) == 4)
    {
        *ptype = 3;
        return cardNumber;
    }
    else
    //check if 16 digit visa
    if((cardNumber / 1000000000000000) == 4)
    {
        *ptype = 4;
        return cardNumber;
    }
    else
    {
        return -1;
    }
}

int checkSum1(long cardNumber)
{
    //this function performs the checksum on the card number

    //vars
    long long mod = 100;
    long long div = 10;
    long long temp = 1;
    long long sum = 0;


    /*================================================
    1.  Multiply every other digit by 2
    2.  starting with the number’s second-to-last digit
    3.  then add those products’ digits together.
    =================================================*/

    for (int i = 0; i < MAX; i++)
    {
        //check if selected number = 0
        if ((cardNumber % mod) / div == 0)
        {
            mod *= 100;
            div *= 100;
            temp = 0;
            continue;
        }

        //get next number
        temp = (cardNumber % mod) / div;

        //multiply by 2
        temp *= 2;

        //check if temp is greater than 9, if so split the two numbers
        if (temp > 9)
        {
            int x = 0, y = 0;
            x = temp / 10;
            y = temp % 10;
            temp = x + y;
        }

        //add onto sum
        sum += temp;

        //increment mod & div by 2 powers of 10
        mod *= 100;
        div *= 100;
    }
    return sum;

}

int checkSum2(long cardNumber, int sum)
{
    /*================================================
    Add the sum to the sum of the digits that weren’t multiplied by 2.
    =================================================*/

    //vars
    long long mod = 10;
    long long div = 1;
    long long temp = 1;

    for (int i = 0; i < MAX; i++)
    {
        //check if selected number = 0
        if ((cardNumber % mod) / div == 0)
        {
            mod *= 100;
            div *= 100;
            temp = 0;
            continue;
        }

        //get next number
        temp = (cardNumber % mod) / div;

        //add onto sum
        sum += temp;

        //increment mod & div by 2 powers of 10
        mod *= 100;
        div *= 100;
    }
    return sum;

}

void printResult(int sum, int *ptype)
{
    //check if sum % 10 = 0
    if ((sum % 10) == 0)
    {
        switch (*ptype)
		{
		    case 1:
            {
                printf("AMEX\n");
                break;
            }
		    case 2:
            {
                printf("MASTERCARD\n");
                break;
            }
		    case 3:
            {
                printf("VISA\n");
                break;
            }
		    case 4:
            {
                printf("VISA\n");
                break;
            }
		    default:
		        break;
        }
    }
    else
    {
        printf("INVALID\n");
    }
}