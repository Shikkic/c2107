#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

typedef char * string;

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
int compareArray(string[], string[]);

int main(int argc, char *argv[]) {
    char *ef, *ef2;
    char *dic;
    //READFILE
    if(((ef = readFile(argv[1]))==NULL)) {
        printf("READ-FAILED: %s",argv[1]);
        return 1;
    }
    if(((ef2 = readFile(argv[1]))==NULL)) {
        printf("READ-FAILED");
        return 1;
    }
    if(((dic = readFile(argv[2]))==NULL)) {
        printf("READ-FAILED");
        return 1;
    }

    //CHOP & LEN DECLARATIONS
    char **ec = chop(ef, ' ');
    char **dicChop = chop(dic, '\n');
    //int dicLen = array_len(dicChop);
    //int ecLen = array_len(ec);

    int i = 0;
    int results[27];
    while(i <= 27) {
        shiftArray(ec, 1);
        results[i] = compareArray(ec, dicChop);
        printf("results[%d]: %d\n",i,(results[i]) );
        i++;
    }

    int shiftValue = 0;
    int resultValue = 0;
    for(i = 0;i < 26; i++) {
        if(results[i] > resultValue){
            resultValue = results[i];
            shiftValue = i+1;
        }
    }

    printf("Here is the return value!: %d", shiftValue);
    shiftString(ef2, shiftValue);
    printf("%s",ef2);
    return 0;
}

//FUNCTIONS~

// Function which passes a char c, and shift value k.
// Returns the char which is shifted by k characters.
void shiftArray(string a[], int shift) {
    int i = 0;
    while (a[i] != NULL) {
        shiftString(a[i], shift);
        i++;
    }
}


<<<<<<< HEAD
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
=======
int compareArray(string words[], string dictWords[]) {
    int i, j, matches = 0;
    string word, dictWord;
    for (i = 0; i < 500; i++) {
        // Check if each word is in the dict
        word = words[i];
        for (j = 0; dictWords[j] != NULL; j++) {
            dictWord = dictWords[j];
            // If they're equivalent, increment the count
            if ((strlen((char*)word)!= 0)&&(strcasecmp((char *) word, (char *) dictWord) == 0)) {
                //printf("%s MATCHES %s\n", word, dictWord);
                matches++;
                break;
>>>>>>> 33976995a93b08c139ce47a44ba782ae78a2f75c
            }
        }
    }
    return matches;
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

string *chop(string s, char c) {
    char **lines;
    int i, j;
    int num_lines;
    int len;

    /* figure out how many lines there are in s */
    num_lines = get_num_lines(s, c);
    printf("There were %d lines\n", num_lines);

    if ((lines = malloc((num_lines + 2) * sizeof(string))) == NULL) return NULL;

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

void shiftString(string s, int shiftNum) {
    int i = 0;
    while(s[i] != 0) {
        if (isalpha(s[i])) {
            s[i] = shift(s[i], shiftNum);
        }
        i++;
    }
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








