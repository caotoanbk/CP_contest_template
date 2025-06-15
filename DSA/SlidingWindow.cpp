#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <deque>
#include <iostream>
using namespace std;

//-----TIPS-----
// Use 2 pointers (start, end) for most sliding window.
// Use deque for monotonic values (min/max).
// Use hash map/set for frequency/uniqueness tracking.
// Combine with binary search for max/min length window problems.

// Find the maximum sum of any subarray of size k.
int maxSumSubarray(const vector<int>& a, int k) {
    int n = a.size(), sum = 0, maxSum = 0;

    for (int i = 0; i < k; ++i) sum += a[i];
    maxSum = sum;

    for (int i = k; i < n; ++i) {
        sum += a[i] - a[i - k];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}


//Find the length of the longest substring with no repeating characters.
int lengthOfLongestUniqueSubstring(string s) {
    unordered_set<char> seen;
    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); ++right) {
        while (seen.count(s[right])) {
            seen.erase(s[left++]);
        }
        seen.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

//Find the max in every window of size k.
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;

    for (int i = 0; i < nums.size(); ++i) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i])
            dq.pop_back();

        dq.push_back(i);
        if (i >= k - 1)
            res.push_back(nums[dq.front()]);
    }
    return res;
}
#include <bits/stdc++.h>
using namespace std;

//Find the min in every window of size k.
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // stores indices
    vector<int> res;

    for (int i = 0; i < nums.size(); ++i) {
        // Remove indices out of the window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Remove indices whose values are greater than current
        while (!dq.empty() && nums[dq.back()] >= nums[i])
            dq.pop_back();

        // Add current index
        dq.push_back(i);

        // Window is ready: record result
        if (i >= k - 1)
            res.push_back(nums[dq.front()]);
    }

    return res;
}


