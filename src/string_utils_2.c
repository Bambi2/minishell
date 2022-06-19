/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:15 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:16 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//new arr size is [count of arr - 1]
char	**allocate_less_strings(char **arr, int *count)
{
	char	**new_arr;

	*count = get_strings_count(arr);
	new_arr = (char **) malloc(sizeof(char *) * (*count));
	if (!new_arr)
	{
		ft_putstr_fd("Couldn't allocate memory\n", 2);
		return (NULL);
	}
	return (new_arr);
}

void	free_strings_error(char **strings, int i)
{
	ft_putstr_fd("Couldn't allocate memory\n", 2);
	free_strings(strings, i);
}
