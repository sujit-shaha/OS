#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int a = 0, b = 0, page_fault = 0;

    const int total_frames = 3;
    int frames[total_frames]; // Array to store the current pages in memory
    int temp[total_frames];   // Temporary array to mark recently used pages
    int position = 0;         // Position to replace page

    // Reference string: the sequence of pages being requested
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int total_pages = pages.size();

    // Initialize frames with -1 indicating empty
    for (int i = 0; i < total_frames; i++)
    {
        frames[i] = -1;
    }

    // Loop over each page in the reference string
    for (int i = 0; i < total_pages; i++)
    {
        a = 0, b = 0;

        // Check if page is already in any frame (Page Hit)
        for (int j = 0; j < total_frames; j++)
        {
            if (frames[j] == pages[i])
            {
                a = 1; // Page is found
                b = 1; // No need to replace
                break;
            }
        }

        // If it's a Page Miss, check if there's an empty frame
        if (a == 0)
        {
            for (int j = 0; j < total_frames; j++)
            {
                if (frames[j] == -1)
                {
                    frames[j] = pages[i]; // Put the page in the empty frame
                    b = 1;
                    page_fault++;
                    break;
                }
            }
        }

        // If it's a Page Miss and no empty frame, apply replacement
        if (b == 0)
        {
            // Mark all frames as not recently used
            for (int j = 0; j < total_frames; j++)
            {
                temp[j] = 0;
            }

            // Look backwards from the current index and mark recently used pages
            for (int k = i - 1, l = 1; l <= total_frames - 1; l++, k--)
            {
                for (int j = 0; j < total_frames; j++)
                {
                    if (frames[j] == pages[k])
                    {
                        temp[j] = 1;
                    }
                }
            }

            // Find a frame that wasn't recently used (Least Recently Used)
            for (int i = 0; i < total_frames; i++)
            {
                if (temp[i] == 0)
                {
                    position = i;
                }

            }
            // Replace it with the new page
            frames[position] = pages[i];
            page_fault++;

            // Print current frame status
            for (int j = 0; j < total_frames; j++)
            {
                cout << frames[j] << "\t";
            }
            cout << endl;
        }

        
    }
    cout << "\nTotal Page Faults:\t" << page_fault << endl;
    cout << "Total Page Hits:\t" << total_pages - page_fault << endl;
    return 0;
}
    // for (int k = i - 1, l = 1; l <= total_frames - 1; l++, k--) {
    //     for (int j = 0; j < total_frames; j++) {
    //         if (frames[j] == pages[k]) {
    //             temp[j] = 1; // This frame wa s recently used
    //         }
    //     }
    // }