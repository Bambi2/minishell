/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:12 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:13 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rewrite(int fdin)
{
	close(fdin);
	fdin = open(".input", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fdin == -1)
	{
		perror(".input");
		return (-1);
	}
	return (fdin);
}

int	is_limiter(char *limiter, char *line)
{
	int	i;
	int	limiter_len;
	int	line_len;

	limiter_len = ft_strlen(limiter);
	line_len = ft_strlen(line) - 1;
	if (limiter_len != line_len)
		return (-1);
	i = 0;
	while (i < limiter_len)
	{
		if (limiter[i] != line[i])
			return (-1);
		i++;
	}
	return (0);
}

int	reopen(int fdin)
{
	close(fdin);
	fdin = open(".input", O_RDONLY, 0777);
	if (fdin == -1)
	{
		perror(".input");
		return (-1);
	}
	return (fdin);
}

int	count_inputs(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token_type != PIPE)
	{
		if (tokens->token_type == IFILE || tokens->token_type == LIMITER)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
