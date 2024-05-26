// PAGE REPLACEMENT




#include <stdio.h>
#include <stdbool.h>
#define PAGE_FRAMES 3
#define PAGE_REF_LENGTH 20

// Function to check if a page is present in the frames
bool isPageInFrames(int frames[], int page) {
    for (int i = 0; i < PAGE_FRAMES; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to find the index of the LRU page
int findLRU(int time[], int n) {
    int minimum = time[0], pos = 0;
    for (int i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }
    return pos;
}

// Function to find the index of the OPTIMAL page
int findOptimal(int pages[], int frames[], int current, int n) {
    int pos = -1, farthest = current;
    for (int i = 0; i < PAGE_FRAMES; ++i) {
        int j;
        for (j = current; j < n; ++j) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n) return i; // If a page is never referenced again, replace it
    }
    return (pos == -1) ? 0 : pos;
}

// FIFO Page Replacement Algorithm
int fifoPageFaults(int pages[], int n) {
    int frames[PAGE_FRAMES];
    int pageFaults = 0, nextFrame = 0;

    for (int i = 0; i < PAGE_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(frames, pages[i])) {
            frames[nextFrame] = pages[i];
            nextFrame = (nextFrame + 1) % PAGE_FRAMES;
            pageFaults++;
        }
    }
    return pageFaults;
}

// LRU Page Replacement Algorithm
int lruPageFaults(int pages[], int n) {
    int frames[PAGE_FRAMES];
    int time[PAGE_FRAMES];
    int pageFaults = 0, counter = 0;

    for (int i = 0; i < PAGE_FRAMES; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(frames, pages[i])) {
            int lruIndex = findLRU(time, PAGE_FRAMES);
            frames[lruIndex] = pages[i];
            time[lruIndex] = counter++;
            pageFaults++;
        } else {
            for (int j = 0; j < PAGE_FRAMES; j++) {
                if (frames[j] == pages[i]) {
                    time[j] = counter++;
                    break;
                }
            }
        }
    }
    return pageFaults;
}

// Optimal Page Replacement Algorithm
int optimalPageFaults(int pages[], int n) {
    int frames[PAGE_FRAMES];
    int pageFaults = 0;

    for (int i = 0; i < PAGE_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(frames, pages[i])) {
            int optimalIndex = findOptimal(pages, frames, i + 1, n);
            frames[optimalIndex] = pages[i];
            pageFaults++;
        }
    }
    return pageFaults;
}

// Second Chance Page Replacement Algorithm
int secondChancePageFaults(int pages[], int n) {
    int frames[PAGE_FRAMES];
    int reference[PAGE_FRAMES] = {0};
    int pageFaults = 0, nextFrame = 0;

    for (int i = 0; i < PAGE_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        if (!isPageInFrames(frames, pages[i])) {
            while (reference[nextFrame] == 1) {
                reference[nextFrame] = 0;
                nextFrame = (nextFrame + 1) % PAGE_FRAMES;
            }
            frames[nextFrame] = pages[i];
            reference[nextFrame] = 1;
            nextFrame = (nextFrame + 1) % PAGE_FRAMES;
            pageFaults++;
        } else {
            for (int j = 0; j < PAGE_FRAMES; j++) {
                if (frames[j] == pages[i]) {
                    reference[j] = 1;
                    break;
                }
            }
        }
    }
    return pageFaults;
}

int main() {
    int pages[PAGE_REF_LENGTH] = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = PAGE_REF_LENGTH;

    int fifoFaults = fifoPageFaults(pages, n);
    int lruFaults = lruPageFaults(pages, n);
    int optimalFaults = optimalPageFaults(pages, n);
    int secondChanceFaults = secondChancePageFaults(pages, n);

    printf("Total page faults using FIFO: %d\n", fifoFaults);
    printf("Total page faults using LRU: %d\n", lruFaults);
    printf("Total page faults using Optimal: %d\n", optimalFaults);
    printf("Total page faults using Second Chance: %d\n", secondChanceFaults);

    return 0;
}

/*


FIFO Page Replacement Algorithm
-------------------------------

How It Works:

1.Initialize frames to -1 (indicating they are empty).
2.For each page in the reference string:
    * If the page is not in the frames, replace the page in the nextFrame index.
    * Move the nextFrame pointer to the next frame (circularly).
    *Increment the page fault count.


LRU Page Replacement Algorithm
-------------------------------

How It Works:

1.Initialize frames and time arrays.
2.For each page in the reference string:
    *If the page is not in the frames, find the least recently used page using the time array.
    *Replace the LRU page with the new page.
    *Update the time for the new page and increment the page fault count.
    *If the page is found in the frames, update its usage time.
    
    
Optimal Page Replacement Algorithm
-------------------------------
How It Works:

1.Initialize frames.
2.For each page in the reference string:
    *If the page is not in the frames, find the page that will not be used for the longest time in the future using the findOptimal function.
    *Replace this page with the new page and increment the page fault count.
    

Second Chance Page Replacement Algorithm
-----------------------------------------
How It Works:

1.Initialize frames and reference bits.
2.For each page in the reference string:
   *If the page is not in the frames, check the reference bit of the frame in the nextFrame index.
   *If the reference bit is 1, reset it to 0 and move to the next frame.
   *Replace the frame when a frame with reference bit 0 is found.
   *Set the reference bit for the new page and increment the page fault count.
   *If the page is found in the frames, set its reference bit to 1.
   
   
*/