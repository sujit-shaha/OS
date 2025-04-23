#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

// Calculates difference of each track number with the head position 
void calculateDifference(const vector<int>& request, int head, vector<pair<int, bool>>& diff) {
    for (size_t i = 0; i < request.size(); i++) {
        diff[i].first = abs(head - request[i]); // Calculate absolute difference
    }
}

// Finds the unaccessed track that is at the minimum distance from the head 
int findMIN(const vector<pair<int, bool>>& diff) {
    int index = -1;
    int minimum = INT_MAX;

    for (size_t i = 0; i < diff.size(); i++) {
        if (!diff[i].second && minimum > diff[i].first) { // Find minimum unvisited track
            minimum = diff[i].first;
            index = i;
        }
    }
    return index;
}

void shortestSeekTimeFirst(const vector<int>& request, int head) {
    int n = request.size();
    if (n == 0) {
        cout << "No disk requests to process." << endl;
        return;
    }

    vector<pair<int, bool>> diff(n, {0, false}); // {distance, visited}
    vector<int> seekSequence;
    seekSequence.push_back(head);
    
    int seekCount = 0;
    int currentHead = head;

    for (int i = 0; i < n; i++) {
        calculateDifference(request, currentHead, diff);
        int index = findMIN(diff);
        
        if (index == -1) break; // No more unvisited tracks
        
        diff[index].second = true; // Mark as visited
        seekCount += diff[index].first; // Add distance to seek count
        currentHead = request[index];
        seekSequence.push_back(currentHead);
    }

    // Print results
    cout << "Total seek time: " << seekCount << endl;
    cout << "Seek Sequence: ";
    for (int pos : seekSequence) {
        cout << pos << " ";
    }
    cout << endl;
}

int main() {
    vector<int> tracks = {82, 170, 43, 140, 24, 16, 190};
    int initialHead = 50;

    cout << "SSTF Disk Scheduling Algorithm" << endl;
    cout << "Initial head position: " << initialHead << endl;
    shortestSeekTimeFirst(tracks, initialHead);
    
    return 0;
}