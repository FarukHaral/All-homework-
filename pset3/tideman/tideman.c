#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define MAX 9
int preferences[MAX][MAX];
bool locked[MAX][MAX];
typedef struct { int winner; int loser; } pair;
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
int pair_count;
int candidate_count;

bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[]) {
    if (argc < 2) return 1;
    candidate_count = argc - 1;
    for (int i = 0; i < candidate_count; i++) candidates[i] = argv[i + 1];
    int voter_count = get_int("Number of voters: ");
    for (int i = 0; i < voter_count; i++) {
        int ranks[candidate_count];
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks)) return 2;
        }
        record_preferences(ranks);
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
}

bool vote(int rank, string name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(candidates[i], name) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

void record_preferences(int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
}

void sort_pairs(void) {
    for (int i = pair_count - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j+1].winner][pairs[j+1].loser]) {
                pair temp = pairs[j];
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;
            }
        }
    }
}

bool has_cycle(int winner, int loser) {
    if (winner == loser) return true;
    for (int i = 0; i < candidate_count; i++) {
        if (locked[loser][i]) {
            if (has_cycle(winner, i)) return true;
        }
    }
    return false;
}

void lock_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        if (!has_cycle(pairs[i].winner, pairs[i].loser)) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i]) { is_source = false; break; }
        }
        if (is_source) { printf("%s\n", candidates[i]); return; }
    }
}
