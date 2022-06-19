/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:03 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:04 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//allocates argv
static char	**allocate_argv(t_token *token, int *count)
{
	t_token	*temp;
	char	**argv;

	*count = 0;
	temp = token->next;
	while (temp && temp->token_type != CMD)
	{
		if (temp->token_type == ARG)
			(*count)++;
		temp = temp->next;
	}
	argv = (char **) malloc(sizeof(char *) * ((*count) + 2));
	if (!argv)
	{
		ft_putstr_fd("Couldn't allocate memory [allocate_argv]\n", 2);
		return (NULL);
	}
	return (argv);
}

static int	fill_argv(char **argv, t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token->next;
	while (temp && temp->token_type != CMD)
	{
		if (temp->token_type == ARG)
		{
			argv[i + 1] = ft_strdup(temp->token);
			if (!argv[i + 1])
			{
				free_strings(argv, i);
				ft_putstr_fd("Couldn't allocate memory\n", 2);
				return (-1);
			}
			i++;
		}
		temp = temp->next;
	}
	argv[i + 1] = NULL;
	return (0);
}

//returns an array of arguments for cmd
char	**get_arguments(t_token *token, char *path)
{
	char	**argv;
	int		count;

	argv = allocate_argv(token, &count);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(path);
	if (!argv[0])
		return (NULL);
	if (fill_argv(argv, token) == -1)
		return (NULL);
	return (argv);
}
