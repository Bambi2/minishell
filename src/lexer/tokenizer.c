/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:32:27 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:32:28 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_word(char const *s, int *start, char **sub)
{
	int	i;

	i = *start;
	i ++;
	while (s[i])
	{		
		if (is_newtoken(s[i]) == 1)
			break ;
		if (s[i - 1] == '$' && s[i] == '?')
		{
			i ++;
			break ;
		}
		i ++;
	}
	*sub = (char *) malloc (sizeof(char) * (i - *start + 1));
	if (*sub == 0)
		return ;
	ft_strlcpy(*sub, s + *start, (i - *start) + 1);
	*start = i - 1;
}

void	get_symbtoken(char const *s, int *start, char **sub)
{
	*sub = (char *) malloc (sizeof(char) * (2));
	if (*sub == 0)
		return ;
	ft_strlcpy(*sub, s + *start, 2);
}

void	get_dsymbtoken(char const *s, int *start, char **sub)
{
	*sub = (char *) malloc (sizeof(char) * (3));
	if (*sub == 0)
		return ;
	ft_strlcpy(*sub, s + *start, 3);
	*start = *start + 1;
}

void	get_token(char const *s, int *start, char *sep, char **sub)
{
	if ((sep[0] == 0 || sep[0] == '$') && sep[1] == 0)
		get_word(s, start, sub);
	if ((sep[0] == '>' || sep[0] == '<' || sep[0] == '|'
			|| sep[0] == ' ') && sep[1] == 0)
		get_symbtoken(s, start, sub);
	if ((sep[0] == '>' && sep[1] == '>') || (sep[0] == '<' && sep[1] == '<'))
		get_dsymbtoken(s, start, sub);
}

char	*tokenizer(char const *s, int *start, char *sep)
{
	char	*sub;
	int		i;

	if (s == 0)
		return (0);
	if (sep[0] != '\'' && sep[0] != '\"')
	{
		get_token(s, start, sep, &sub);
		return (sub);
	}
	i = *start + 1;
	while (s[i] && s[i] != sep[0])
		i ++;
	if (!s[i])
	{
		ft_putstr_fd("minishell: dquotes!\n", 2);
		return (0);
	}
	sub = (char *) malloc (sizeof(char) * (i - *start));
	if (sub == 0)
		return (0);
	ft_strlcpy(sub, s + *start + 1, i - *start);
	*start = i;
	return (sub);
}
