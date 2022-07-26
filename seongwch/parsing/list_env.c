#include "parsing.h"

char **split_key_value(char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char *) * 3);
	if (new == NULL)
		exit(1);
	while (str[i] != '=')
		i++;
	new[0] = get_strdup(str, i);
	new[1] = ft_strdup(&str[i + 1]);
	return (new);
}

char	*get_value(t_list * env, char *key)
{
	char	**split;
	t_node	*ptr;
	

	split = split_key_value()




}

t_list	*make_list_env(char **env)
{
	t_list	*new;
	int		i;

	i = 0;
	new = new_list();
	while (env[i] != NULL)
	{
		push_node_back(new, new_node(env[i]));
		i++;
	}
	return (new);
}