#include <stdio.h>

long long T, k, a, b, c;
long long solve() {
    scanf("%d %d %d %d", &k, &a, &b, &c);
    long long max_s = 0;
    max_s = (a <= k) ? a : max_s;
    max_s = (b <= k) ? b : max_s;
    max_s = (c <= k) ? c : max_s;
    max_s = (a + b <= k) ? a + b : max_s;
    max_s = (a + c <= k) ? a + c : max_s;
    max_s = (b + c <= k) ? b + c : max_s;
    max_s = (a + b + c <= k) ? a + b + c : max_s;
    return k > max_s ? k - max_s : 0;
}

int main() {
    scanf("%d", &T);
    char buf[32];
    while (T--) {
        long long result = solve();
        sprintf(buf, "%lld\n", result);
        fputs(buf, stdout);
    }
    return 0;
}
