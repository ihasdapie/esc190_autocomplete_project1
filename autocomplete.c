//#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
};

int lowest_match(struct term *terms, int nterms, char *substr){
     
    int low = 0;
    int high = nterms - 1;
    int res = -1;
    int sub_length = strlen(substr);

     
    while (low <= high){
         
        // Normal Binary Search Logic 
        int mid = (low + high) / 2;
        
        char test_string[sub_length + 1];
        strncpy(test_string, terms[mid].term, sub_length);
        int result = strcmp(test_string, substr);

        if (result > 0){
            high = mid - 1;
        }
        else if (result < 0){
            low = mid + 1;
        }
        else{
            res = mid;
            high = mid - 1;
        }

    }
    return res;
}

int highest_match(struct term *terms, int nterms, char *substr){

         
    int low = 0;
    int high = nterms - 1;
    int res = -1;
    int sub_length = strlen(substr);
     
    while (low <= high){
         
        // Normal Binary Search Logic 
        int mid = (low + high) / 2;
        
        char test_string[sub_length + 1];
        strncpy(test_string, terms[mid].term, sub_length);

        int result = strcmp(test_string, substr);

        if (result > 0){
            high = mid - 1;
        }
        else if (result < 0){
            low = mid + 1;
        }
        else{
            res = mid;
            low = mid + 1;
        }

    }
    return res;         
}
