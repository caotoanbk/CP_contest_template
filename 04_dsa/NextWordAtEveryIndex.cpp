#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to build the next word at every index in the string
// It returns a vector where each index contains the next word starting from that index
vector<string> buildNextWord(const string& s) {
    int n = s.size();
    vector<string> nextWord(n, "");

    int i = n - 1;
    while (i >= 0) {
        if (s[i] == ' ') {
            // Skip spaces
            nextWord[i] = (i + 1 < n) ? nextWord[i + 1] : "";
            --i;
        } else {
            // Find start of the word
            int end = i;
            while (i >= 0 && s[i] != ' ') {
                --i;
            }
            string word = s.substr(i + 1, end - i);
            for (int j = i + 1; j <= end; ++j) {
                nextWord[j] = word;
            }
        }
    }

    return nextWord;
}

int main() {
    string s = "the  quick brown   fox";
    auto words = buildNextWord(s);

    for (int i = 0; i < s.size(); ++i) {
        cout << "Index " << i << " ('" << s[i] << "') → " << (words[i].empty() ? "[empty]" : words[i]) << '\n';
    }
}
