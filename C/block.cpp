#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    int T;
    cin >> T;
    while (T--) {
        ll e, l, r, b, maxx, minn;
        cin >> e >> l >> r >> b;
        
        if (e == b) {
            maxx = l + r + 2 * e;
        } else {
            maxx = l + r + 2 * min(e, b) + 1;
        }
        
        if (l == 0 && r == 0) {
            minn = e + (b > 0 ? 1 : 0);
        } else {
            minn = max(l, r) + e;
        }
        
        cout << minn << ' ' << maxx << endl;
    }
    return 0;
}
