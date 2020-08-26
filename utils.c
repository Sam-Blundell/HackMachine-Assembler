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

    for (int i = 15; i > 0; i--)
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
    bin[16] = '\n';
}

#define DEST_SIZE 4
#define COMP_SIZE 8
#define JUMP_SIZE 4

void parse_destination(char[], char[]);

void assemble_c_instruction(char instr[], char bin[])
{

    char dest[DEST_SIZE] = "000";
    char comp[COMP_SIZE];
    char jump[JUMP_SIZE] = "000";

    char *token;

    if (strstr(instr, "=") != NULL)
    {
        token = strtok_r(instr, "=", &instr);
        parse_destination(token, dest);
    }
    if (strstr(instr, ";") != NULL)
    {
        token = strtok_r(instr, ";", &instr);
        // parse_jump(instr, jump);
    }

    for (int i = 0; i < 3; i++)
    {
        bin[i] = '1';
    }

    for (int i = 3; i < 10; i++)
    {
        bin[i] = '0';
    }

    for (int i = 10; i < 13; i++)
    {
        bin[i] = dest[i - 10];
    }

    for (int i = 13; i < 16; i++)
    {
        bin[i] = '0';
    }

    bin[16] = '\n';
}

void parse_destination(char mnemonic[], char dest[])
{
    char *types[] = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
    char *bins[] = {"001", "010", "011", "100", "101", "110", "111"};

    for (int i = 0; i < 7; i++)
    {
        if (strcmp(mnemonic, types[i]) == 0)
        {
            
	    for (int j = 0; j < 3; j++) {
	    	dest[j] = bins[i][j];
	    }
            break;
        }
    }
}
