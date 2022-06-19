/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:24 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:25 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	connect_token(t_token **new, t_token **old)
{
	char	*token;

	token = 0;
	strjoin(&token, (*old)->token);
	while ((*old)->next && (*old)->next->token_type != SPACER
		&& ((*old)->next->token_type == WORD
			|| (*old)->next->token_type == FIELD
			|| (*old)->next->token_type == DFIELD))
	{	
		(*old) = (*old)->next;
		strjoin(&token, (*old)->token);
	}
	lstadd_back(new, lstnew((*old)->token_type, token));
}

void	get_newelem(t_token	**new, t_token	**old)
{
	if (*old == 0)
		return ;
	if ((*old)->token_type != WORD && (*old)->token_type != FIELD
		&& (*old)->token_type != DFIELD && (*old)->token_type != SPACER)
	{
		lstadd_back(new, lstnew((*old)->token_type, ft_strdup((*old)->token)));
		return ;
	}
	connect_token(new, old);
}

void	remove_spaces(t_token **token_list)
{
	t_token	*lst;
	t_token	*new_list;

	new_list = 0;
	lst = *token_list;
	while (lst)
	{
		if (lst->token_type == SPACER)
			lst = lst->next;
		get_newelem(&new_list, &lst);
		if (lst)
			lst = lst->next;
	}
	lstclear(token_list, free);
	*token_list = new_list;
}
