/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmalphit <mmalphit@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:33:29 by mmalphit          #+#    #+#             */
/*   Updated: 2022/06/01 18:44:38 by mmalphit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# define BUFFER_SIZE 1

char	*get_next_line(int fd);

int		next_line_check(const char *line);
int		strl(const char *str);
char	*make_line(const char *buf, int *i);
char	*gnl_ft_strjoin(char *s1, char *s2);
int		fd_read(int fd, char *buf, int *i);

typedef struct s_file {
	int		i;
	char	buf[BUFFER_SIZE * (-1 + (BUFFER_SIZE >= 0) * 2) + 1];
}	t_file;

#endif