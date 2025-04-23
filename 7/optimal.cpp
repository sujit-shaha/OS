#include <iostream>
#include <vector>
using namespace std;

// Function to check whether a page exists in a frame
bool search(int key, vector<int>& fr) {
    for (int val : fr) {
        if (val == key)
            return true;
    }
    return false;
}

// Function to find the frame that will not be used recently in future
int predict(vector<int>& pg, vector<int>& fr, int index) {
    int res = -1, farthest = index;

    for (int i = 0; i < fr.size(); i++) {
        int j;
        for (j = index; j < pg.size(); j++) {
            if (fr[i] == pg[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        // If a page is never referenced in the future
        if (j == pg.size())
            return i;
    }

    // Return the index of the frame to be replaced
    return (res == -1) ? 0 : res;
}

void optimalPage(vector<int>& pg, int fn) {
    vector<int> fr(fn, -1);  // Initialize frames with -1
    int hit = 0;

    for (int i = 0; i < pg.size(); i++) {

        // Page Hit
        if (search(pg[i], fr)) {
            hit++;
            cout << "Hit" << endl;
            continue;
        }

        // Page Fault
        cout << "Fault" << endl;

        // Check for empty frame
        bool placed = false;
        for (int j = 0; j < fn; j++) {
            if (fr[j] == -1) {
                fr[j] = pg[i];
                placed = true;
                break;
            }
        }

        // If no empty frame, replace using prediction
        if (!placed) {
            int pos = predict(pg, fr, i + 1);
            fr[pos] = pg[i];
        }
    }

    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pg.size() - hit << endl;
}

int main() {
    int pn, fn;
    cout << "Enter the number of pages: ";
    cin >> pn;
    cout << "Enter the number of frames: ";
    cin >> fn;

    vector<int> pg(pn);
    cout << "Enter the page reference sequence:\n";
    for (int i = 0; i < pn; i++) {
        cin >> pg[i];
    }

    optimalPage(pg, fn);
    return 0;
}
