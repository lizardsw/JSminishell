#include "parsing.h"

char	*null_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (s1[j] != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

// str에 number 만큼 c 를 찾아서 return 해준다.
int	get_strchr(char *str, int number, char c)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// str에 number만큼 strdup
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