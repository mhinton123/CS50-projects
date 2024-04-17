#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Points assigned to each letter of the alphabet
//              a  b  c  d  e  f  g  h  i  j  k  l  m  n  o  p  q   r  s  t  u  v  w  x  y  z
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    //if tie, print tie
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
        //if 1 < 2 player 1 wins
        if (score1 > score2)
        {
            printf("Player 1 wins!\n");
        }
        else
        {
            printf("Player 2 wins!\n");
        }
}

int compute_score(string word)
{
    int score = 0;
    int diff = 0;

    //loop through array
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        //convert char to upper
        word[i] = toupper(word[i]);

        //if not a letter ASCII range, score 0
        if ((int)word[i] < 65 || (int)word[i] > 90)
        {
            score += 0;
        }
        else
        {
            //get diff from A
            diff = (int)word[i] - 65;
            score += POINTS[diff];
        }
    }
    return score;
}
