/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnila <mnila@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:03:06 by mnila             #+#    #+#             */
/*   Updated: 2019/12/20 02:11:14 by mnila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		delete_file(const int fd, t_list **file_list)
{
	t_list		*current;
	t_list		*previous;

	current = *file_list;
	if (current && current->content_size == (size_t)fd)
	{
		*file_list = (*file_list)->next;
		free(*file_list);
		*file_list = NULL;
	}
	else
	{
		while (current && current->content_size != (size_t)fd)
		{
			previous = current;
			current = current->next;
		}
		if (current)
		{
			previous->next = current->next;
			free(current);
		}
	}
}

static t_list	*get_file(const int fd, t_list *file_list)
{
	t_list	*new_file;

	if (file_list == NULL)
	{
		if ((new_file = ft_lstnew(NULL, 0)) == NULL)
			return (NULL);
		new_file->content_size = (size_t)fd;
		new_file->content = ft_strdup("");
		return (new_file);
	}
	if (file_list->content_size == (size_t)fd)
	{
		return (file_list);
	}
	if (file_list->next == NULL)
	{
		if ((file_list->next = get_file(fd, file_list->next)) == NULL)
			return (NULL);
		return (file_list->next);
	}
	return (get_file(fd, file_list->next));
}

static int		set_line(t_list *file, char *new, char *buffer, char **line)
{
	void	*temp;

	if (file == NULL || new == NULL || buffer == NULL || line == NULL)
		return (-1);
	temp = file->content;
	*line = new;
	file->content = (char *)buffer;
	free(temp);
	return (1);
}

static int		read_file(const int fd, t_list **file_list, char **line)
{
	int			bytes_read;
	char		buffer[BUFF_SIZE + 1];
	t_list		*file;
	char		*newline;
	char		*temp;

	file = get_file(fd, *file_list);
	while ((bytes_read = read(fd, &buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		set_line(file, buffer, ft_strjoin(file->content, buffer), line);
		if ((newline = ft_strchr(file->content, '\n')))
		{
			temp = ft_strsub(file->content, 0, newline - (char *)file->content);
			return (set_line(file, temp, ft_strdup(newline + 1), line));
		}
	}
	if (file != NULL && file->content != NULL && ft_strlen(file->content) > 0)
	{
		set_line(file, ft_strdup(file->content), file->content, line);
		delete_file(fd, file_list);
		return (1);
	}
	return (bytes_read);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*file_list;
	t_list			*file;
	char			*newline;
	char			*temp;

	if (fd <= -1 || line == NULL)
		return (-1);
	if (file_list == NULL)
		file_list = get_file(fd, NULL);
	file = get_file(fd, file_list);
	if (file->content && (newline = ft_strchr(file->content, '\n')))
	{
		temp = ft_strsub(file->content, 0, newline - (char *)file->content);
		return (set_line(file, temp, ft_strdup(newline + 1), line));
	}
	return (read_file(fd, &file_list, line));
}
