#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void assemble_a_instruction(char instr[], char bin[])
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

#define DEST_SIZE 3
#define COMP_SIZE 7
#define JUMP_SIZE 3

void assemble_c_instruction(char instr[], char bin[])
{

    // dest=comp;jump
    char dest[DEST_SIZE] = "000";
    char comp[COMP_SIZE];
    char jump[JUMP_SIZE] = "000";

    char *token;

    printf("%s", instr);

    if (strstr(instr, "=") != NULL)
    {
        token = strtok_r(instr, "=", &instr);
        printf("%s <- destination\n%s <- computation\n", token, instr);
    }
    if (strstr(instr, ";") != NULL)
    {
        token = strtok_r(instr, ";", &instr);
        printf("%s <- computation\n%s <- jump\n", token, instr);
    }
    // if (strstr(instr, ";") != NULL)
    // {
    //     token = strtok_r(instr, ";", &instr);
    //     printf("%s <- token\n%s <- remainder\n", token, instr);
    // }

    // if (strstr(instr, "=") != NULL)
    // {
    //     desttoken = strtok(instr, "=");
    //     comptoken = strtok(NULL, "\n");
    // }
    // else if (strstr(instr, ";") != NULL)
    // {
    //     comptoken = strtok(instr, ";");
    //     jumptoken = strtok(NULL, "\n");
    // }

    bin[0] = '1';
    for (int i = 1; i < 17; i++)
    {
        bin[i] = '0';
    }
    bin[17] = '\n';
}

// struct lookup
// {
//     char *name;
//     char *bin;
// };

// void parse_dest(char dest[])
// {
//     struct lookup dest
//     {
//     }
// }