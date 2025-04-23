#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "Please Enter Correct Command !!!" << endl;
        exit(EXIT_FAILURE);
    }

    string pattern = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (!file) {
        cout << "No File Found, Error in Opening File !!!" << endl;
        exit(EXIT_FAILURE);
    }

    char line[1000];

    cout << "Searching for pattern '" << pattern << "' in '" << filename << "'..." << endl;

    while (fgets(line, sizeof(line), file)) {
        string strLine(line);
        size_t pos = strLine.find(pattern);
        if (pos != string::npos) {
            // Print before, highlight match, then after
            cout << strLine.substr(0, pos);
            cout << "\033[1;31m" << pattern << "\033[0m";
            cout << strLine.substr(pos + pattern.length());
        }
    }

    fclose(file);
    return 0;

}