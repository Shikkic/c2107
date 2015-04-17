#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char **chop(char* , char c);
int checkInDict(char*, char**);
int get_num_lines(char*, char c);
char *readFile(char*);
char shift(char, int);
void shiftString(char[], int);
int wordInDic(char[], char*[]);
int file_len(char*);
int array_len(char **);
void shiftArray(char **, int );

main(int r, char **argv) {
    char *ef, *ef2;
    char *dic;
    //READFILE
    if(((ef = readFile("jaws_encr.txt"))==NULL)) {
        printf("READ-FAILED");
        return 1;
    }
    if(((ef2 = readFile("jaws_encr.txt"))==NULL)) {
        printf("READ-FAILED");
        return 1;
    }
    if(((dic = readFile("words.txt"))==NULL)) {
        printf("READ-FAILED");
        return 1;
    }
   
    //CHOP & LEN DECLARATIONS
    char **ec = chop(ef, ' ');
    char **dicChop = chop(dic, '\n');
    int dicLen = array_len(dicChop);
    int ecLen = array_len(ec);

    /*
    int i;
    for(i = 0; i < ecLen; i++){
        printf("Printing file %s\n", ec[i]); 
    }
*//*
    shiftArray(dicChop, 1);
    int z;
    for(z = 0; z < dicLen; z++) {
        printf("Printing file %s\n", dicChop[z]);
    }*/
        /*
    int i = 0, z = 0, count;
    char results[27];    

    for(i = 0; i < ecLen; i++) {

    }
*/
/*
    char *a[] = {"dog","doge","butt",'\0'};
    char *b[] = {"dog","doge","butt",'\0'};
    int rap = compareArray(a, b);
    printf("rap IS = %d ", rap);
    */
    
    int i = 0;
    int results[27];
    while(i <= 27) {
        shiftArray(ec, 1);
        results[i] = compareArray(ec, dicChop); 
        printf("results[%d]: %d\n",i,(results[i]) );
        i++; 
    }
    /*
    i =0;
    while(i <= 26) {
        printf("results[%d]: %d\n",i,results[i] );
        i++;
    }
*/
    shiftString(ef2, 26);
    //printf("lololollololol%s",ef2);
    printf("WE MADE IT!");
    return 0;
}

//FUNCTIONS~

// Function which passes a char c, and shift value k. 
// Returns the char which is shifted by k characters.
void shiftArray(char **a, int shift) {
    int i = 0;
    while(*a[i] != '\0') {
        shiftString(a[i], shift);
        i++;
    }
}

typedef char * string;

int compareArray(string a[], string b[]) {
    int i = 0,count = 0, z = 0;
    while(i < 50) {
        while((b[z]) != NULL) {
            if((strcasecmp((char*)a[i], (char*)b[z]))==0) {
                count++;  
                //printf("A[%d] = %s  B[%d] = %s\n", i, a[i], z,b[z]);
                //printf("count++");
            }else{
               //count++; 
            }
            z++;
        }
        //printf("A[%d] = %s  B[%d] = %s\n", i, a[i], z,b[z]);
        i++;
        z=0;
    }
    return count;

}

int array_len(char **a) {
    int i = 0;
    int sum = 0;
    while(a[i] != '\0'){
        sum++;
        i++;
    }
    return sum;
}

char **chop(char *s , char c) {
    char **lines;
    int i, j;
    int num_lines;
    int len;

    /* figure out how many lines there are in s */
    num_lines=get_num_lines(s ,c);

    if ((lines=malloc((num_lines+2)*sizeof(char*)))==NULL)
        return NULL;

    len=strlen(s);
    lines[0]=s;
    for (i=0, j=1; i<len; i++) {
        if( (s[i]==c)){
             s[i]='\0';
             lines[j]=&(s[i+1]);
             j++;
        }
    }
    lines[j]=NULL;
    return lines;
}

int checkInDict(char *s, char **dict){
    int x=0,y=-1;
    while((dict[x] !=NULL)&&(y !=0)){
        y = strcasecmp(s,dict[x]);
        x++;
    }
    if(y==0){
        return 1;
    }
    else{ 
        return 0;
    }
}

int file_len(char *filename) {
    int count=0;
    int c;
    FILE *fp;

    if ((fp=fopen(filename, "r"))==NULL)
        return -1;

    while ((c=fgetc(fp))!=EOF)
        count++;

    fclose(fp);
    return count;
    }

int get_num_lines(char *s, char c) {
    int count=0;
    int i=0;

    while (s[i]!='\0') {
        if (s[i]==c)
        count++;
        i++;
    }

    return count;
}

char *readFile(char *filename){
    int len = file_len(filename);
    FILE *fp;
    char *s;int c,i;
    if(len ==-1){
        return NULL;
    }
    if((s=(char*)malloc(len+len))==NULL){
        return NULL;
    }
    if((fp=fopen(filename,"r"))==NULL){
       free(s);
        return NULL;
    }
    i=0;
    while ((c=fgetc(fp))!=EOF){
        s[i] =c;
        i++;
    }
    s[i]='\0';

    fclose(fp);
    return s;
}


char shift(char c, int shift) {
    int upper = isupper(c);
    c = tolower(c);   
    unsigned char newChar = c + shift;
    while( newChar > 122) {
        newChar = 97 + (newChar - 123);
    }  
    if(upper)
        newChar -= 32;
    return newChar;
}

void shiftString(char s[], int shiftNum) {
    char *p = s;
    int alpha = isalpha(*p);
    while(*p != '\0') {
        alpha = isalpha(*p);
        if(alpha){
            *p = shift(*p, shiftNum);
        }
        p++;
    }
    p = s;
}  

int wordInDic(char s[], char *dict[]) {
    int i = 0;
    while( dict[i] != '\0') {
        if(strcasecmp(s,dict[i]) == 0) {
            return 1;    
        }
        i++;
    } 
    return 0;
}








