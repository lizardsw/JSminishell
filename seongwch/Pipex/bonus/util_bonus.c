/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:28:38 by junoh             #+#    #+#             */
/*   Updated: 2022/06/18 20:16:34 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex_bonus.h"

int	ft_strlen(char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strichr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	if (s[i] == c)
		return (i);
	else
		return (-1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((n-- > 0) && !(!*s1 && !*s2))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strndup(const char *s, int cpy_len)
{
	char	*tmp;
	int		len;

	len = cpy_len;
	tmp = malloc(sizeof(char) * (cpy_len + 1));
	if (tmp == NULL)
		return (NULL);
	while (cpy_len-- > 0)
	{
		*tmp = *s;
		tmp++;
		s++;
	}
	*tmp = '\0';
	return (tmp - len);
}

char	*ft_path_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) \
	+ ft_strlen(s2) + 2));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i++] = '/';
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2) + 1] = '\0';
	return (str);
}
