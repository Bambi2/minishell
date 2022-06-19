/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lekser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:18 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:19 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_newtoken(char c)
{
	if (c == '\"')
		return (1);
	else if (c == '\'')
		return (1);
	else if (c == ' ')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '<')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '$')
		return (1);
	return (0);
}

int	get_type(char *sep)
{
	if (sep[0] == '\"' && sep[1] == 0)
		return (DFIELD);
	if (sep[0] == '\'' && sep[1] == 0)
		return (FIELD);
	if ((sep[0] == 0 || sep[0] == '$') && sep[1] == 0)
		return (WORD);
	if (sep[0] == '>' && sep[1] == 0)
		return (TRUNC);
	if (sep[0] == '>' && sep[1] == '>')
		return (APPEND);
	if (sep[0] == '<' && sep[1] == 0)
		return (READ);
	if (sep[0] == '<' && sep[1] == '<')
		return (HEREDOC);
	if (sep[0] == '|' && sep[1] == 0)
		return (PIPE);
	if (sep[0] == ' ' && sep[1] == 0)
		return (SPACER);
	return (0);
}

void	skip_space(char *str, int *i)
{
	while (str[*i] && str[*i] == ' ' && str[*i + 1] == ' ')
		*i = *i + 1;
}

void	get_sep(char s1, char s2, char **sep)
{
	if (*sep == 0)
	{
		*sep = (char *) malloc (sizeof(char) * 2);
		if (!(*sep))
			exit (1);
	}
	(*sep)[0] = s1;
	(*sep)[1] = s2;
}

void	find_sep(char *str, int i, char **sep)
{
	if (str[i] == '\"')
		get_sep('\"', 0, sep);
	else if (str[i] == '\'')
		get_sep('\'', 0, sep);
	else if (str[i] == ' ')
		get_sep(' ', 0, sep);
	else if (str[i] == '|')
		get_sep('|', 0, sep);
	else if (str[i] == '>' && str[i + 1] != '>')
		get_sep('>', 0, sep);
	else if (str[i] == '>' && str[i + 1] == '>')
		get_sep('>', '>', sep);
	else if (str[i] == '<' && str[i + 1] != '<')
		get_sep('<', 0, sep);
	else if (str[i] == '<' && str[i + 1] == '<')
		get_sep('<', '<', sep);
	else if (str[i] == '$')
		get_sep('$', 0, sep);
	else
		get_sep(0, 0, sep);
}
