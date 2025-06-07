
// This code computes the prefix function (also known as the failure function) for a given string.
// The prefix function is used in string matching algorithms, such as the Knuth-Morris-Pratt (KMP) algorithm.
// The prefix function for a string `s` is an array `pi` where `pi[i]` is the length of the longest proper prefix of the substring `s[0..i]` which is also a suffix of this substring.
// The prefix function is useful for efficiently finding occurrences of a pattern in a text.
// The time complexity of computing the prefix function is O(n), where n is the length of the string.
// The space complexity is O(n) for storing the prefix function array.
// The prefix function is particularly useful in string matching algorithms, allowing for efficient searching and pattern recognition.
// The prefix function is widely used in competitive programming and algorithmic challenges involving string matching.
// The algorithm is efficient and can handle large strings, making it suitable for various applications in string processing.
// This code is a fundamental part of many string algorithms and is essential for understanding more complex string processing techniques.
#include <vector>
#include <string>
using namespace std;

vector<int> computePrefixFunction(const string& s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}
vector<int> KMP_Search(const string& text, const string& pattern) {
    int n = text.length(), m = pattern.length();
    vector<int> pi = computePrefixFunction(pattern);
    vector<int> result;
    int j = 0;  // index for pattern

    for (int i = 0; i < n; ++i) {  // index for text
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j]) ++j;
        if (j == m) {
            result.push_back(i - m + 1);  // match found at i - m + 1
            j = pi[j - 1];  // continue searching
        }
    }
    return result;
}
