#include <stdio.h>

#define MAX_FILENAMESIZE 64
#define MAX_LINELENGTH 80

void trim_instruction(char *line)
{
    char *copy = line;

    while (*copy != '\0')
    {
        if (*copy == '/' && *(copy + 1) == '/')
        {
            *line++ = '\n';
            break;
        }

        if (*copy != ' ' && *copy != '\t')
        {
            *line++ = *copy;
        }
        copy++;
    }
    *line = '\0';
}

int main(int argc, char *argv[])
{
    char output_file[MAX_FILENAMESIZE], line[MAX_LINELENGTH];
    FILE *readptr, *writeptr;

    if (argc < 2)
    {
        printf("Err:\nProgram requires at least one input filename argument: './hackasm <file>'\n");
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
        sprintf(output_file, "%s", argv[2]);
    }

    writeptr = fopen(output_file, "w");

    while (fgets(line, sizeof line, readptr) != NULL)
    {
        trim_instruction(line);
        if (*line != '\n')
        {
            printf("%s", line);
            fprintf(writeptr, "%s", line);
        }
    }

    fclose(readptr);
    fclose(writeptr);

    return 0;
}