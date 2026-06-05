/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpecelli <gpecelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 12:39:07 by gpecelli          #+#    #+#             */
/*   Updated: 2026/06/03 10:27:30 by gpecelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// This function create a buffer with dimension of BUFFER_SIZE
// Control if Storage is valid
// while loop for search the end of the file or the line_sep at least
// read from the fd - and add the terminator at the end of the buffer
// past storage and buffer to strjoin_and_free
//	1: create an allocation: dimension fo storage len + buffer len + 1(\0)
//	2: build join - the string who become the storage (where fine "line")
//	3: free buffer to prevent us form data leak and return(storage)

char	*read_and_archive(int fd, char *storage, char line_sep)
{
	char	*buffer;
	char	*tmp;
	ssize_t	read_byte;

	if (!storage)
		storage = ft_strdup("");
	if (!storage)
		return (NULL);
	buffer = malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (del(&storage), NULL);
	read_byte = 1;
	while (ft_strchr(storage, line_sep) == 0 && read_byte != 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (del(&buffer), del(&storage), NULL);
		buffer[read_byte] = '\0';
		tmp = ft_strjoin_and_free(storage, buffer);
		if (!tmp)
			return (del(&buffer), del(&storage), NULL);
		storage = tmp;
	}
	free(buffer);
	return (storage);
}

// extract_line have the purpose to fine the line in storage
// allocate dimension of the len of the line using row_len
//		strlen but for '\n' researches
// copy the line in storage in "line" + '\0'
// return (line) - here we must save the extra part in storage

char	*extract_line(char *storage, char line_sep)
{
	int		index;
	char	*line;

	line = (char *)malloc(sizeof(char) * (row_len(storage, line_sep) + 1));
	if (!line)
		return (NULL);
	index = 0;
	while (storage[index] != line_sep && storage[index])
	{
		line[index] = storage[index];
		index++;
	}
	if (storage[index] == line_sep)
	{
		line[index] = storage[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

void	del(char **mem)
{
	if (mem && *mem)
	{
		free(*mem);
		*mem = NULL;
	}
}

// clean_storage save the extra_storege
//		so the remaning part after we take the line
// allocate a sufficient dimension: (storage - line) len
// in the final line -> free of storage and return extra_storage

char	*clean_storage(char *storage, char line_sep)
{
	char	*extra_storage;
	int		index;
	int		es_index;

	index = 0;
	while (storage[index] && storage[index] != line_sep)
		index++;
	if (!storage[index])
		return (del(&storage), NULL);
	extra_storage = malloc((ft_strlen(storage) - index) + 1);
	if (!extra_storage)
		return (del(&storage), NULL);
	index++;
	es_index = 0;
	while (storage[index])
	{
		extra_storage[es_index] = storage[index];
		es_index++;
		index++;
	}
	extra_storage[es_index] = '\0';
	free(storage);
	return (extra_storage);
}

// get_next_line -> call read_and_archive
//					-> call strdup - strchr - strjoin_and_free
// get_next_line -> call extract_line
//					-> call row_len
// get_next_line -> call clean_storage
//					-> call del(memory)

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line;
	char		line_sep;

	line_sep = '\n';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_and_archive(fd, storage, line_sep);
	if (!storage)
		return (NULL);
	if (!storage[0])
	{
		del(&storage);
		return (NULL);
	}
	line = extract_line(storage, line_sep);
	if (!line)
	{
		del(&storage);
		return (NULL);
	}
	storage = clean_storage(storage, line_sep);
	return (line);
}
