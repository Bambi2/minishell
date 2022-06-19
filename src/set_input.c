/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:13 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 19:40:04 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	add_file(t_minishell *minishell, char *path)
{
	int		fd;
	char	*line;

	minishell->fdin = rewrite(minishell->fdin);
	if (minishell->fdin == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		minishell->fdin = -1;
		perror(path);
		return (-1);
	}
	line = get_next_line(fd);
	while (line)
	{
		write(minishell->fdin, line, ft_strlen(line));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

static int	add_heredoc(t_minishell *minishell, char *limiter)
{
	char	*line;

	minishell->fdin = rewrite(minishell->fdin);
	if (minishell->fdin == -1)
	{
		minishell->fdin = -1;
		return (-1);
	}
	line = get_next_line(0);
	while (line && is_limiter(limiter, line) == -1)
	{
		write(minishell->fdin, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	return (0);
}

static	int	start_opening_inputs(t_minishell *minishell)
{
	t_token	*temp;

	temp = minishell->tokens;
	while (temp && temp->token_type != PIPE)
	{
		if (temp->token_type == IFILE)
		{
			if (add_file(minishell, temp->token) == -1)
				return (-1);
		}
		else if (temp->token_type == LIMITER)
		{
			if (add_heredoc(minishell, temp->token) == -1)
				return (-1);
		}
		temp = temp->next;
	}
	return (0);
}

int	set_input(t_minishell *minishell)
{
	if (count_inputs(minishell->tokens) == 0)
	{
		if (!minishell->is_pipe)
			minishell->fdin = dup(STDIN_FILENO);
		return (0);
	}
	minishell->fdin = open(".input", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (minishell->fdin == -1)
	{
		perror(".input");
		return (-1);
	}
	if (start_opening_inputs(minishell) == -1)
		return (-1);
	minishell->fdin = reopen(minishell->fdin);
	return (0);
}
