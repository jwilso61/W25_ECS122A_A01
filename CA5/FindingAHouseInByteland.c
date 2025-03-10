
/*
board of R×C cells, R:rows & C:columns.
ADA at (1, 1). ADA home at (R,C), ADA is going home.
Cell (1, 1) = NW most cell. Cell (R,C) = SE most cell.

From cell (i, j) ADA can move to an adjacent cell (i+1, j), (i−1, j), (i, j+1) or (i, j−1), with constraints:

- ADA has to be on one of the R×C cells.
- "empty" cells take 1 second regardless of the type of cell ADA is previously in.
- "rock"  cells are impassable, ADA cannot go to these cells.
- "muddy" cells take ADA between 2 and 5 seconds to reach them. Seconds is always an integer.
- "spiky" cells can only be walked over h times. Fail if (h+1)th spiky cell is stepped on. It takes 1 second to reach a spiky cell.
- “Teleport” cells teleport to a specifically chosen teleport cell in 1 second as described:
Ex, assume that ADA stepped on teleport cell (i, j). Then, there are five options:
• Do not use the teleport portal
• Use portal and in 1 second, move to teleport cell (k, j) with the maximum possible k; i.e., move to the south-most teleport cell in column j.
• Use portal and in 1 second, move to teleport cell (k, j) with the minimum possible k; i.e., move to the north-most teleport cell in column j.
• Use portal and in 1 second, move to teleport cell (i, k) with the maximum possible k; i.e., move to the east-most teleport cell in row i.
• Use portal and in 1 second, move to teleport cell (i, k) with the minimum possible k; i.e., move to the west-most teleport cell in row i.

Find shortest time path, from (1, 1) to (R,C). Need for each cell (i, j), the shortest time to reach (i, j). 
She already knows how to use this information to construct all shortest paths and – perhaps more importantly – a random shortest path. 
Any shortest time path works.

Input
First line, integer I = number of test instances. 

Each test instance consists of multiple lines:
• line 1 = three space-separated integers R,C, h. R subsequent lines follow.
• The following R lines contain C space-separated integers denoting the types of the cells in row-major order. 
The jth integer in the ith row is the type of the cell (i, j). We denote it by grid(i, j).
• If grid(i, j) = 1, then cell (i, j) is an empty cell,
• If grid(i, j) ∈ [2, 5] then it is a muddy cell that takes ADA grid(i, j) seconds to reach,
• If grid(i, j) = 0, then it is a rocky cell,
• If grid(i, j) = −1, then it is a teleport cell,
• If grid(i, j) = −2, then it is a spiky cell.

Output
Compute result, an R×C matrix where result(i, j) denotes the minimum amount of time ADA needs
to reach cell (i, j) from (1, 1). If (i, j) cannot be reached from (1, 1), then output -1 instead.
Print the matrix as R lines where each line contains C space separated integers. 
These integers should be the elements of the result matrix in row-major order.

Constraints
Each input file contains at most 11 test instances. In a single input file, the total number of cells across
all test instances is at most 4E6. The time limit (for all test instances in a single file) is 3 seconds.
Each test instance satisfies the following additional constraints:
• Cell (1, 1) is empty, i.e., grid(1, 1) = 1
• 1 ≤ R,C ≤ 1000
• 0 ≤ h ≤ 10
• Sum of R·C across all instances is at most 4E6

Test Cases
Program will be evaluated on 10 test files. Passing all the instances within a file will earn 0.8 points. 
If program output is incorrect for >=1 instances within a file, 0 points for that file.

Subtasks
1). In 60% of test files, each cell is empty or rock. In a third of those test files, R and C are at <= 10 for each test instance.
2). In 20% of other test files, each cell is empty, rock, muddy, or teleport. That is, there are no spiky cells in those two test files.
3). In the remaining 20% of test files, all types of cells are present.
*/

#include <stdio.h>

#define MAX_R 1000
#define MAX_C 1000
#define MAX_QUEUE (MAX_R * MAX_C)

int grid[MAX_R][MAX_C];
int dist[MAX_R][MAX_C];
int queueR[MAX_QUEUE];
int queueC[MAX_QUEUE];

int main(void) {
    int T, R, C, H;
    int front, rear;
    int moveR[4] = {1, -1, 0, 0};
    int moveC[4] = {0, 0, 1, -1};

    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d", &R, &C, &H);

        for (int i=0; i<R; i++) { // populate input grid
            for (int j=0; j<C; j++) {
                scanf("%d", &grid[i][j]);
            }
        }
        
        // init distances to -1 (unvisited)
        for (int i=0; i<R; i++) {
            for (int j=0; j<C; j++) {
                dist[i][j] = -1;
            }
        }
        
        // BFS init
        front = 0;
        rear = 0;
        dist[0][0] = 0; //start at (0,0)
        queueR[rear] = 0;
        queueC[rear] = 0;
        rear++;
        
        while (front < rear) { // BFS loop
            int r = queueR[front];
            int c = queueC[front];
            front++;
            for (int k=0; k<4; k++) { // go through all neighbors of cell in front position of queue
                int nr = r + moveR[k];
                int nc = c + moveC[k];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) { continue; } // skip out of bounds
                if (grid[nr][nc] == 0 || dist[nr][nc] != -1) { continue; } // skip rocks and already visited cells
                dist[nr][nc] = dist[r][c] + 1;
                queueR[rear] = nr;
                queueC[rear] = nc;
                rear++;
            }
        }
                
        for (int i=0; i < R; i++) { // print result matrix
            for (int j=0; j < C; j++) {
                printf("%d", dist[i][j]);
                if (j < C - 1)
                    printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}
