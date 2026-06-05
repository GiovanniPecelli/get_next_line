/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecelli <gpecelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:40:04 by gpecelli          #+#    #+#             */
/*   Updated: 2026/06/03 09:19:53 by gpecelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_and_free(char *storage, char const *buffer);
char	*extract_line(char *storage, char line_sep);
char	*clean_storage(char *storage, char line_sep);
char	*ft_strdup(const char *s);
void	del(char **mem);
size_t	row_len(char *s, char line_sep);
size_t	ft_strlen(const char *s);
int		ft_strchr(const char *s, int c);

#endif
