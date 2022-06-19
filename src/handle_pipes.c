/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:08 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 20:42:48 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_pipeline(t_minishell *minishell, int not_pipe)
{
	minishell->is_pipe = 1;
	if (not_pipe)
		close(minishell->pipes[minishell->currentp].fd[1]);
	else
	{
		close(minishell->fdout);
		minishell->fdout = minishell->pipes[minishell->currentp].fd[1];
	}
	minishell->fdin = minishell->pipes[minishell->currentp].fd[0];
	minishell->currentp++;
	return (0);
}

static void	open_file(t_minishell *minishell,
	int *not_pipe, int *after_cmd, int type)
{
	close(minishell->fdout);
	if (type == TRUNC)
	{
		minishell->fdout = open(minishell->tokens->next->token,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	}
	else if (type == APPEND)
	{
		minishell->fdout = open(minishell->tokens->next->token,
				O_CREAT | O_WRONLY | O_APPEND, 0777);
	}
	if (!minishell->fdout)
		perror(minishell->tokens->next->token);
	if (*after_cmd)
		*not_pipe = 1;
}

void	set_output(t_minishell *minishell, int *not_pipe, int *after_cmd)
{
	minishell->fdout = dup(STDOUT_FILENO);
	while (minishell->tokens && minishell->tokens->token_type != PIPE)
	{
		if (minishell->tokens->token_type == CMD)
			*after_cmd = 1;
		if (minishell->tokens->token_type == TRUNC)
			open_file(minishell, not_pipe, after_cmd, TRUNC);
		else if (minishell->tokens->token_type == APPEND)
			open_file(minishell, not_pipe, after_cmd, APPEND);
		minishell->tokens = minishell->tokens->next;
	}
}

int	handle_pipes(t_minishell *minishell)
{
	int	after_cmd;
	int	not_pipe;

	not_pipe = 0;
	after_cmd = 0;
	set_input(minishell);
	set_output(minishell, &not_pipe, &after_cmd);
	if (minishell->fdin == -1)
	{
		close(minishell->fdout);
		return (-1);
	}
	dup2(minishell->fdin, 0);
	close(minishell->fdin);
	if (minishell->tokens && minishell->tokens->token_type == PIPE)
	{
		if (handle_pipeline(minishell, not_pipe) == -1)
			return (-1);
	}
	else
		minishell->is_pipe = 0;
	dup2(minishell->fdout, 1);
	close(minishell->fdout);
	return (0);
}
