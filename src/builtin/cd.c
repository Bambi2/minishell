/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:41 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:31:42 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	update_cd_vars(t_minishell *minishell, char *pwd, char *oldpwd)
{
	char	*check;

	check = get_env_var(minishell->envp, "OLDPWD");
	if (check)
	{
		free(check);
		change_env(minishell, "OLDPWD", oldpwd);
	}
	else
		add_env_var(minishell, "OLDPWD", oldpwd);
	check = get_env_var(minishell->envp, "PWD");
	if (check)
	{
		free(check);
		change_env(minishell, "PWD", pwd);
	}
	else
		add_env_var(minishell, "PWD", pwd);
}

static int	cd_home(t_minishell *minishell)
{
	char	*home_dir;
	char	*oldpwd;

	home_dir = get_env_var(minishell->envp, "HOME");
	if (!home_dir)
		return (-1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd");
		free(home_dir);
		return (-2);
	}
	if (chdir(home_dir) == -1)
	{
		perror(home_dir);
		free(home_dir);
		free(oldpwd);
		return (-2);
	}
	update_cd_vars(minishell, home_dir, oldpwd);
	free(home_dir);
	free(oldpwd);
	return (0);
}

static int	cd_dir(t_minishell *minishell, char *dir)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror(dir);
		return (-1);
	}
	if (chdir(dir) == -1)
	{
		perror(dir);
		free(oldpwd);
		return (-1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		update_cd_vars(minishell, pwd, oldpwd);
		free(pwd);
	}
	free(oldpwd);
	return (0);
}

void	cd(t_minishell *minishell, char **argv)
{
	int	answer;

	if (!argv[1])
	{
		answer = cd_home(minishell);
		if (answer == -1 || answer == -2)
		{
			g_termflag.last_exit_status = 1;
			if (answer == -1)
				ft_putstr_fd("cd: HOME not set\n", 2);
		}
		else
			g_termflag.last_exit_status = 0;
		return ;
	}
	if (cd_dir(minishell, argv[1]) == -1)
		g_termflag.last_exit_status = 1;
	else
		g_termflag.last_exit_status = 0;
}
