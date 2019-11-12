int         ft_num_len(int num, int base)
{
    int     i;

    i = 0;
    if (num < 0)
    {
        num = num * (-1);
        i++;
    }
    while (num > 0)
    {
        num = num / base;
        i++;
    }
    return (i);
}
