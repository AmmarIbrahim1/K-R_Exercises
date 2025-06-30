#include <stdio.h>
#define MAXLINE 1000
#define TAB_WIDTH 8     // A tab spans 8 columns

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
    char trail[MAXLINE];
    int tabN = 1; // which tab field are we in?
    for (int i=0; i<=MAXLINE && line[i]!='\n'; ++i) {
        if (i>tabN*TAB_WIDTH-1)
            ++tabN;
        if (line[i]=='\t') {
            copy(line, trail, i+1, 0);
            for (int j=i; j<=TAB_WIDTH*tabN-1; ++j)
                line[j]=' '; // insert blanks until the current tab field is covered.
            copy(trail, line, 0, TAB_WIDTH*tabN); // copy remaining chars from trail[] to line[]
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

