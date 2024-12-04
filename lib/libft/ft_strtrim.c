/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vados-sa <vados-sa@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:43:03 by pbencze           #+#    #+#             */
/*   Updated: 2024/12/04 14:40:57 by vados-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		aux_trim(char c, char const *set);
static char		*aux_newstring(char const *s1, int i, int j);

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (!s1)
		return (NULL);
	i = 0;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	j = (int)(ft_strlen(s1)) - 1;
	while (aux_trim(s1[i], set))
		i++;
	while (aux_trim(s1[j], set))
		j--;
	if (j < i)
		return (ft_strdup(""));
	return (aux_newstring(s1, i, j));
}

static int	aux_trim(char c, char const *set)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (set[k] == c)
			return (1);
		k++;
	}
	return (0);
}

static char	*aux_newstring(char const *s1, int i, int j)
{
	char	*new;
	int		k;

	k = 0;
	new = malloc((j - i + 2) * sizeof(char));
	if (!new)
		return (NULL);
	while (i <= j)
	{
		new[k] = s1[i];
		i++;
		k++;
	}
	new[k] = '\0';
	return (new);
}
