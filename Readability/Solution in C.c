#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//prototypes
int count_letters(string str);
int count_words(string str);
int count_sentences(string str);

int main(void)
{
    //Get input
    string str = get_string("Text: ");

    //count L,W,S
    int letters = count_letters(str);
    int words = count_words(str);
    int sentences = count_sentences(str);

    //printf("W: %d\nS: %d\nL: %d\n", words, sentences, letters);

    //print grade
    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    //round grade
    index = round(index);

    //if grade >= 16 print "Grade 16+"
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        //if grade < 1 print "Before Grade 1"
        if (index < 1)
        {
            printf("Before Grade 1\n");
        }
        else
        {
            //print calculated grade
            printf("Grade %.0f\n", index);
        }
    return 0;
}

int count_letters(string str)
{
    //this function counts the number of letters in str
    int letters = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        //check if upper letter
        if (str[i] >= 65 && str[i] <= 90)
        {
            letters++;
        }
        //check if upper letter
        if (str[i] >= 96 && str[i] <= 122)
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string str)
{
    //this function counts hoow many words are in str (number of spaces)
    int words = 1;

    for (int i = 0; i < strlen(str); i++)
    {
        //check if str[i] is a space
        if (str[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string str)
{
    //this function coutns how many sentences (number of '.' OR '!' OR '?')
    int sentences = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        //check if str[i] is a '.'
        if (str[i] == '.')
        {
            sentences++;
        }
        //check if str[i] is a '!'
        if (str[i] == '!')
        {
            sentences++;
        }
        //check if str[i] is a '?'
        if (str[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}