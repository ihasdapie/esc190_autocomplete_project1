#include "autocomplete.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_term(struct term t) {
    printf("%s: %f\n", t.term, t.weight);
}


void print_term_array(struct term * t, int num) {
    for (int i = 0; i < num; i++) {
        printf("%s %f\n", t[i].term, t[i].weight);
    }
}






int lex_cmp_func(const void * t1, const void* t2) {
    return strcmp(((struct term*) t1)->term, ((struct term*) t2)->term);
}

void read_in_terms(struct term **terms, int *pnterms, char *filename){

    FILE* fp;
    int n_cities;
    int linesize = 200;
    char line[linesize];
    char* delim = "	";
    struct term* term_array;

    fp = fopen(filename, "r");
    fscanf(fp, "%d", &n_cities);

    term_array = (struct term*) malloc(sizeof(struct term) * n_cities);

    for (int i = 0; i < n_cities; i++) {
        struct term tt;
        fgets(line, linesize, fp);
        char* ptr = strtok(line, delim);
        int flag = 0;
        while (ptr) {
            if (flag == 0) {
                tt.weight = (double) atoi(ptr);
                flag = 1;
            } else {
                strcpy(tt.term, ptr);
                flag = 0;
            }
            ptr = strtok(NULL, delim);
        }
        term_array[i] = tt;
    }

    qsort(term_array, n_cities, sizeof(struct term), lex_cmp_func);

    *terms = term_array;
    *pnterms = n_cities;

    /* print_term_array(term_array, n_cities); */
}



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
