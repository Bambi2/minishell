/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:05 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:43:21 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_bin(t_minishell *minishell, t_token *token, char **path)
{
	int		i;
	char	**argv;

	i = 0;
	argv = get_arguments(token, token->token);
	execve(token->token, argv, minishell->envp);
	while (path && path[i])
	{
		execve(path[i], argv, minishell->envp);
		free_strings(argv, get_strings_count(argv) - 1);
		argv = get_arguments(token, path[i]);
		i++;
	}
	if (path)
		free_strings(path, get_strings_count(path) - 1);
	perror(token->token);
	exit(EXIT_FAILURE);
}

void	close_allpipes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->count_of_pipe)
	{
		if (i != msh->currentp - 1)
			close (msh->pipes[i].fd[1]);
		if (i != msh->currentp)
			close (msh->pipes[i].fd[0]);
		i ++;
	}
}

int	handle_bin(t_minishell *minishell, t_token *token)
{
	char	**path;

	minishell->is_wstatus = 1;
	g_termflag.last_exit_status = 0;
	path = get_path(minishell, token->token);
	minishell->pids[minishell->currentcmd] = fork();
	if (minishell->pids[minishell->currentcmd] == -1)
	{
		perror("fork");
		return (-1);
	}
	if (minishell->pids[minishell->currentcmd] == 0)
	{	
		close_allpipes(minishell);
		run_bin(minishell, token, path);
	}
	if (path)
		free_strings(path, get_strings_count(path) - 1);
	return (0);
}
