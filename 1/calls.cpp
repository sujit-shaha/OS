#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/wait.h> // Add this for wait() function
#include <sys/types.h> // Add this for pid_t and other types
using namespace std;

void simulate_cp(string& src, string& dest)
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0)
    {
        cout<<"Child Process pid : "<< getpid() <<endl;
        cout<<"Parent Process pid : "<< getppid()<<endl;

        // Use standard cp command instead of mycp
        execlp("./mycp", "mycp", src.c_str(), dest.c_str(), NULL);
        perror("execlp failed");
        exit(EXIT_FAILURE); 
    }
    else{
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        cout<<"CP command done."<<endl;
    }
}

void simulate_grep(const std::string& pattern, const std::string& file) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        std::cout << "Child (grep): PID=" << getpid() << ", Parent PID=" << getppid() << std::endl;
        
        // Use standard grep command instead of mygrep
        execlp("./mygrep", "mygrep", pattern.c_str(), file.c_str(), nullptr);
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        std::cout << "\nParent: Completed grep command.\n";
    }
}

// Add this function to your file
void simulate_ls(const std::string& path, bool long_format) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        std::cout << "Child (ls): PID=" << getpid() << ", Parent PID=" << getppid() << std::endl;
        
        if (long_format) {
            // For long format (ls -l)
            execlp("ls", "ls", "-l", path.c_str(), nullptr);
        } else {
            // For regular ls
            execlp("ls", "ls", path.c_str(), nullptr);
        }
        
        perror("execlp failed");
        exit(EXIT_FAILURE);
    } else {
        // Wait for child to complete
        int status;
        waitpid(pid, &status, 0);
        std::cout << "\nParent: Completed ls command.\n";
    }
}

int main()
{
    string src, dest, pattern, filename, path;
    int ch;
    bool long_format;
    while(true)
    {
        cout << "Enter the choice:" << endl;
        cout << "1. Copy File" << endl;
        cout << "2. Search Pattern in File" << endl;
        cout << "3. List Directory Contents" << endl;
        cout << "4. Exit" << endl;
        cin >> ch;

        switch(ch)
        {
            case 1:
                cout << "Enter Source File Name:";
                cin >> src;
                cout << "Enter Destination File Name:";
                cin >> dest;
                simulate_cp(src, dest);
                break;

            case 2:
                cout << "Enter Pattern to Search:";
                cin >> pattern;
                cout << "Enter File Name:";
                cin >> filename;
                simulate_grep(pattern, filename);
                break;
                
            case 3:
                cout << "Enter Path (or press Enter for current directory):";
                cin.ignore();
                getline(cin, path);
                if (path.empty()) {
                    path = ".";
                }
                cout << "Use long format? (1 for yes, 0 for no):";
                cin >> long_format;
                simulate_ls(path, long_format);
                break;

            case 4:
                cout << "Exiting..." << endl;
                exit(0);
        }
    }
}