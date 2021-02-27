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

int weight_cmp_func(const void * t1, const void* t2) {
    return ((struct term*) t1)->weight < ((struct term*) t2)->weight;
}
void read_in_terms(struct term **terms, int *pnterms, char *filename){

    FILE* fp;
    int f_nterms;
    int linesize = 200;
    char line[linesize];
    char* delim = "	";
    struct term* term_array;

    fp = fopen(filename, "r");

    fgets(line, linesize, fp);
    f_nterms = atof(line);



    /* fscanf(fp, "%d", &f_nterms); */

    term_array = (struct term*) malloc(sizeof(struct term) * f_nterms);

    for (int i = 0; i < f_nterms; i++) {
        struct term tt;
        fgets(line, linesize, fp);
        char* ptr = strtok(line, delim);
        int flag = 0;
        while (ptr) {
            if (flag == 0) {
                tt.weight = atof(ptr);
                flag = 1;
            } else {
                ptr[strcspn(ptr, "\n")] = 0;   // removing "\n"
                strcpy(tt.term, ptr);
                flag = 0;
            }
            ptr = strtok(NULL, delim);
        }
        term_array[i] = tt;
    }

    qsort(term_array, f_nterms, sizeof(struct term), lex_cmp_func);

    *terms = term_array;
    *pnterms = f_nterms;

    /* print_term_array(term_array, f_nterms); */
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




void autocomplete(struct term **answer, int *n_answer, struct term *terms,
        int nterms, char *substr){
    // The function takes terms (assume it is sorted lexicographically), the number of terms nterms, and the 
    // query string substr, and places the answers in answer, with *n_answer being the number of answers. The answer should be sorted by weight.

    
    // we want to know the range where our answers can be
    // get high and lowest bound
    // because the items are sorted lexicographically, all items between
    // lower_bound and higher_bound all match
    
    struct term * answer_array = NULL;
    size_t term_size = sizeof(struct term);


    int lower_bound = lowest_match(terms, nterms, substr);
    int higher_bound = highest_match(terms, nterms, substr);


    if (lower_bound != -1){
        // n_answer is simply difference between higher_bound and lower_bound + 1
        *n_answer = higher_bound - lower_bound + 1;

        answer_array = (struct term*) malloc(term_size * (*n_answer));

        // construct term array since in answer_array
        memcpy(answer_array, &terms[lower_bound] , (*n_answer)*term_size);
        qsort(answer_array, *n_answer, sizeof(struct term), weight_cmp_func);

        // set variables as required
        *answer = answer_array;
    }
    else if (lower_bound == -1){
        // no match, so answer is 0
        *n_answer = 0;

        //creates a empty array
        answer_array = NULL;

        // set variables as required
        *answer = answer_array;
    }
}








