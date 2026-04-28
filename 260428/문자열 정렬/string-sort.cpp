#include <iostream>
#include <string>

using namespace std;

string str;

int main() {
    cin >> str;

    int cnt[26] = {0};

    for (int i = 0; i < str.length(); i++) {
        cnt[str[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        while (cnt[i] > 0) {
            cnt[i]--;
            cout << (char)('a' + i);
        }
    }

    return 0;
}