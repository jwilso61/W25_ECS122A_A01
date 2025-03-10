#include <stdio.h>
#include <limits.h>

#define MAX_I 16  // Hardcoded target amount
#define NUM_COINS 3
int COINS[NUM_COINS] = {2, 7, 3};  // Hardcoded denominations

void compute_min_coins(int i, int coins[], int num_coins, int opt[]) {
    opt[0] = 0;  // Base case: 0 coins needed for amount 0

    printf("OPT(0)=0\n");
    printf("Recursive Computation:\n\n");

    // Compute minimum coins for each amount from 1 to i
    for (int amt = 1; amt <= i; amt++) {
        opt[amt] = INT_MAX;  // Initialize with a large number
        int chosen_coin = -1; // To track which coin was used

        printf("OPT(%d) = min(", amt);

        // Try each coin
        for (int j = 0; j < num_coins; j++) {
            if (amt >= coins[j] && opt[amt - coins[j]] != INT_MAX) {
                int candidate = 1 + opt[amt - coins[j]];

                if (candidate < opt[amt]) {
                    opt[amt] = candidate;
                    chosen_coin = coins[j];
                }
            }
            // Print the intermediate calculation
            if (amt >= coins[j]) {
                printf("1 + OPT(%d)", amt - coins[j]);
                if (j < num_coins - 1) printf(", ");
            }
        }

        printf(") = %d", opt[amt]);

        if (chosen_coin != -1) {
            printf(" (use one %d-coin)", chosen_coin);
        }
        
        printf("\n");
    }
}

void write_output_to_file(int i, int opt[]) {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write space-separated values to file
    for (int amt = 0; amt <= i; amt++) {
        fprintf(file, "%d ", opt[amt]);
    }

    fclose(file);
    printf("\nResults written to output.txt\n");
}

int main() {
    int opt[MAX_I + 1];  // Array to store minimum coins needed for each value

    compute_min_coins(MAX_I, COINS, NUM_COINS, opt);
    write_output_to_file(MAX_I, opt);

    return 0;
}

