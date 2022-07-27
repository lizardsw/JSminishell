#include "parsing.h"

int	cmd_expand(char **str_storage, char *str)
{
	char	*front_str;
	char	*back_str;
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != '\"' && str[i] != '\'' && str[i] != '\0' && str[i] != '$')
			i++;
	front_str = *str_storage;
	back_str = get_strdup(str, i);
	*str_storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	return (i);
}

int	squote_expand(char **str_storage, char *str)
{
	char	*front_str;
	char	*back_str;
	int		i;
	
	front_str = *str_storage;
	i = 1;
	while (str[i] != '\n' && str[i] != '\'')
		i++;
	back_str = get_strdup(&str[1], i - 1);
	*str_storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	return (i);
}

int	position_expand(char **str_storage, char *str, t_state *state)
{
	int		i;
	char	*key;
	char	*back_str;
	char	*front_str;

	i = 1;
	front_str = *str_storage;
	while (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && str[i] != '\0' && str[i] != '$')
		i++;
	key = get_strdup(&str[1], i - 1);
	back_str = get_value(state->env_lst, key);
	*str_storage = null_strjoin(front_str, back_str);
	free(front_str);
	free(back_str);
	free(key);
	return (i);
}

int	dquote_expand(char **str_storage, char *str, t_state *state)
{
	char	*front_str;
	char	*back_str;
	int		i;
	int		j;
	
	i = 1;
	while (str[i] != '\"')
	{
		front_str = *str_storage;
		j = 0;
		while (str[i + j] != '$' && str[i + j] != '\"')
			j++;
		back_str = get_strdup(&str[i], j);
		*str_storage = null_strjoin(front_str, back_str);
		free(front_str);
		free(back_str);
		if (str[i + j] == '$')
			j = position_expand(str_storage, &str[i + j], state);
		i += j;
	}
	return (i);
}