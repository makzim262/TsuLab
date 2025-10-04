#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int bmFind(const string& s, const string& p) {

    unordered_map<char, int> map;

    int n = s.length();
    int m = p.length();
    int i = m - 1;

    for (int i = 0, j = m - 1; i < m; i++) {
        if (!map.count(p[i])) {
            map[p[i]] = j;
            j--;
        }
    }

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

vector<int> bmFindAll(const string& s, const string& p, int start, int end) {

    unordered_map<char, int> map;

    vector<int> matches;
    
    int n = s.length();
    int m = p.length();
    int i = start + m - 2;

    for (int i = 0, j = m - 1; i < m; i++) {
        if (not map.count(p[i])) {
            map[p[i]] = j;
            j--;
        }
    }

    while (i < n) {

        int j = m - 1;
        int k = 0;

        while (j >= 0 and p[j] == s[i - k]) {
            j--;
            k++;
        }

        if (j < 0 and i >= start and i <= end) matches.push_back(i - m + 1);

        if (map.count(s[i-k])) i += map[s[i-k]];
        else i += m;
    }

    return matches;
}

vector<int> bmFindAll(const string& s, const string& p) {
    return bmFindAll(s, p, 0, s.length());
}


int main() {

    string s = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    string p = "tor";

    int result = bmFind(s, p);
    if (not(result == -1)) cout << result;
    else cout << "подстрока не найдена";
    cout << "\n";

    vector<int> matchesAll = bmFindAll(s, p);
    if (not matchesAll.empty()) for (int pos : matchesAll) cout << pos << " ";
    else cout << "подстрока не найдена";
    cout << "\n";

    vector<int> matches = bmFindAll(s, p, 28, 36);
    if (not matches.empty()) for (int pos : matches) cout << pos << " ";
    else cout << "подстрока не найдена";
    cout << "\n";

    return 0;
}