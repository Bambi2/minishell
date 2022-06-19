/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lekser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:19 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:20 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_synatx_error(t_token *lst)
{
	t_token	*prev;
	int		cmd_flag;

	prev = 0;
	cmd_flag = 0;
	if (lst == 0)
		return (0);
	while (lst)
	{
		if (!change_tokens(lst, prev, &cmd_flag))
			return (0);
		prev = lst;
		lst = lst->next;
	}
	return (1);
}

void	parser(t_token **token_list, t_minishell *minishell)
{
	if (*token_list == 0)
		return ;
	open_evar(token_list, minishell);
	remove_spaces(token_list);
	if (!check_synatx_error(*token_list))
	{
		lstclear(token_list, free);
		g_termflag.last_exit_status = 1;
	}
}

t_token	*lekser(char *str, t_minishell *minishell)
{
	int		i;
	char	*sep;
	t_token	*token_list;

	i = 0;
	sep = 0;
	token_list = 0;
	if (str == 0)
		return (0);
	while (str[i])
	{
		skip_space(str, &i);
		find_sep(str, i, &sep);
		if (!(lstadd_back(&token_list, lstnew(get_type(sep),
						tokenizer(str, &i, sep)))))
		{
			lstclear(&token_list, free);
			g_termflag.last_exit_status = 1;
			break ;
		}
		i ++;
	}
	free (sep);
	parser(&token_list, minishell);
	return (token_list);
}
