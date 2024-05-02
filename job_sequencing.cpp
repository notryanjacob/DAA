#include <iostream>
#include <vector>
#include <algorithm>


struct Job {
    int id;
    int deadline;
    int profit;
};


bool compare(Job a, Job b) {
    return (a.profit > b.profit);
}

void printJobScheduling(std::vector<Job>& jobs) {
    
    std::sort(jobs.begin(), jobs.end(), compare);

    int n = jobs.size();
    int result[n];
    bool slot[n];

    
    for (int i = 0; i < n; i++) {
        slot[i] = false;
    }

    
    for (int i = 0; i < n; i++) {
        result[i] = -1;
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = std::min(n, jobs[i].deadline) - 1; j >= 0; j--) {
            if (!slot[j]) {
                result[j] = i; 
                slot[j] = true; 
                break;
            }
        }
    }

    
    std::cout << "Selected jobs and their profits:" << std::endl;
    for (int i = 0; i < n; i++) {
        if (slot[i]) {
            std::cout << "Job " << jobs[result[i]].id << ": Profit " << jobs[result[i]].profit << std::endl;
        }
    }
}

int main() {
    std::vector<Job> jobs = { {1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30} };

    std::cout << "Maximum profit subset of jobs:" << std::endl;
    printJobScheduling(jobs);

    return 0;
}
