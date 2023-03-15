#include "../global.h"

void	lexer_error(char *message) //example and sketch of an exit error function, not really integrated with the minishell
{
	printf("Error: %s\n", message);
	//free(com->shell->input);
	//free(com);
}

//looks for the index where to split the line between command and line yet to be checked.
int	split_operator_line(char *line, int i)
{
	char	quote;

	while (line[i])
	{
		quote = line[i];
		if (ft_isquote(quote))
		{
			i++;
			while (line[i] && line[i] != quote)
				i++;
		}
		if (line[i] && line[i] == '|')
			return (i + 1);
		i++;
	}
	return (i);
}

//splits the line with the following command from the line yet to be checked
char	*split_operator(char *line, int *ff, int not_new)
{
	static int	r;
	char		*ret;
	int			i;
	int			j;

	if (!r || !not_new)
		r = 0;
	j = 0;
	i = split_operator_line(line, *ff);
	ret = ft_calloc(sizeof(char), (i + 1));
	if (!ret)
		return ('\0');
	while ((j + r) < i)
	{
		ret[j] = line[j + r];
		j++;
	}
	ret[j] = '\0';
	*ff = i;
	r += j;
	return (ret);
}

//splits the line yet to be controlled from the command already split
/*char	*split_line(char *line)
{
	char	*ret;
	int		i;
	int		j;

	j = 0;
	//i = split_operator_line(line);
	i = 0;
	while (line[i] != 0)
	{
		ret[j] = line[i];
		j++;
		i++;
	}
	return (ret);
}*/
