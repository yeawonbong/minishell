char **ft_strinsert(char *str, char set)
{
    int i;
    int start;
    int len;
    char *s;
    char *temp;
    char *subs;

    len = 0;
    i = 0;
    start = 0;
    s = ft_strdup(' ');
    while (str[i])
    {
        if (ft_strchr("<>", str[i]))
        {
            if (str[i] == '<' && str[i + 1] == '<')
            {
                subs = ft_substr(str, start, len);
                temp = ft_strjoin(subs, " << ");
                free(s);
                s = temp;
                start = i + 2;

            }
            else
            {
                s = ft_substr(str, start, i);
                start = i;
            }

        }
        len++;
        i++;
    }
}