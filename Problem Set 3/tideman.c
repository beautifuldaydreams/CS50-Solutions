#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
bool lock = true;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

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
    
    // for (int i = 0; i < pair_count; i++)
    // {
    //     printf("winner: %i\n", pairs[i].winner);
    //     printf("loser: %i\n", pairs[i].loser);
    //     printf("\n");
    // }
    
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(name, candidates[x]) == 0)
        {
            ranks[rank] = x;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int x = 0; x < candidate_count - 1; x++)
    {
        for (int j = 1; j < candidate_count; j++)
        {
            if (x != j)
            {
                preferences[ranks[x]][ranks[j]] += 1;                
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ((i != j) && preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                pair_count += 1;
                k++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            int curr = preferences[pairs[j].winner][pairs[j].loser];
            int next = preferences[pairs[j+1].winner][pairs[j+1].loser];
            pair curr_pair = pairs[j];
            pair next_pair = pairs[j+1];
            if (curr < next)
            {
                pairs[j] = next_pair;
                pairs[j+1] = curr_pair;
            }
        }
    }
    return;
}

void check_lock(int x)
{
    if (x == 0)
    {
        return;
    }

    bool sub_lock[x];
    int r = 0;

    for (int i = 0; i < x; i++)
    {
        sub_lock[i] = false;
    }

    // checks all the submatrixes up to a single square using recursion
    check_lock(x - 1);

    for (int i = 0; i < x; i++)
    {
        for (int k = 0; k < x; k++)
        {
            if (locked[i][k] == true)
            {
                sub_lock[i] = true;
            }
        }
    }

    for (int i = 0; i < x; i++)
    {
        if (sub_lock[i] == true)
        {
            r++;
        }
    }

    // if the rank is max the lock is canceled
    if (r == x)
    {
        lock = false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        check_lock(candidate_count);
        // if the validateLock function found a cycle we reverse the lock
        if (!lock)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        lock = true;
    }
}

// Print the winner of the election
void print_winner(void)
{
    int score;
    for (int i = 0; i < candidate_count; i++)
    {
        score = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                score++;
            }
        }
        if (score == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

