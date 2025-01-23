#include <iostream>

using namespace std;

int a[(int)1e5 + 5];
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    int n, d;
    cin >> n >> d;
    for (int i=0;i<n;++i) {
        cin >> a[i];
    }
    for (int i=0;i<n;++i) {
        int ans = 0;
        /*
            Compute `ans` as the number of cities covered by a tower located at a[i]
        */
        cout << ans << '\n';
    }
    int ans = 0;
    /*
        Compute `ans` as the maximum number of cities that can be covered by a single tower
    */
    cout << ans << '\n';
    return 0;
}
