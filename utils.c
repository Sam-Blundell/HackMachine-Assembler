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