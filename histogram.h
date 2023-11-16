#include <stdio.h>
#include <stdlib.h>

/*operational functions*/
float findLargestF(float *arr, int N);
int findLongestS(char **arr, int W);
void clearHist(float *bin, float *freq, int *N);
void sortWordLen(char **word, float *bin, float *freq, int W, int *N);

/*file read functions*/
void readHistFile(char *filename, float *bin, float *freq, int *N, int L);
void readTextFile(char *filename, char **word, int *W, int L);

/*histogram print functions*/
void printHist(float *bin, float *freq, int N);
void plotHistH(float *bin, float *freq, int N, int S, char B);
void plotHistV(float *bin, float *freq, int N, int S, char B);