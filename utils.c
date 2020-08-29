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
void parse_jump(char[], char[]);
void parse_comp(char[], char[]);

void assemble_c_instruction(char instr[], char bin[])
{

    char dest[DEST_SIZE] = "000";
    char comp[COMP_SIZE] = "0000000";
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
        parse_jump(instr, jump);
        parse_comp(token, comp);
    }
    else
    {
        parse_comp(instr, comp);
    }

    for (int i = 0; i < 3; i++)
    {
        bin[i] = '1';
    }

    for (int i = 3; i < 10; i++)
    {
        bin[i] = comp[i - 3];
    }

    for (int i = 10; i < 13; i++)
    {
        bin[i] = dest[i - 10];
    }

    for (int i = 13; i < 16; i++)
    {
        bin[i] = jump[i - 13];
    }

    bin[16] = '\n';
}

void parse_destination(char mnemonic[], char dest[])
{
    char *types[] = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
    char *bins[] = {"001", "010", "011", "100", "101", "110", "111"};

    for (int i = 0; i < 7; i++)
    {
        if (strncmp(mnemonic, types[i], 3) == 0)
        {

            for (int j = 0; j < 3; j++)
            {
                dest[j] = bins[i][j];
            }
            break;
        }
    }
}

void parse_jump(char mnemonic[], char jump[])
{
    char *types[] = {"JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
    char *bins[] = {"001", "010", "011", "100", "101", "110", "111"};

    for (int i = 0; i < 7; i++)
    {

        if (strncmp(mnemonic, types[i], 3) == 0)
        {
            for (int j = 0; j < 3; j++)
            {
                jump[j] = bins[i][j];
            }
            break;
        }
    }
}

void parse_comp(char mnemonic[], char comp[])
{
    char *types[] = {"0", "1", "-1", "D", "A",
                     "M", "!D", "!A", "!M", "-D",
                     "-A", "-M", "D+1", "A+1", "M+1",
                     "D-1", "A-1", "M-1", "D+A", "D+M",
                     "D-A", "D-M", "A-D", "M-D", "D&A",
                     "D&M", "D|A", "D|M"};

    char *bins[] = {"101010", "111111", "111010", "001100", "110000",
                    "110000", "001101", "110001", "110001", "001111",
                    "110011", "110011", "011111", "110111", "110111",
                    "001110", "110010", "110010", "000010", "000010",
                    "010011", "010011", "000111", "000111", "000000",
                    "000000", "010101", "010101"};

    printf("\t%s\n", mnemonic);

    for (int i = 0; i < 28; i++)
    {

        if (strncmp(mnemonic, types[i], 3) == 0)
        {
            for (int j = 1; j < 7; j++)
            {
                comp[j] = bins[i][j - 1];
            }
            break;
        }
    }

    if (strstr(mnemonic, "M") != NULL)
    {
        comp[0] = '1';
    }
    else
    {
        comp[0] = '0';
    }
}