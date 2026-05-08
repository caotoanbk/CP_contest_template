
// Given n activities with start and end times, find the maximum number of activities you can attend (no overlap).
bool cmp(pair<int, int>& a, pair<int, int>& b) {
    return a.second < b.second; // Sort by end time
}

int maxActivities(vector<pair<int, int>>& intervals) {
    sort(intervals.begin(), intervals.end(), cmp);
    int count = 0, lastEnd = -1;

    for (auto [start, end] : intervals) {
        if (start >= lastEnd) {
            count++;
            lastEnd = end;
        }
    }

    return count;
}

// You are given n jobs where each job has a deadline and profit. Each job takes 1 unit of time. Schedule jobs to maximize total profit such that no two jobs overlap, and each job is completed before its deadline.
// Sort jobs by profit (descending).
// Always schedule the most profitable job as late as possible before its deadline.
struct Job {
    int id, deadline, profit;
};

bool cmp(Job& a, Job& b) {
    return a.profit > b.profit;
}

int maxProfit(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), cmp);
    int n = jobs.size();

    vector<int> slot(n, -1); // -1 means free
    int totalProfit = 0;

    for (auto& job : jobs) {
        for (int t = min(n, job.deadline) - 1; t >= 0; t--) {
            if (slot[t] == -1) {
                slot[t] = job.id;
                totalProfit += job.profit;
                break;
            }
        }
    }

    return totalProfit;
}

// Minimum Number of Platforms (Train Schedule Problem)
// Given arrival and departure times of trains at a station, find the minimum number of platforms required so that no train has to wait.
// We need to track the number of overlapping trains at any time.
// Sort arrival and departure arrays separately.
// Use two pointers to simulate events in time order.
int findMinPlatforms(vector<int>& arrival, vector<int>& departure) {
    sort(arrival.begin(), arrival.end());
    sort(departure.begin(), departure.end());

    int n = arrival.size();
    int i = 0, j = 0;
    int platforms = 0, maxPlatforms = 0;

    while (i < n && j < n) {
        if (arrival[i] <= departure[j]) {
            platforms++; // new train arrived
            maxPlatforms = max(maxPlatforms, platforms);
            i++;
        } else {
            platforms--; // train departed
            j++;
        }
    }

    return maxPlatforms;
}



// You're walking along a path with n plants that need watering. You have a watering can with capacity C, and each plant i needs plants[i] units of water. Find the minimum number of refills needed to water all the plants in order.
// Always try to water as far as possible before refilling.
// Refill only when the next plant cannot be watered with the remaining water.
int minRefills(vector<int>& plants, int capacity) {
    int current = capacity;
    int refills = 0;

    for (int i = 0; i < plants.size(); ++i) {
        if (plants[i] > capacity)
            return -1; // impossible

        if (plants[i] > current) {
            refills++;
            current = capacity;
        }

        current -= plants[i];
    }

    return refills;
}
