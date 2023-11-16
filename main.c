#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "histogram.h"

int main(int argc, char **argv){
    int L = 100;        //array limits

    float bin[L];       //memory allocation for the bin of the histogram
    float freq[L];      //memory allocation for the frequency of the histogram
    char *word[5*L];    //memory allocation for storing strings from a .txt file 

    int N = 0;          //initialisation for number of bins of the histogram
    int W = 0;          //initialisation for number of words in the file
    
    int S = 25;         //initialisation for the maximum size of the bars of the histogram
    char B = 'o';       //for setting the style of the histogram bars

    argc = 3;
    argv[1] = "input.hist";
    argv[2] = "input.txt";

    
    if (argc>1){        //process files if input is given
        /*.hist output*/
        readHistFile(argv[1], bin, freq, &N, L);   //reads histogram file
        printHist(bin, freq, N);                //prints histogram data

        printf("\n===horizontal histogram===\n");   //plots horizontal histogram
        plotHistH(bin, freq, N, S, B);

        printf("\n===vertical histogram===\n");     //plots vertical histogram
        plotHistV(bin, freq, N, S, B);

       
        /*.txt output*/
        printf("\n\n>===word length histogram===<\n");

        clearHist(bin, freq, &N);   //clear previous histogram data
        
        if(argc>2){
            readTextFile(argv[2], word, &W, 5*L);    //reads text file

            printf("\nNumber of words in the file: %d\n", W);   //prints number of words in the file

            sortWordLen(word, bin, freq, W, &N);    //sorts word lengths

            printf("\nPlotting histogram...\n");    //plots word length frequency histogram
     
            printf("\n===horizontal histogram===\n");   //plots horizontal histogram
            plotHistH(bin, freq, N, S, B);

            printf("\n===vertical histogram===\n");     //plots vertical histogram
            plotHistV(bin, freq, N, S, B);
        }
        else{
            printf("No .txt file specified.");   //error if no .txt file specified
        }
    }
    else{   //error: no file specified
        printf("No file specified, please input a valid file name.\n");
    }

    return(0);
}