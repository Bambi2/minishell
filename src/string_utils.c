/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:16 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:17 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns number of strings
int	get_strings_count(char **strings)
{
	int	count;

	count = 0;
	while (strings[count])
		count++;
	return (count);
}

//creates a new array of strings
char	**copy_strings(char **strings)
{
	char	**copy;
	int		count;
	int		i;

	count = get_strings_count(strings);
	copy = (char **) malloc(sizeof(char *) * count + 1);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(strings[i]);
		if (!copy[i])
		{
			free_strings(copy, i - 1);
			ft_putstr_fd("Couldn't allocate memory\n", 2);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

//frees strings up to i-index (including)
void	free_strings(char **strings, int i)
{
	while (i >= 0)
	{
		free(strings[i]);
		i--;
	}
	free(strings);
}

//copies array and adds one extra string space
char	**allocate_extra_space(char **old_arr, int *count)
{
	char	**new_arr;
	int		i;

	*count = get_strings_count(old_arr) + 2;
	new_arr = (char **) malloc(sizeof(char *) * (*count));
	if (!new_arr)
	{
		ft_putstr_fd("Couldn't allocate memory\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < ((*count) - 2))
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		if (!new_arr[i])
		{
			ft_putstr_fd("Couldn't allocate memory\n", 2);
			free_strings(new_arr, i - 1);
			return (NULL);
		}
		i++;
	}
	return (new_arr);
}

char	**remove_string(char **old_arr, int index)
{
	char	**new_arr;
	int		i;
	int		y;
	int		count;

	new_arr = allocate_less_strings(old_arr, &count);
	if (!new_arr)
		return (NULL);
	i = 0;
	y = 0;
	while (i < count - 1)
	{
		if (i == index)
			y++;
		new_arr[i] = ft_strdup(old_arr[y++]);
		if (!new_arr[i])
		{
			ft_putstr_fd("Couldn't allocate memory\n", 2);
			free_strings(new_arr, i - 1);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}
