#include <stdio.h>
#define MAXLINE 1000
#define TAB_STOP 8     // A new tab every 8 columns

int gline(char line[], int lim) {  // the same getline() func as in the book
    int i, c;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) 
        line[i]=c;
    if (c=='\n') {
        line[i]=c;
        ++i;
    }
    line[i]='\0';
    return i;
}

void copy(char from[], char to[], int FROMindx, int TOindx) {
    int i;
    i=0;
    while ((to[TOindx+i]=from[FROMindx+i]) != '\0')
        ++i;
    return;
}

void detab(char line[], int len) {  
    if (len==1) { // handle empty lines 
        return;
    }
    char trail[MAXLINE];
    int ntab = 1; // which tab field are we in?
    for (int i=0; i<=MAXLINE; ++i) {
        if (i>ntab*TAB_STOP-1)
            ++ntab;
        if (line[i]=='\t') {
            copy(line, trail, i+1, 0);
            for (int j=i; j<=TAB_STOP*ntab-1; ++j)
                line[j]=' '; // insert blanks until the current tab field is covered.
            copy(trail, line, 0, TAB_STOP*ntab); // copy remaining chars from trail[] to line[]
        }
    }
}

int main() {
    char ln[MAXLINE];
    int len;
    while ((len = gline(ln, MAXLINE)) > 0) {
        detab(ln, len);
        printf("%s", ln);
    } 
    return 0;
}

