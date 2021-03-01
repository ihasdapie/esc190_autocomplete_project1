#include "autocomplete.h"
#include "stdio.h"

int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "./cities.txt");
    /* print_term_array(terms, nterms); */
    /* int lm = lowest_match(terms, nterms, "Tor"); */
    /* int hm = highest_match(terms, nterms, "Tor"); */

    /* print_term_array(terms, nterms); */

    
    struct term *answer;
    int n_answer;

    autocomplete(&answer, &n_answer, terms, nterms, "Tor");

    print_term_array(answer, n_answer);


    /* //free allocated blocks here -- not required for the project, but good practice */
    



    return 0;
}

