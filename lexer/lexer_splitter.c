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

	while (line[i] != 0)
	{
		//pfn("augusto miagola: %c\n", line[i]);
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote = line[i];
			i++;
			//pfn("augusto miagola ancora: %c\n", quote);
			while (line[i] != quote && line[i] != 0)
				i++;
		}
		if (line[i] == '|')
			break ;
		//else if (line[i] == '<' || line[i] == '>')
		//{
		//	operator = line[i];
		//	if (line[i + 1] == operator)
		//		i++;
			//printf("splitto %s su %c\n", line, line[i]);
		//	break;
		//}
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
	ret = (char *) malloc(sizeof(char) * (i) + 1);
	while ((j + r) <= i)
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
