/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:25 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:26 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printlist(t_token *lst)
{
	while (lst)
	{
		printf ("token = [%s]\t type = %d\n", lst->token, lst->token_type);
		lst = lst->next;
	}
}
