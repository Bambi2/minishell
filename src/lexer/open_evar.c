/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_evar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:21 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:22 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_var(char **str, t_minishell *minishell)
{
	char	*tmp;
	int		j;
	int		len;

	j = 0;
	len = ft_strlen(*str) - 1;
	if (ft_strnstr("$?", (*str), len + 1))
	{
		free (*str);
		*str = ft_itoa(g_termflag.last_exit_status);
		return ;
	}
	while (minishell->envp[j])
	{
		tmp = ft_strnstr(minishell->envp[j], (*str + 1), len);
		if (tmp != 0)
		{
			free (*str);
			*str = ft_strdup(tmp + len + 1);
			return ;
		}
		j ++;
	}
	free (*str);
	*str = 0;
}

void	remove_elem(t_token **head, t_token **lst, t_token **prev, int *flag)
{
	if (*prev == 0)
	{
		*head = (*head)->next;
		free((*lst)->token);
		free((*lst));
		(*lst) = *head;
		*flag = 1;
	}
	else
	{
		(*prev)->next = (*lst)->next;
		free((*lst)->token);
		free((*lst));
		*lst = *prev;
	}
}
// void	find_var(int i, char **str, char **envp)
// {
// 	int		j;
// 	char	*new_str;

// 	new_str = 0;
// 	j = 1;
// 	if ((*str)[i + j] == '?') // handle $? and other
// 		get_var(*str, i, j + 1, &new_str);
// 	else
// 	{
// 		while ((*str)[i + j] && (*str)[i + j] != '$' &&  
// 			(*str)[i + j] != ' '  &&  (*str)[i + j] != '\'')
// 			j ++;
// 		get_var(*str, i, j, &new_str);	
// 	}
// 	free(*str);
// 	*str = new_str;
// }

int	get_newword(char **str, t_minishell *minishell)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != 0 && (*str)[i + 1] != '\'')
		{
			get_var(str, minishell);
			if (*str == 0)
				return (0);
			else
				return (1);
		}
		i ++;
	}
	return (1);
}

int	change_word(t_token **head, t_token **lst,
	t_token **prev, t_minishell *minishell)
{
	int	flag;

	flag = 0;
	if ((*lst)->token[1] == 0 && (*lst)->next
		&& ((*lst)->next->token_type == DFIELD
			|| (*lst)->next->token_type == FIELD))
		remove_elem(head, lst, prev, &flag);
	else
	{
		if (!get_newword(&(*lst)->token, minishell))
			remove_elem(head, lst, prev, &flag);
	}
	return (flag);
}

void	open_evar(t_token **head, t_minishell *minishell)
{
	t_token	*prev;
	t_token	*lst;
	int		flag;

	lst = *head;
	prev = 0;
	flag = 0;
	while (lst)
	{
		if (lst->token_type == WORD || lst->token_type == DFIELD)
		{
			if (ft_strchr(lst->token, '$'))
				flag = change_word(head, &lst, &prev, minishell);
		}
		if (flag == 0)
		{
			prev = lst;
			lst = lst->next;
		}
		else
			flag = 0;
	}
}
