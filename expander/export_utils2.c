#include "../global.h"


///receives cmd,
// void    handle_quotes(t_command cmd)
// {
//     int         i;
//     char        c;
//     char     *tmp;

//     i = 0;
//     while (&cmd.command[i])
//     {}


// }

//return lowest number among three numbers, currently unused
int mini_mini_sort(int a, int b, int c)
{
    int min;

    min = -1;
    if (a >= 0 && ((b > c && c > a) || (c > b && b > a)))
            min = a;
    if (b >= 0 && ((a > c && c > b) || (c > a && a > b)))
            min = b;
    if (c >= 0 && ((b > a && a > c) || (a > b && b > c)))
            min = c;
    return (min);
}

// int mini_sort(char *str)
// {
//     char set[2];
//     int min;
//     int qi;
//     int wi;
//     int ci;

//     set[0] = '\'';
//     set[1] = '"';
//     set[2] = '$';
//     qi = ft_strchr_len(str, set[0]);
//     wi = ft_strchr_len(str, set[1]);
//     ci = ft_strchr_len(str, set[2]);
//     if (qi >= 0 && qi < wi && wi < ci)
//         min = qi;
//     else if (wi >= 0 && wi < qi && qi < ci)
//         min = wi;
//     else if (ci >= 0 && ci < qi && qi < wi)
//         min = ci;
//     return(min);
// }

//norm-proof version, fetches min nbr out of three
int mini_sort(char *str)
{
    char set[3];
    int min;
    int qi;
    int wi;
    int ci;

    set[0] = '\'';
    set[1] = '"';
    set[2] = '$';
    min = -1;
    qi = ft_strchr_len(str, set[0]);
    wi = ft_strchr_len(str, set[1]);
    ci = ft_strchr_len(str, set[2]);
    if (qi == -1)
        qi = 2147483646;
    if (wi == -1)
        wi = 2147483646;
    if (ci == -1)
        ci = 2147483646;
    if (qi >= 0 && ((wi >= ci && ci > qi) || (ci >= wi && wi > qi)))
        min = qi;
    if (wi >= 0 && ((qi >= ci && ci > wi) || (ci >= qi && qi > wi)))
        min = wi;
    if (ci >= 0 && ((wi >= qi && qi > ci) || (qi >= wi && wi > ci)))
        min = ci;
    return (min);
}

int    expansion_explosion(char *str,char tmp[4095], int *index, char **env)
{
    char    *to_ret;
    char    buff[4095];
    int     i;
    int     j;

write(1, "YOYOYO\n", 7);
    i = *index;
    j = 0;
    while (str[++i] != '\''|| str[i] != '"'
        || str[i] != '$' || str[i] != '\0' || !ft_isspace(str[i]))
    {
        buff[j++] = str[i];
    }
    *index = i;
    i = 0;
    buff[j] = '\0';
    to_ret = exp_tkn(buff, env);
    j = ft_strlen(tmp);
    while (to_ret[i])
        tmp[j++] = to_ret[i++];
    return (i);
}

// char    *new_tkn_aux(char *str, t_command cmd, int i , int k)
// {
//     int f;
//     int c;
//     char tmp[4095];

//     f = mini_sort(str);
//     c = str[f];
//     while (++k < f && (str[k] != c && (c == '"' || c == '\'') || str[k]))
//     {
//         if ((str[k] == '$' && c == '"') || (c != '\'' && str[k] == '$'))
//             i += expansion_explosion(str, tmp, &k, cmd.shell->env);
//         tmp[i] = str[k];
//     }
//     return (tmp);
// }

// char    *new_tkn(char *ol_tkn, t_command cmd)
// {
//     int     i;
//     int     f;
//     int     k;
//     char    tmp[4095];
//     char    c;

//     i = 0;
//     k = -1;
//     if (mini_sort(ol_tkn) >= 0)
//     {
//         while (i < ft_strlen(ol_tkn))
//         {
//             new_tkn_aux(ol_tkn, cmd, i, k);
//             // f = mini_sort(ol_tkn);
//             // c = ol_tkn[f];
//             // while (++k < f)
//             // {
//             //     if (ol_tkn[k] == '$')
//             //         i += expansion_explosion(ol_tkn,tmp, &k, &cmd.shell->env);
//             //     tmp[i] = ol_tkn[k];
//             //     while (ol_tkn[++k] != c)
//             //     {
//             //         if (ol_tkn[k] == '$')
//             //             i += expansion_explosion(ol_tkn, tmp, &k, &cmd.shell->env);
//             //         tmp[i] = ol_tkn[k];
//             //     }
//             // }
//         }
//         return (tmp);
//     }
//     else
//         return(ol_tkn);
// }

char *new_tkn(char *ol_tkn, t_command *cmd)
{
    size_t i;
    int f;
    int k;
    char tmp[4095];
    char c;

    pfn("%t new_tkn %s", ol_tkn);
    i = 0;
    k = -1;
    pfn("%t sort = %d", mini_sort(ol_tkn));
    if (mini_sort(ol_tkn) >= 0)
    {
        while (i < ft_strlen(ol_tkn))
        {
            pfn("%1t %d", i);

            f = mini_sort(ol_tkn);
            c = ol_tkn[f];
            while (k <= f || ((ol_tkn[k + 1] != c && (c == '"' || c == '\''))
                || ol_tkn[k + 1]))
            {
                pfn("dead loop");
                if ((ol_tkn[k] == '$' && c == '"') || (c != '\'' && ol_tkn[k] == '$'))
                    i += expansion_explosion(ol_tkn, tmp, &k, cmd->shell->env);
                tmp[i++] = ol_tkn[k++];
            }
            i++;
        }
    }
    free (ol_tkn);
    ol_tkn = ft_strdup(tmp);
    return (ol_tkn);
}
