/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junoh <junoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:49:58 by junoh             #+#    #+#             */
/*   Updated: 2022/08/05 19:50:13 by junoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		new[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i++] = s2[j++];
	}
	new[i] = '\0';
	free(s1);
	return (new);
}