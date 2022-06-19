/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:33:15 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:33:16 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_check(char sym, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == sym)
			return (1);
		i++;
	}
	return (0);
}

static int	get_length(char const *s1, char const *set)
{
	int	length;
	int	i;
	int	j;

	length = 0;
	i = 0;
	while (s1[i] && set_check(s1[i], set))
	{
		i++;
		length++;
	}
	j = ft_strlen(s1);
	while (j > i && set_check(s1[j - 1], set))
	{
		j--;
		length++;
	}
	return (length);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		i;
	int		length;
	char	*result;

	length = ft_strlen(s1) - get_length(s1, set);
	result = (char *) malloc(length + 1);
	if (!result)
		return (NULL);
	first = 0;
	while (s1[first] && set_check(s1[first], set))
		first++;
	i = 0;
	while (i < length)
		result[i++] = s1[first++];
	result[length] = '\0';
	return (result);
}
