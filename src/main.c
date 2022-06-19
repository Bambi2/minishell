/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:11 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:12 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_termflag	g_termflag;

void	ft_printlist(t_token *lst)
{
	while (lst)
	{
		printf ("token = [%s]\t type = %d\n", lst->token, lst->token_type);
		lst = lst->next;
	}
}

void	start_minishell(t_minishell *minishell)
{
	char	*line;
	t_token	*temp;

	line = custom_readline(minishell, PROMPT);
	while (1)
	{
		minishell->tokens = lekser(line, minishell);
		free(line);
		if (minishell->tokens)
		{
			temp = minishell->tokens;
			executor(minishell);
			lstclear(&temp, free);
		}
		line = custom_readline(minishell, PROMPT);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*minishell;

	if (argc != 1)
	{
		argv = NULL;
		printf("Minishell doesn't take any arguments\n");
		return (EXIT_FAILURE);
	}
	g_termflag.last_exit_status = 0;
	minishell = init_minishell(envp);
	if (!minishell)
		exit(EXIT_FAILURE);
	if (set_signals() == -1)
		exit(EXIT_FAILURE);
	start_minishell(minishell);
}
