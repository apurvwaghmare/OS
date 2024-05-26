// LA TO PA


#include <stdio.h>

int main() {
    int logicalAddress;
    int segmentSize, pageSize;
    int segmentNumber, segmentOffset, pageNumber, pageOffset;
    int physicalAddress;

    // Input: segment size
    printf("Enter segment size: ");
    scanf("%d", &segmentSize);

    // Input: page size
    printf("Enter page size: ");
    scanf("%d", &pageSize);

    // Input: logical address
    printf("Enter logical address: ");
    scanf("%d", &logicalAddress);

    // Calculate segment number and offset
    segmentNumber = logicalAddress / segmentSize;
    segmentOffset = logicalAddress % segmentSize;

    // Calculate page number and offset within the segment
    pageNumber = segmentOffset / pageSize;
    pageOffset = segmentOffset % pageSize;

    // Page table that maps page numbers to frame numbers
    int pageTable[] = {0, 2, 1};
    
    // Get frame number from page table using page number
    int frameNumber = pageTable[pageNumber];
    
    // Calculate physical address
    physicalAddress = frameNumber * pageSize + pageOffset;

    // Output the results
    printf("Segment Number: %d\n", segmentNumber);
    printf("Segment Offset: %d\n", segmentOffset);
    printf("Page Number: %d\n", pageNumber);
    printf("Page Offset: %d\n", pageOffset);
    printf("Frame Number: %d\n", frameNumber);
    printf("Physical Address: %d\n", physicalAddress);

    return 0;
}

/*

Enter segment size: 100
Enter page size: 20
Enter logical address: 215
Segment Number: 2
Segment Offset: 15
Page Number: 0
Page Offset: 15
Frame Number: 0
Physical Address: 15

*/



/*


Segmentation
------------
   Segmentation divides the process's address space into different segments, 
   each of which can correspond to logical units like code, data, stack, etc. Each segment has a base address and a limit (size).

   *Segment Number: This indicates which segment the address belongs to.
   *Segment Offset: This is the offset within the segment.
   
Paging
------
Paging is used within each segment to further divide the memory into fixed-size blocks called pages.
The process's address space is divided into pages, and the physical memory is divided into frames of the same size.

   *Page Number: This is the index of the page within the segment. 
   *Page Offset: This is the offset within the page. 
   
   
Segment Calculation:
-------------------

   *The logical address is divided by the segment size to determine the segment number.
   *The remainder of this division gives the segment offset.


Page Calculation within the Segment:
-----------------------------------

   *The segment offset is divided by the page size to determine the page number.
   *The remainder of this division gives the page offset.
   
   
Physical Address Calculation:
----------------------

   *The physical address is calculated by multiplying the frame number by the page size and adding the page offset.
   
   
*/