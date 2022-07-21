#include "list.h"


char	*get_strdup(char *src, int number)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * number + 1);
	if (new == NULL)
		exit(1);
	while (i < number)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	check_group(char c)
{
	if (c == ' ')
		return (SPACES);
	else if (c == '<' || c == '>')
		return (REDIR);
	else if (c == '\'' || c == '\"')
		return (QUOTE);
	else if (c == '|')
		return (PIP);
	else if (c == '\0')
		return (ZERO);
	return (WORD);
}

int	push_syntax(t_list *list, char *str, int index, int len)
{
	t_node	*new;
	char	*temp;

	temp = get_strdup(&str[index], len);
	new = new_node(temp);
	new->group = check_group(str[0]);
	push_node_back(list, new);
	free(temp);
	return (len);
}

int	label_group(t_list *split_list, char *str)
{
	int		i;
	int		add_index;
	char	*temp;

	i = 0;
	add_index = 0;
	if (check_group(str[0]) == PIP)
	{
		add_index = push_syntax(split_list, str, 0, 1);
		split_list->pipe_num++;
	}
	else if (check_group(str[0]) == REDIR)
	{
		if (str[0] == str[1])
			add_index = push_syntax(split_list, str, 0, 2);
		else
			add_index = push_syntax(split_list, str, 0, 1);
	}
	else if (check_group(str[0]) == QUOTE)
	{
		i = 1;
		while (str[0] != str[i] && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			split_list->state = ERROR;
		add_index = push_syntax(split_list, str, 1, i - 1) + 2;
	}
	else if (check_group(str[0]) == SPACES)
	{
		while (str[i] == ' ')
			i++;
		add_index = i;
	}
	return (add_index);
}

t_list *shell_split(char *str)
{
	t_list	*split_list;
	int		check;
	int		i;
	int		j;

	i = 0;
	split_list = new_list();
	if (str[0] == '\0')
		split_list->state = BLANK;
	while (str[i] != '\0')
	{
		j = 0;
		while (!check_group(str[i + j])) // 명령어 녀석들 아니면 세주는거야!! 쫄지마
			j++;
		if (j != 0)
			push_syntax(split_list, &str[i], 0, j);
		check = label_group(split_list, &str[i + j]);
		j += check;
		i = i + j;
		if (i > ft_strlen(str))
			break;
	}
	return (split_list);
}