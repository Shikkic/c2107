#include<stdio.h>
#include<stdlib.h>

int FirstTime = 1;
char *heapAddress = NULL;
char *heapEndAddress = NULL;
int heapsize = 100;

typedef struct header {
    unsigned int length :29;
    unsigned int NOT_USED :2;
    unsigned int allocated :1;
}HEADER;

/*
//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
*/
void *my_malloc(size_t);
HEADER *head(HEADER*);
void headerINFO(HEADER*);
int roundUp(size_t);
void *nextHeader(HEADER*);

/*
//////////////////////////
//         MAIN         //
//////////////////////////
*/

main() {    
    //my_malloc(8);
    printf("Here is the heap address %x\n", heapAddress); 
    printf("Here is the int in the address %x\n", &heapAddress);
    int i =0;
    HEADER *p = my_malloc(8);
    HEADER *c = my_malloc(9);
    HEADER *d = my_malloc(17);
    while ( i < (heapsize/4)+4) {
        printf("Heap[%d] = %u\n", i, p -> length);
        p++; 
        i++;
    }
     
    printf("Round up of 9 is = %d",roundUp(8)); 

    /*HEADER *h;
    h = (int)heapAddress;
    printf("This should print H.allocated = %u", h -> allocated);
   */ 
    //headerINFO(p);
}

/*
///////////////////////////
//      FUNCTIONS        //
///////////////////////////
*/
void *my_malloc(size_t size) {
    char *heap;

    // RUNS ONLY THE FIRST TIME FUNCTION IS CALLED 
    if(FirstTime) {
        heap = malloc(heapsize);
         
        FirstTime = 0;
        heapAddress = heap;
        //Declaring first free header
        HEADER *freeHeader;
        freeHeader = (HEADER*)heap;
        freeHeader -> length = heapsize;
        freeHeader -> allocated = 0;
        
        //Declaring first free footer
        heap = ((heap)+(heapsize) - 4);
        HEADER *freeFooter; 
        freeFooter = (HEADER*)(heap);
        freeFooter -> length = heapsize;
        freeFooter -> allocated = 0;
    }
 
    HEADER *hp = (HEADER*)heapAddress;
    HEADER *tempHolder;
    HEADER *tempHolder2;
    HEADER *newHeader;
    HEADER *newFooter;
    unsigned int freeHeaderLen;
    unsigned int newBlockSize = roundUp(size)+8;
    int i = 0;
    //WHILE NOT THE END OF THE ARRAY
    //Traverse every header until we find free header
    printf("GOING THROUGH\n");
    int found = 0;
    while(i < 3 | !found) {
        //IF HP != END MEMORY ADDRESS 

        //Check if allocated
        if(isFree(hp)&&((hp -> length >= newBlockSize))){
            printf("HP IS FREE\n");
            //TODO move free header down
            unsigned int oldBlockSize = (hp -> length);
            tempHolder = hp;
            tempHolder = tempHolder + ((newBlockSize/4));
            tempHolder -> length = (oldBlockSize - newBlockSize);
            tempHolder -> allocated = 0;
            freeHeaderLen = (tempHolder -> length);
            printf("THIS IS THE FREEHEADERLEN = %u\n", freeHeaderLen);
            //TODO readjust the older free header
            printf("OLDBLOCK SIZE = %d \n", (oldBlockSize/4));
            printf("NEWBLOCK SIZE = %d \n", (newBlockSize/4));
            tempHolder2 = tempHolder + ((((tempHolder -> length)-4)/4));
            tempHolder2 -> length = freeHeaderLen;
            tempHolder2 -> allocated = 0;
            //TODO save new spot header
            newHeader = hp; 
            newHeader -> length = newBlockSize;
            newHeader -> allocated = 1;
            //TODO save new spot footer
            newFooter = hp + (((newBlockSize)/4)-1);
            newFooter -> length = newBlockSize;
            newFooter -> allocated = 1;
            found = 1;  
        }else{
            //GO to next header
            printf("SKIPPED\n");
            printf("HP HAS LENGTH = %u\n", hp -> length);
            hp = nextHeader(hp);
            printf ("next header is = %u\n", hp -> length);
           
        }   
    i++;
    }        
    
    heap = heapAddress;
    return heap;
    
}

//TODO Not tested yet
int isFree(HEADER *hp) {
    if(hp -> allocated) {
        return 0;
    }
    return 1;
}

//TODO Not tested yet
int isEnd(HEADER *hp) {
    if((HEADER*)hp == (HEADER*)heapEndAddress) {
        return 1;
    }
    return 0;
}

//TODO Not tested yet
void *nextHeader(HEADER *hp){
    hp = hp + ((hp -> length)/4);
    return hp;
}

// TESTED!
void headerINFO(HEADER *hp) {
   printf("This is the length %d\n", hp -> length); 
   printf("This is the the allocation %d\n", hp -> allocated);
}

// TESTED!
int roundUp(size_t num) {
    if(num % 8 == 0) {
        return num;
    }
    int done = 1;
    while(done) {
        if(num % 8 != 0) {
            num++;
        }else{
            done = 0;
        }
    }
    return num;
}
