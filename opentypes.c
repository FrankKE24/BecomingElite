#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio_ext.h>

int main(int argc, char const *argv[])
{
    //FILE *pfile = fopen("plcs.txt", "m");
    //FILE *pfile = fopen("plcs.txt", "rx");
    //FILE *pfile = fopen("plcs.txt", "c");
    FILE *pfile = fopen("plcss.txt", "re");
    if (pfile == NULL){
        fprintf(stderr, "Couldnt open file");
        perror("\nCouldnt open file");
        return EXIT_FAILURE;
    }

    int state = __freading(pfile);

    if (state== 0)
    {
        printf("File was not last read from");
    }

    if(state ==1){
        printf("File was last read from");
    }
    char buffer[100];


    while (fgets(buffer, 100, pfile))
    {
        printf("%s", buffer);
    }

    fclose(pfile);
    
    
    return 0;
}
