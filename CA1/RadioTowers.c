#include <stdio.h>

int main(){
    int    a[(int)1e5 + 5];
    int    n, d, mCovered = 0;

    scanf("%d %d", &n, &d);
    for (int i=0; i<n; ++i){ scanf("%d", &a[i]); }

    // Compute `ans` as the number of cities covered by a tower located at a[i]
    int lead = 0;
    int trail = 0;
    int ans = 0;
    for (int i=0; i<n; ++i){
        while ( lead<n && (a[lead] - a[i]) <= d){ lead++;  }
        while (trail<n && (a[i] - a[trail]) > d){ trail++; }
        ans = lead - trail;
        printf("%d\n", ans);
    }
        
    //Compute `ans` as the maximum number of cities that can be covered by a single tower
    ans = 1;
    lead = 1;
    trail = 0;
    int count = 1;
        while (lead<n){
            if (a[lead] - a[trail] <= d*2){ 
                count++;
                lead++; 
            }
            else if (a[lead] - a[trail] > d*2) {
                if (count>0){count--;}
                trail++;
            }
            if (count > ans){ ans = count;}
        }
    printf("%d\n", ans);
    return 0;
}