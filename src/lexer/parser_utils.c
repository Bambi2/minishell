/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:22 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:23 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_cmd(int *cmd_flag, t_token *lst)
{
	*cmd_flag = 1;
	lst->token_type = CMD;
}

int	print_err(char *str)
{
	ft_putstr_fd("minishell: синтаксическая ошибка рядом\
	с неожиданным маркером «", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("»\n", 2);
	return (0);
}

int	check_redir(t_token *lst)
{
	if (!lst->next)
		return (print_err("newline"));
	if (lst->next->token_type != WORD && lst->next->token_type != FIELD
		&& lst->next->token_type != DFIELD)
		return (print_err(lst->next->token));
	if (lst->token_type == TRUNC || lst->token_type == APPEND)
		lst->next->token_type = OFILE;
	if (lst->token_type == HEREDOC)
		lst->next->token_type = LIMITER;
	if (lst->token_type == READ)
		lst->next->token_type = IFILE;
	lst = lst->next;
	return (1);
}

int	check_pipe(t_token *lst, t_token *prev, int *cmd_flag)
{
	if (prev == 0)
		return (print_err("|"));
	if (!(lst->next))
		return (print_err("newline"));
	if (lst->next->token_type == PIPE)
		return (print_err("|"));
	*cmd_flag = 0;
	return (1);
}

int	change_tokens(t_token *lst, t_token *prev, int *cmd_flag)
{
	if (*cmd_flag == 0 && (lst->token_type == WORD
			|| lst->token_type == FIELD || lst->token_type == DFIELD))
		get_cmd(cmd_flag, lst);
	else if ((lst->token_type == TRUNC || lst->token_type == APPEND
			|| lst->token_type == READ || lst->token_type == HEREDOC))
	{
		if (!check_redir(lst))
			return (0);
	}
	else if (lst->token_type == PIPE)
	{
		if (!check_pipe(lst, prev, cmd_flag))
			return (0);
	}
	else if (*cmd_flag == 1 && (lst->token_type == WORD
			|| lst->token_type == FIELD || lst->token_type == DFIELD))
		lst->token_type = ARG;
	return (1);
}
