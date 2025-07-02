#include <stdio.h>
#define MAXLINE 1000
#define TAB_WIDTH 8

char inLine[MAXLINE];
char outLine[MAXLINE];

// the same getline() func as in the book
int gline(int lim) {
    int i, c;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) 
        inLine[i]=c;
    if (c=='\n') {
        inLine[i]=c;
        ++i;
    }
    inLine[i]='\0';
    return i;
}

void entab() {
    // displayCol is the actual column the cursor is at, instead of the array column inPos
    int inPos, outPos = 0, displayCol = 0, spaceCount = 0;
    for (inPos = 0; inPos<MAXLINE && inLine[inPos]!='\0'; ++inPos) {
        char c = inLine[inPos];
        if (c == ' ') {
            ++spaceCount;
            ++displayCol;
        } else {
            if (spaceCount > 0) {
                // calculate first and last column
                int fromCol = displayCol - spaceCount;
                int toCol   = displayCol;
                // first tab stop after fromCol
                int firstStop = ((fromCol / TAB_WIDTH) + 1) * TAB_WIDTH;
                // calc number of tabs and spaces required
                int nTabs = (toCol>=firstStop) + (toCol - firstStop) / TAB_WIDTH;
                int nSpaces = toCol - (nTabs > 0 ? (toCol / TAB_WIDTH * TAB_WIDTH) : fromCol);

                for (int t = 0; t < nTabs; ++t)
                    outLine[outPos++] = '\t';
                for (int s = 0; s < nSpaces; ++s)
                    outLine[outPos++] = ' ';
                spaceCount = 0;
            }
            // add the non-space char to outLine
            outLine[outPos++] = c;
            // advance displayCol (tabs jump to next stop)
            // this modifies displayCol only for the non-space char
            if (c == '\t')
                displayCol = (displayCol / TAB_WIDTH + 1) * TAB_WIDTH;
            else 
                ++displayCol;
        }
    }
    outLine[outPos] = '\0';
}

int main() {
    int len;
    while ((len = gline(MAXLINE)) > 0) {
        entab();
        printf("%s", outLine);
    }
    return 0;
}