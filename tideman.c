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
    bool check_cycle(int winner, int loser);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            int pref_cand = ranks[i];
            int less_pref_cand = ranks[j];
            preferences[pref_cand][less_pref_cand] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    bool swap = false;
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int win_str_1 = preferences[pairs[j].winner][pairs[j].loser];
            int lose_str_1 = preferences[pairs[j].loser][pairs[j].winner];
            int strength_1 = win_str_1 - lose_str_1;

            int win_str_2 = preferences[pairs[j+1].winner][pairs[j+1].loser];
            int lose_str_2 = preferences[pairs[j+1].loser][pairs[j+1].winner];
            int strength_2 = win_str_2 - lose_str_2;

            if(strength_1 < strength_2)
            {
                int pair1_win = pairs[j].winner;
                int pair1_lose = pairs[j].loser;

                pairs[j].winner = pairs[j+1].winner;
                pairs[j].loser = pairs[j+1].loser;

                pairs[j+1].winner = pair1_win;
                pairs[j+1].loser = pair1_lose;

                swap = true;
            }
        }
        if(swap != true)
        {
            break;
        }
    }
    return;
}

// check if locking a pair create a cycle
bool check_cycle(int winner, int loser)
{
    if(winner == loser)
    {
        return true;
    }

    for(int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (check_cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0;i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if(check_cycle(winner, loser) == false)
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool x = false;
    int winner;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                break;
            }
            if (j == candidate_count - 1)
            {
                x = true;
                winner = i;
                break;
            }
        }
        if (x == true)
        {
            break;
        }
    }
    printf("%s\n", candidates[winner]);
    return;
}
