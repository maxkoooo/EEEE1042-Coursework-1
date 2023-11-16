#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*operational functions*/
//find largest float in array with total number of floats, N
float findLargestF(float *arr, int N){
    int i;
    
    float max = arr[0]; //initialise the maximum element

    for (i=1;i<N;i++){  
        if(arr[i] > max){   //compares all elements of the array with the current max
            max = arr[i];   //replaces max if larger element is found
        }
    }

    return (max);
}

//find longest string in array with total number of strings, W
int findLongestS(char **arr, int W){
    int i, l;
    
    int max = 0;    //initialise the maximum element

    for(i=0;i<W;i++){
        l = strlen(arr[i]);

        if(l > max){    //compares current string length with current max
            max = l;    //replaces max if larger string length found
        }
    }

    return (max);
}

//resets the bin, freq, and number of bins, N, of the histogram
void clearHist(float *bin, float *freq, int *N){
    memset(bin, 0, 100*sizeof(float));      //clear bin array
    memset(freq, 0, 100*sizeof(float));     //clear freq array
    *N = 0;                        //reset number of bins
}

//sorts strings in word array into their length and frequency with total strings, W, and total bins, N
void sortWordLen(char **word, float *bin, float *freq, int W, int *N){
    int i, l;

    *N = findLongestS(word, W); //gets number of bins
    
    for(i=0;i<*N;i++){   //initialises bin number up to the L of the largest string
        bin[i] = i+1;
    }
    
    for(i=0;i<W;i++){
        l = strlen(word[i]);    //calculates length of word
        freq[l-1]++;    //increments frequency of the particular bin (starts array index at 0)
        free(word[i]);  //frees the allocated memory
    }
}


/*file read functions*/
//reads data from .hist file and stores the data in 2 arrays, and gets total number of bins, N
void readHistFile(char *filename, float *bin, float *freq, int *N, int L){
    FILE *f; //file pointer
    
    if((f=fopen(filename,"r")) != NULL){ //ensure that file exists
        int i = 0;

        printf("\nReading .hist file...\n");

        while((fscanf(f, "%f %f\n", &bin[i], &freq[i])) != EOF){ //scans 2 floats from each line of the file into bin[i] and freq[i] until the end of file (EOF) is reached
            if(i < L){  //prevents overflowing the bin and freq array
                i++;    //index increment
            }
            else{
                printf("\nArray limit of %d reached, terminating to prevent array overflow.\n", L);
                printf("Histogram will be limited to the first %d bins of the file.\n", L);
                break;
            }
        }
        
        *N = i; //gets number of bins
    }
    else{ //error: file specified doesn't exist
        printf("\nFile not found! :(\n");
    }
}

//reads data from .txt file and stores it in an array, and gets total number of words in the file, W
void readTextFile(char *filename, char **word, int *W, int L){
    FILE *f; //file pointer

    char str[50]; //buffer to store string before passing it to word array

    if((f=fopen(filename,"r")) != NULL){ //ensure that file exists
        int i = 0;

        printf("\nReading .txt file...\n");

        while((fscanf(f, "%49[a-zA-Z0-9'] %*[^a-zA-Z0-9']", str)) != EOF){  //scans strings excluding punctuation from the file until the end of file (EOF) is reached
            if(i<L){    //prevents overflowing the word array
                word[i] = (char*)calloc(strlen(str) + 1, sizeof(char)); //memory allocation based on string length
                strcpy(&*word[i], str); //copies data from the buffer into the corresponding word array
                i++; //index increment
            }
            else{
                printf("\nWord array limit of %d reached, terminating to prevent array overflow.\n", L);
                printf("Histogram will be limited to the first %d words of the file.\n", L);
                break;
            }
        }
        
        *W = i; //gets number of words in the file
    }
    else{ //error: file specified doesn't exist
        printf("\nFile not found! :(\n");
    }
}


/*histogram plotting functions*/
//prints data from bin and freq array
void printHist(float *bin, float *freq, int N){
    int i;

    printf("\n|===bin===|===freq===|\n");

    for(i=0;i<N;i++){
        printf("|   %6.2f|    %6.2f|\n", bin[i], freq[i]); //prints data to 2 decimal places in a table
    }

    printf("|=========|==========|\n");
}

//plots a horizontal histogram with number of bins, N, L of the histogram bars, S, and histogram style, B
void plotHistH(float *bin, float *freq, int N, int S, char B){
    int i,j;
    int l[N];   //initialise array for histogram bar length

    float m = findLargestF(freq, N);    //finds the mode of the histogram

    for(i=0;i<N;i++){
        l[i] = S*freq[i]/m;    //length of histogram bars (integer value) using ratio of the freq and mode
    }
    
    printf("|-------------|\n");
    printf("|bin   |  freq|\n");
    printf("|-------------|\n");
    
    for(i=0;i<N;i++){
        printf("|%-6.2f|%6.2f|", bin[i], freq[i]); //prints data to 2 decimal places in a table
        
        for(j=1;j<=l[i];j++){  //prints histogram up to value l
            printf("%c", B);
        }
        
        printf("\n");
    }
    
    printf("|-------------|\n");
}

//plots a vertical histogram with number of bins, N, L of the histogram bars, S, and histogram style, B
void plotHistV(float *bin, float *freq, int N, int S, char B){
    int i,j;
    int l[N];   //initialise array for histogram bar length
   
    float m = findLargestF(freq, N);    //finds the mode of the histogram

    for(i=0;i<N;i++){
        l[i] = S*freq[i]/m;    //length of histogram bars (integer value) using ratio of the freq and mode
    }
    
    for(j=S;j>=0;j--){   //iterate from maximum histogram bar L to 0 (top to bottom)
        for(i=0;i<N;i++){   //iterate over every bin (left to right)
            if(l[i]>j){
                printf(" %c ", B); //print * if length of bar is greater than the current row
            }
            else{
                printf("   "); //print space if length of bar is smaller than the current row
            }
        }
        printf("\n");
    }
    
    for(i=0;i<3*N;i++){
        printf("-");    //prints a line so that it looks prettier
     }

    printf("\n");
    
    for(i=0;i<N;i++){   //prints out bin as integer at the bottom
        if(i<9){        
            printf(" %d ", (int)bin[i]);    //1 digit number prints with 2 spaces (for alignment)
        }
        else{
            printf(" %d", (int)bin[i]);     //2 digit number prints with 1 space (for alignment)
        }
    }
}