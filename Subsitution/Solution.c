#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 26

//prototypes
int getCypher(int argc, string argv[], char cypher[]);
void convertCypher(char alphabet[], char cypher[], char plainText[], char cypherText[]);

int main(int argc, string argv[])
{
    //arrays
    char alphabet[MAX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char cypherText[256];
    char plainText[256];
    char cypher[MAX];



    //get cypher and return 1 if cypher is invalid
    if (getCypher(argc, argv, cypher) == 1)
    {
        return 1;
    }

    //convert plaintext to cypher
    convertCypher(alphabet, cypher, plainText, cypherText);

    return 0;
}

int getCypher(int argc, string argv[], char cypher[])
{

    //this function checks the cypherkey is valid

    char cypherCheck[MAX];
    int cyphIndex = 0;

    //check there is no more than one argument (cyper key)
    if (argc > 2 || argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //check valid key
    if (strlen(argv[1]) != MAX)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        //copy argv[1] to cypher[]
        strncpy(cypher, argv[1], MAX);
        printf("cypher = %s\n", cypher);
        //check contains each letter once
        for (int i = 0; i < MAX; i++)
        {
            //convert to uppercase
            cypher[i] = toupper(cypher[i]);

            //check it is a letter
            if ((int)cypher[i] < 65 || (int)cypher[i] > 90)
            {
                printf("key contains special chars\n");
                return 1;
            }

            //loop through array to check if letter exists
            for (int j = 0; j < MAX; j++)
            {
                if (cypherCheck[j] == cypher[i])
                {
                    printf("invalid key\n");
                    return 1;
                }
            }
            //if not
            //store letter in array
            //move index of array +1 to store next char
            cypherCheck[cyphIndex] = cypher[i];
            cyphIndex++;
        }
    }
    return 0;
}

void convertCypher(char alphabet[], char cypher[], char plainText[], char cypherText[])
{
    //this gets plain text from the user, then converts it to cyphertext

    //get plaintext from user
    plainText = get_string("plaintext: ");
    int j = 0;
    int k = 0;

    //loop through plainText[] (i)
    for (int i = 0, x = 0; i < strlen(plainText); i++)
    {
        //check if plainText[i] != to letter
        int tmp = toupper(plainText[i]);
        if (tmp < 65 || tmp > 90)
        {
            //copy special char to cypherText[i]
            cypherText[x] = plainText[i];
            x++;
        }
        else
            //check if lowercase
            if (plainText[i] >= 97 && plainText[i] <= 122)
            {
                //convert plainText[i] to uppercase
                plainText[i] = toupper(plainText[i]);
                //loop through alphabet[] (j)
                for (j = 0; j < MAX; j++)
                {
                    //once found letter, break loop to get correct index for cypher[j]
                    if (plainText[i] == alphabet[j])
                    {
                        break;
                    }
                }
                //change plaintext char to cyher char
                cypherText[i] = cypher[j];
                //change back to lower case
                cypherText[i] = tolower(cypherText[i]);
                x++;
            }
            else
            {
                //must be uppercase

                //loop through alphabet[] (k)
                for (k = 0; k < MAX; k++)
                {
                    //once found letter, break loop to get correct index for cypher[j]
                    if (plainText[i] == alphabet[k])
                    {
                        break;
                    }
                }
                //change plaintext char to cyher char
                cypherText[i] = cypher[k];
                x++;
            }
    }
    //print out cyphertext
    printf("ciphertext: %s", cypherText);
    printf("\n");
}