/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:01 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:02 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//searches for environment variable
char	*get_env_var(char **envp, char *var_name)
{
	int		i;
	int		length;
	char	*value;

	i = 0;
	length = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, length) == 0
			&& envp[i][length] == '=')
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	value = ft_strdup(envp[i] + length + 1);
	if (!value)
	{
		ft_putstr_fd("Memory error\n", 2);
		return (NULL);
	}
	return (value);
}

//returns index of env variable
int	get_env_index(char **envp, char *var_name)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, length) == 0
			&& envp[i][length] == '=')
			break ;
		i++;
	}
	if (!envp[i])
		return (-1);
	return (i);
}

//changes the value of env variable
int	change_env(t_minishell *minishell, char *var_name, char *new_var_value)
{
	int		i;
	char	*temp;
	char	*old_value;

	i = get_env_index(minishell->envp, var_name);
	old_value = ft_strdup(minishell->envp[i]);
	if (!old_value)
		return (-1);
	free(minishell->envp[i]);
	temp = ft_strjoin(var_name, "=");
	if (!temp)
	{
		minishell->envp[i] = old_value;
		return (-1);
	}
	minishell->envp[i] = ft_strjoin(temp, new_var_value);
	free(temp);
	if (!minishell->envp[i])
	{
		minishell->envp[i] = old_value;
		return (-1);
	}
	free(old_value);
	return (0);
}

//adds new env variable or returns -1 and keeps env the same
int	add_env_var(t_minishell *minishell, char *var_name, char *var_value)
{
	char	**new_envp;
	int		count;
	char	*temp;

	new_envp = allocate_extra_space(minishell->envp, &count);
	if (!new_envp)
		return (-1);
	temp = ft_strjoin(var_name, "=");
	if (!temp)
	{
		free_strings_error(new_envp, count - 3);
		return (-1);
	}
	new_envp[count - 2] = ft_strjoin(temp, var_value);
	free(temp);
	if (!new_envp[count - 2])
	{
		free_strings_error(new_envp, count - 3);
		return (-1);
	}
	new_envp[count - 1] = NULL;
	free_strings(minishell->envp, count - 3);
	minishell->envp = new_envp;
	return (0);
}

int	remove_env_var(t_minishell *minishell, char *var_name)
{
	int		i;
	char	**new_envp;

	i = get_env_index(minishell->envp, var_name);
	if (i == -1)
		return (0);
	new_envp = remove_string(minishell->envp, i);
	if (!new_envp)
		return (-1);
	free_strings(minishell->envp, get_strings_count(minishell->envp));
	minishell->envp = new_envp;
	return (0);
}
