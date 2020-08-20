#include <stdio.h>
#include <stdlib.h>

void trim_instruction(char *inst)
{
    char *copy = inst;

    while (*copy != '\0')
    {
        if (*copy == '/' && *(copy + 1) == '/')
        {
            *inst++ = '\n';
            break;
        }

        if (*copy != ' ' && *copy != '\t')
        {
            *inst++ = *copy;
        }
        copy++;
    }
    *inst = '\0';
}

void *assemble_a_instruction(char instr[], char bin[])
{

    int tempint = strtol((instr + 1), NULL, 10);

    for (int i = 16; i > 0; i--)
    {
        if (tempint % 2 == 1)
        {
            bin[i] = '1';
        }
        else
        {
            bin[i] = '0';
        }
        tempint = tempint / 2;
    };

    bin[0] = '0';
    bin[17] = '\n';
}