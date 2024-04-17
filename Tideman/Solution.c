#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int findStrenghtOfVic(int x);
bool getCycle(int w, int l);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }



    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //loop through candidate[], and check given name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        // if name matches
        if (strcmp(name, candidates[i]) == 0)
        {
            //ranks[] = index of candidates[]
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //loop through ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        //loop through all candidates under i (j)
        for (int j = i + 1; j < candidate_count; j++)
        {
            //updtes pref[][]
            int k = ranks[i];
            int l = ranks[j];
            preferences[k][l]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //iterate though all conbinations
    int i = 0, j = 1, c = candidate_count - 1;
    pair_count = 0;

    while (i != c)
    {
        //if pref[i][j] == pref[j][i] dont add to pairs
        if (preferences[i][j] == preferences[j][i])
        {
            //dont add to pairs array
        }
        else
        {
            //if pref[i][j] > pref[j][i] THEN i = winner, j = loser
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else
            {
                if (preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }

        if (j == c)
        {
            i++;
            j = i + 1;
        }
        else
        {
            j++;
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //bubble sort pairs[]
    pair temp;
    for (int x = 0; x < pair_count - 1; x++)
    {
        for (int y = 0; y < pair_count - x - 1; y++)
        {
            if (findStrenghtOfVic(y + 1) > findStrenghtOfVic(y))
            {
                temp = pairs[y];

                pairs[y] = pairs[y + 1];

                pairs[y + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n = 0; n < pair_count; n ++)
    {
        int w = pairs[n].winner;
        int l = pairs[n].loser;
        if (!getCycle(w, l))
        {
            locked[w][l] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //loop through all rows and columns in locked[ROW][COLUMN] and check for a column of all false
    for (int col = 0; col < candidate_count; col++)
    {
        for (int row = 0; row < candidate_count; row++)
        {
            if (locked[row][col] == true)
            {
                break;
            }
            else if (row == candidate_count - 1)
            {
                printf("%s\n", candidates[col]);
            }
        }
    }
    return;
}

int findStrenghtOfVic(int x)
{
    //this will find and return the victory strength for pairs[x]
    int i = pairs[x].winner;
    int j = pairs[x].loser;

    int str = preferences[i][j] - preferences[j][i];

    return str;
}

bool getCycle(int w, int l)
{
    //this funciton check for a cycle
    if (locked[l][w] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i] == true && getCycle(w, i))
        {
            return true;
        }
    }
    return false;
}