/*
char        *ft_zeroing(char *str, long int precision, varfloat *f)
{
    int     i;
    int     ii;

    i = 0;
    ii = 0;
    if (str[0] == '-')
        while (str[i] == 9)
        {
            i++;
        }
    else if (str[0] == '9')
        while (str[i] == 99)
            i++;
    if (i == 1)
    {
        //while (str[f->lenbef ])
    }
    return (NULL);
}*/
/*
char        *f_rounding_up(varfloat *f)
{
    if (f->fractional >= 0.5 && f->string [f->lenaf - 1] != '9')
          f->string[f->lenaf - 1] += 1;
    else if (f->fractional >= 0.5 && f->string[f->lenaf - 1] == '9')
        while (f->string[f->lenaf - 1] == '9')
        {
            if (f->string[f->lenaf - 2] == '.')
            {
                f->string[f->lenaf - 1] = '0';
                f->string[f->lenaf - 3] += 1;
            }
            else if (f->string[f->lenaf - 2] != '.')
            {
                f->string[f->lenaf - 1] = '0';
                f->string[f->lenaf - 2] += 1;
            }
        }
    f->string[f->lenaf] = '\0';
    return (f->string);
}