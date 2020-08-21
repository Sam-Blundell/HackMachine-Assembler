#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

#define MAX_FILENAMESIZE 64
#define MAX_LINELENGTH 80
#define BIN_STRING_LENGTH 18

int main(int argc, char **argv)
{
    char output_file[MAX_FILENAMESIZE], instr[MAX_LINELENGTH], bin[BIN_STRING_LENGTH];
    FILE *readptr, *writeptr;

    if (argc < 2)
    {
        fprintf(stderr, "Error: Program requires at least one input filename argument.\nUsage: '%s <file>'\n", argv[0]);
        return -1;
    }

    readptr = fopen(argv[1], "r");
    if (readptr == NULL)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return -1;
    }

    //  if no filename argument, default to "out.hack"
    if (argv[2] == NULL)
    {
        sprintf(output_file, "out.hack");
    }
    else
    {
        sprintf(output_file, "%s", argv[2]);
    }

    writeptr = fopen(output_file, "w");

    while (fgets(instr, sizeof instr, readptr) != NULL)
    {
        trim_instruction(instr);

        if (*instr == '\n')
            continue;

        if (*instr == '@')
        {
            assemble_a_instruction(instr, bin);
        }
        else
        {
            assemble_c_instruction(instr, bin);
        }

        fprintf(writeptr, "%s", bin);
    }

    fclose(readptr);
    fclose(writeptr);

    return 0;
}