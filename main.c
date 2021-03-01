#include "autocomplete.h"
#include "stdio.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "./cities.txt");
    /* int lm = lowest_match(terms, nterms, "Tordd"); */
    /* int hm = highest_match(terms, nterms, "Tordd"); */

    /* /1* print_term_array(terms, nterms); *1/ */

    /* printf("%d, %d\n", lm, hm); */


    
    struct term *answer;
    int n_answer;

    autocomplete(&answer, &n_answer, terms, nterms, "Toronto, Ontario, Canada");

    print_term_array(answer, n_answer);


    /* //free allocated blocks here -- not required for the project, but good practice */
    return 0;
}

