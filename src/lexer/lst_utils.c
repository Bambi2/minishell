/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:20 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:21 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*lstnew(int token_type, char *token)
{
	t_token	*new_obj;

	if (token == 0)
		return (0);
	new_obj = (t_token *) malloc (sizeof(t_token));
	if (new_obj == 0)
		return (0);
	new_obj->token_type = token_type;
	new_obj->token = token;
	new_obj->next = 0;
	return (new_obj);
}

t_token	*lstlast(t_token *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

int	lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (new == 0)
		return (0);
	if (*lst == 0)
		(*lst) = new;
	else
	{
		last = lstlast(*lst);
		last->next = new;
	}
	return (1);
}

void	lstdelone(t_token *lst, void (*del)(void *))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->token);
	free(lst);
}

void	lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	if (*lst == 0)
		return ;
	while ((*lst)->next != 0)
	{
		tmp = (*lst)->next;
		lstdelone(*lst, del);
		(*lst) = tmp;
	}
	lstdelone(*lst, del);
	*lst = 0;
}
