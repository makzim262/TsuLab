#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int bmFind(string s, string p) {

    unordered_map<char, int> map;

    for (int i = 0, j = p.length()-1; i < p.length(); i++) {
        if (!map.count(p[i])) {
            map[p[i]] = j;
            j--;
        }
    }

    int n = s.length();
    int m = p.length();
    int i = m - 1;

    while (i < n) {

        int j = m - 1;
        int k = 0;

        while (j >= 0 and p[j] == s[i - k]) {
            j--;
            k++;
        }

        if (j < 0) return i - m + 1;

        if (map.count(s[i-k])) i += map[s[i-k]];
        else i += m;
    }

    return -1;
}

int main() {

    string s = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    string p = "tor";

    int result = bmFind(s, p);
    if (result == -1) cout << "подстрока не найдена";
    else cout << result;
    return 0;
}