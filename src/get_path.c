/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:04 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:05 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	join_string(char **path, char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, str);
		free(temp);
		if (!path[i])
		{
			free_strings(path, i - 1);
			free_strings(path + i + 1, ft_strlen(*(path + i + 1)));
			ft_putstr_fd("Couldn't allocate memory\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

//returns an array of strings joined with cmd
char	**get_path(t_minishell *minishell, char *cmd)
{
	char	**path;
	char	*temp_path;

	temp_path = get_env_var(minishell->envp, "PATH");
	if (!temp_path)
		return (NULL);
	path = ft_split(temp_path, ':');
	free(temp_path);
	if (!path)
		return (NULL);
	if (join_string(path, "/") == -1)
		return (NULL);
	if (join_string(path, cmd) == -1)
		return (NULL);
	return (path);
}
