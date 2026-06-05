/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecelli <gpecelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:39:46 by gpecelli          #+#    #+#             */
/*   Updated: 2026/06/03 11:00:35 by gpecelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	row_len(char *s, char line_sep)
{
	size_t	line_len;

	line_len = 0;
	while (s[line_len] != line_sep && s[line_len])
	{
		line_len++;
	}
	if (s[line_len] == line_sep)
		line_len++;
	return (line_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

int	ft_strchr(const char *s, int c)
{
	int		index;

	index = 0;
	while (s[index])
	{
		if (s[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		index;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dup)
		return (NULL);
	index = 0;
	while (s[index] != '\0')
	{
		dup[index] = s[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}

char	*ft_strjoin_and_free(char *storage, char const *buffer)
{
	char	*join;
	size_t	s_len;
	size_t	b_len;
	size_t	index;

	s_len = ft_strlen(storage);
	b_len = ft_strlen(buffer);
	join = malloc(s_len + b_len + 1);
	if (!join)
		return (NULL);
	index = 0;
	while (index < s_len)
	{
		join[index] = storage[index];
		index++;
	}
	index = 0;
	while (index < b_len)
	{
		join[s_len + index] = buffer[index];
		index++;
	}
	join[s_len + index] = '\0';
	free(storage);
	return (join);
}
