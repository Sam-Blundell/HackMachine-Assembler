#include <stdio.h>

#define MAX_FILENAMESIZE 64

int main(int argc, char *argv[])
{
    char output_file[MAX_FILENAMESIZE];
    FILE *readptr, *writeptr;

    if (argc < 2)
    {
        printf("Err:\nProgram requires at least one inputfilename argument: './hackasm <file>'\n");
        return -1;
    }

    readptr = fopen(argv[1], "r");
    if (readptr == NULL)
    {
        printf("ERR: Input file not found in directory.\n");
        return -1;
    }

    if (argv[2] == NULL)
    {
        sprintf(output_file, "out.hack");
    }
    else
    {
        sprintf(output_file, "%.63s", argv[2]);
    }

    writeptr = fopen(output_file, "w");

    fclose(readptr);
    fclose(writeptr);

    return 0;
}