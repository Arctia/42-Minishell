#include "./lexer.h"

//looks for the index where to split the line between 
// command and line yet to be checked.
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
		return (NULL);
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

int	check_operator(char *line, int i)
{
	int	flag;

	flag = 0;
	while (ms_isoperator(line[i]) || ft_isspace(line[i]))
	{	
		if (!line[i + 1])
			return (-1);
		if (ms_isoperator(line[i]) == 1)
		{
			if (ms_isoperator(line[i + 1]) && line[i + 1] == '|')
				return (-1);
			else if (ms_isoperator(line[i + 1]) && line[i + 1] != line[i])
				return (-1);
			else if (ms_isoperator(line[i + 1]) && ms_isoperator(line[i + 2]))
				return (-1);
			else if (ms_isoperator(line[i] == 1) && flag == 1)
				return (-1);
		}
		else if (ft_isspace(line[i]) == 1)
			flag = 1;
		i++;
	}
	return (0);
}
