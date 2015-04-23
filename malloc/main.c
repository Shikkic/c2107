#include<stdio.h>
#include<stdlib.h>

#include<errno.h>
int FirstTime = 1;
char *heapAddress = NULL;
char *heapEndAddress = NULL;
int heapsize = 104;

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
void *my_free(void*);
void *previousFooter(HEADER*);
void *nextFooter(HEADER*);
/*
//////////////////////////
//         MAIN         //
//////////////////////////
*/

main() {    
    
    printf("Here is the heap address %x\n", heapAddress); 
    printf("Here is the int in the address %x\n", &heapAddress);
    int i =0;
    HEADER *p = my_malloc(16);
    if(p != NULL)
        p -> length = 9999;
    HEADER *c = my_malloc(16);
    if(c != NULL)
        c -> length = 9999;
    HEADER *f = my_malloc(16);
    f -> length = 9999;
    /*HEADER *g = my_malloc(4);
    g -> length = 9999;
    */

    //my_free(p);
    my_free(c);
    my_free(f);
    //HEADER *d = my_malloc(17);
    //d -> length = 9999;
    HEADER *pointer = (HEADER*)heapAddress;
    while ( i < (heapsize/4)) {
        printf("Heap[%d] = %u, allocated = %u\n", i, pointer -> length, pointer -> allocated);
        pointer++; 
        i++;
    }
     
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
    HEADER *returnAddress;
    unsigned int freeHeaderLen;
    unsigned int newBlockSize = roundUp(size)+8;
    int i = 0;
    //WHILE NOT THE END OF THE ARRAY
    //Traverse every header until we find free header
    printf("GOING THROUGH\n");
    int traversal = 0;
    int found = 0;
    while(traversal < heapsize && !found) {
        //IF HP != END MEMORY ADDRESS 
        printf("TRAVERSAL = %d", traversal);
        //Check if hp -> length == newBlockSize
        if(isFree(hp)&&(hp -> length) == newBlockSize) {
            //TODO take the header and change it to allocated
            hp -> allocated = 1;
            returnAddress = hp + 1;
            //TODO take the footer and change it to allocated
            hp = hp +(((hp -> length)-4)/4);
            hp -> allocated = 1;
            //TODO save found = 1;
            found = 1;
        }//Check if allocated
        else if(isFree(hp)&&((hp -> length >= newBlockSize))){
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
            returnAddress = hp + 1;
            newHeader -> length = newBlockSize;
            newHeader -> allocated = 1;
            //TODO save new spot footer
            newFooter = hp + (((newBlockSize)/4)-1);
            newFooter -> length = newBlockSize;
            newFooter -> allocated = 1;
            //TODO Save found 
            found = 1;
            //TODO Return proper memory address;

        }else{
            //GO to next header
            printf("SKIPPED\n");
            printf("HP HAS LENGTH = %u\n", hp -> length);
            hp = nextHeader(hp);
            printf ("next header is = %u\n", hp -> length);
           
        }   
    //traversal += (hp -> length);
    traversal++;
    }
    if(!found){
        errno = ENOMEM;
        return NULL;
    }    
    return returnAddress;
    
}

void *my_free(void *p) {
    
    HEADER *hp = (HEADER*)p;
    hp = (hp - 1); 
    HEADER *currentHeader = hp;
    //TODO CHECK IF PREVIOUS HEADER EXISTS AND IS FREE
    //hp = previousHeader(hp);
    if(isFree(previousFooter(hp))){
        printf("PREVIOuS FOOTER IS FREE\n");
        //TODO UPDATE NEW HEADER
        hp = previousFooter(hp);
        hp = hp -(((hp ->length)/4)-1);
        printf("hp's length = %u", currentHeader -> length);
        unsigned int NL= (hp -> length) + (currentHeader -> length);
        hp -> length = NL; 
        //TODO UPDATE NEW FOOTER
        hp = currentHeader;
        hp = hp + (((hp -> length)/4)-1);
        hp -> length = NL;
    }    
    //TODO CHECK IF NEXT FOOTER EXISTS AND FREE CHANGE LENGTH TO INCLUDE BOTH
    /*if(isFree(nextFooter(hp))) {
        printf("NEXT FOOTER IS FREE");
        hp = nextFooter(hp);
        
        hp -> length = 66; 


    } */ 
        //TODO CHANGE PREVIOUS HEADER LENGTH TO += freed header 
        
    //TODO CHCK IF NEXT HEADER IS FREE
        //TODO IF FREE CHANGE LENGTH TO INCLUDE BOTH
    //TODO change footer allocated to 0
    hp = currentHeader;
    hp -> allocated = 0;

    //TODO 

    //TODO change footer allocaed to 0
    hp = hp + (((hp -> length)-1)/4);
    hp -> allocated = 0;
}

//TODO TESTED!
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

void *nextFooter(HEADER *hp) {
    hp = hp +(((hp -> length)/4) +1);
    hp = hp +(((hp -> length)/4) +1);
    return hp;
}

//TODO Not tested yet
void *previousFooter(HEADER *hp) {
    hp = hp - 1;
    return hp;
}

//TODO TESTED!
void *nextHeader(HEADER *hp){
    hp = hp + (((hp -> length))/4);
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
