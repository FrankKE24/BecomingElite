#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

int string_compare(const void *a, const void *b){
    return strcmp(*(const char **)a, *(const char **)b);
}

int compare_doubles(const void *a, const void *b){
    const double *da = (const double *)a;
    const double *db = (const double *)b;

    return (*da > *db) - (*da < *db);
}

void *lfind(const void *key, const void *base, 
    size_t *nmemb, size_t size, int(*compar)(const void *, const void *)){

        int i;
        for (int i = 0; i < *nmemb; i++)
        {
            if(compar(key, (const char *)base + i * size) == 0){
                return (void *)((char *)base + i *size);
            }
        }
        
        return NULL;
}


int main(int argc, char const *argv[])
{
    const double doubles[] = {33545, 5434, 424234, 455,3000, 5353};
    size_t count = sizeof(doubles)/sizeof(doubles[0]);

    const double key = 33545;
    const double *result = lfind(&key, doubles, &count, sizeof(double *), compare_doubles);
    if(result != NULL){
        printf("Found: %.f\n", *result);
        return EXIT_SUCCESS;
    }
    else{
        printf("%f Not found\n", key);
        return EXIT_FAILURE;
    }


    /*const char *foods[] = {"chapati", "ugali", "chicken", "fish", "beef", "pork"};
    size_t count = sizeof(foods)/sizeof(foods[0]);
    const char *key  = "cchicken";

    const char **result = lfind(&key, foods, &count, sizeof(char *), string_compare);
    if(result != NULL){
        printf("Found: %s\n", *result);
        return EXIT_SUCCESS;
    }
    else{
        printf("%s Not found\n", key);
        return EXIT_FAILURE;
    }*/
    return 0;
}
