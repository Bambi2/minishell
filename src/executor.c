/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:02 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:47:16 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*get_cmd(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (temp)
	{
		if (temp->token_type == PIPE)
			return (NULL);
		if (temp->token_type == CMD)
			break ;
		temp = temp->next;
	}
	return (temp);
}

static void	init_pipes(t_minishell *msh)
{
	t_token	*tmp;
	int		i;

	msh->count_of_pipe = 0;
	msh->count_of_cmd = 0;
	i = 0;
	msh->currentp = 0;
	msh->currentcmd = 0;
	tmp = msh->tokens;
	while (tmp)
	{
		if (tmp->token_type == PIPE)
			msh->count_of_pipe ++;
		if (tmp->token_type == CMD)
			msh->count_of_cmd ++;
		tmp = tmp->next;
	}
	msh->pipes = (t_pipes *) malloc (sizeof(t_pipes) * msh->count_of_pipe);
	while (i < msh->count_of_pipe)
	{
		pipe(msh->pipes[i].fd);
		i ++;
	}
	msh->pids = (int *) malloc (sizeof(int) * msh->count_of_cmd);
}

void	wait_all_child(t_minishell *msh)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < msh->count_of_cmd)
	{
		if (i != msh->count_of_cmd - 1)
			waitpid(msh->pids[i], 0, 0);
		else
		{
			waitpid(msh->pids[i], &wstatus, 0);
			if (msh->is_wstatus && g_termflag.last_exit_status != 130
				&& g_termflag.last_exit_status != 131)
				g_termflag.last_exit_status = WEXITSTATUS(wstatus);
		}
		i++;
	}
	free(msh->pids);
	free(msh->pipes);
}

static void	closeallpipes(t_minishell *msh)
{
	int	i;

	i = 0;
	while (i < msh->count_of_pipe - 1)
	{
		close (msh->pipes[i].fd[0]);
		close (msh->pipes[i].fd[1]);
		i ++;
	}
}

void	executor(t_minishell *minishell)
{
	int		tmpin;
	int		tmpout;
	t_token	*cmd;

	tmpin = dup(STDIN_FILENO);
	tmpout = dup(STDOUT_FILENO);
	init_pipes(minishell);
	while (minishell->tokens)
	{
		cmd = get_cmd(minishell);
		if (handle_pipes(minishell) != -1)
			handle_cmd(minishell, cmd);
		dup2(tmpin, 0);
		dup2(tmpout, 1);
		if (minishell->tokens)
			minishell->tokens = minishell->tokens->next;
		minishell->currentcmd++;
	}
	closeallpipes(minishell);
	wait_all_child(minishell);
	unlink(".input");
	close(tmpin);
	close(tmpout);
}
