#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct MemoryBlock {
    int id;
    int size;
    bool allocated;
    int processId;
};

struct Process {
    int id;
    int size;
    bool allocated;
    int blockId;
};

// Global variables
vector<MemoryBlock> memoryBlocks;
vector<Process> processes;
int lastAllocatedIndex = 0;

// Function to reset allocation status
void resetAllocation() {
    for (auto& block : memoryBlocks) {
        block.allocated = false;
        block.processId = -1;
    }

    for (auto& process : processes) {
        process.allocated = false;
        process.blockId = -1;
    }

    lastAllocatedIndex = 0;
}

// First Fit allocation algorithm
void firstFit() {
    resetAllocation();
    
    for (auto& process : processes) {
        for (auto& block : memoryBlocks) {
            if (!block.allocated && block.size >= process.size) {
                block.allocated = true;
                block.processId = process.id;
                process.allocated = true;
                process.blockId = block.id;
                break;
            }
        }
    }
}

// Best Fit allocation algorithm
void bestFit() {
    resetAllocation();
    
    for (auto& process : processes) {
        int bestFitIndex = -1;
        int bestFitSize = INT_MAX;

        for (int i = 0; i < memoryBlocks.size(); i++) {
            if (!memoryBlocks[i].allocated && memoryBlocks[i].size >= process.size) {
                if (memoryBlocks[i].size < bestFitSize) {
                    bestFitSize = memoryBlocks[i].size;
                    bestFitIndex = i;
                }
            }
        }

        if (bestFitIndex != -1) {
            memoryBlocks[bestFitIndex].allocated = true;
            memoryBlocks[bestFitIndex].processId = process.id;
            process.allocated = true;
            process.blockId = memoryBlocks[bestFitIndex].id;
        }
    }
}

// Worst Fit allocation algorithm
void worstFit() {
    resetAllocation();
    
    for (auto& process : processes) {
        int worstFitIndex = -1;
        int worstFitSize = -1;

        for (int i = 0; i < memoryBlocks.size(); i++) {
            if (!memoryBlocks[i].allocated && memoryBlocks[i].size >= process.size) {
                if (memoryBlocks[i].size > worstFitSize) {
                    worstFitSize = memoryBlocks[i].size;
                    worstFitIndex = i;
                }
            }
        }

        if (worstFitIndex != -1) {
            memoryBlocks[worstFitIndex].allocated = true;
            memoryBlocks[worstFitIndex].processId = process.id;
            process.allocated = true;
            process.blockId = memoryBlocks[worstFitIndex].id;
        }
    }
}

// Next Fit allocation algorithm
void nextFit() {
    resetAllocation();
    int n = memoryBlocks.size();

    for (auto& process : processes) {
        bool allocated = false;
        int count = 0;
        int index = lastAllocatedIndex;

        while (count < n) {
            if (!memoryBlocks[index].allocated && memoryBlocks[index].size >= process.size) {
                memoryBlocks[index].allocated = true;
                memoryBlocks[index].processId = process.id;
                process.allocated = true;
                process.blockId = memoryBlocks[index].id;
                lastAllocatedIndex = (index + 1) % n;
                allocated = true;
                break;
            }
            index = (index + 1) % n;
            count++;
        }
    }
}

// Display memory allocation results
void displayMemoryState(const string& algorithm) {
    cout << "\n" << algorithm << " Allocation Result:\n";
    cout << "------------------------------------------\n";
    cout << "Memory Blocks:\n";
    cout << setw(10) << "Block ID" << setw(10) << "Size" << setw(15) << "Status" << setw(15) << "Process ID\n";
    
    for (const auto& block : memoryBlocks) {
        cout << setw(10) << block.id << setw(10) << block.size;
        
        if (block.allocated) {
            cout << setw(15) << "Allocated" << setw(15) << block.processId << endl;
        } else {
            cout << setw(15) << "Free" << setw(15) << "-" << endl;
        }
    }
    
    cout << "\nProcesses:\n";
    cout << setw(12) << "Process ID" << setw(10) << "Size" << setw(15) << "Status" << setw(15) << "Block ID\n";
    
    for (const auto& process : processes) {
        cout << setw(12) << process.id << setw(10) << process.size;
        
        if (process.allocated) {
            cout << setw(15) << "Allocated" << setw(15) << process.blockId << endl;
        } else {
            cout << setw(15) << "Waiting" << setw(15) << "-" << endl;
        }
    }
    
    cout << "------------------------------------------\n";
}

int main() {
    int choice, size, numBlocks, numProcesses;
    
    cout << "Memory Allocation Simulator\n";
    cout << "===========================\n\n";
    
    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    
    cout << "\nEnter the sizes of memory blocks:\n";
    for (int i = 0; i < numBlocks; i++) {
        cout << "Block " << i+1 << " size: ";
        cin >> size;
        memoryBlocks.push_back({i+1, size, false, -1});
    }
    
    cout << "\nEnter the number of processes: ";
    cin >> numProcesses;
    
    cout << "\nEnter the sizes of processes:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << i+1 << " size: ";
        cin >> size;
        processes.push_back({i+1, size, false, -1});
    }
    
    do {
        cout << "\nMemory Allocation Strategies\n";
        cout << "----------------------------\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Next Fit\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                firstFit();
                displayMemoryState("First Fit");
                break;
                
            case 2:
                bestFit();
                displayMemoryState("Best Fit");
                break;
                
            case 3:
                worstFit();
                displayMemoryState("Worst Fit");
                break;
                
            case 4:
                nextFit();
                displayMemoryState("Next Fit");
                break;
                
            case 5:
                cout << "\nExiting the program. Thank you!\n";
                break;
                
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}