/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:33:00 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:33:01 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_string_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == c && i != 0 && s[i + 1] && s[i - 1] != c)
			count++;
		i++;
	}
	return (count);
}

static int	get_string_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static void	add_new(char *result, char c, int *z, char const *s)
{
	int	j;

	j = 0;
	while (s[(*z)] != c && s[(*z)])
		result[j++] = s[(*z)++];
	result[j] = '\0';
}

static int	fill(char **result, char const *s, char c)
{
	int	i;
	int	z;
	int	length;

	i = 0;
	z = 0;
	while (s[z])
	{
		if (s[z] != c)
		{
			length = get_string_length(s + z, c);
			result[i] = (char *) malloc((length + 1) * sizeof(char));
			if (!result[i])
			{
				while (i - 1 >= 0)
					free(result[--i]);
				return (0);
			}
			add_new(result[i++], c, &z, s);
		}
		else
			z++;
	}
	result[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = (char **) malloc((get_string_count(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill(result, s, c))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
