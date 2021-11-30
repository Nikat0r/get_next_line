/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:23:16 by ababa             #+#    #+#             */
/*   Updated: 2021/11/29 21:37:15 by ababa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	safefree(char	**ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*is_newline(char **str)
{
	char	*line;
	char	*temp;
	int		index;

	index = ft_strchr(*str, '\n');
	temp = ft_strdup(*str);
	line = ft_substr(*str, 0, index + 1);
	free(*str);
	*str = ft_substr(temp, index + 1, ft_strlen(temp));
	safefree(&temp);
	return (line);
}

static char	*is_not_newline(char **str)
{
	char	*temp;

	if (**str != '\0' && *str != NULL)
	{
		temp = ft_strdup(*str);
		safefree(str);
		return (temp);
	}
	else
	{
		safefree(str);
		return (NULL);
	}
}

static char	*ft_read(char **str, char **temp, int fd)
{
	int		r;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr(*str, '\n') == 1)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			safefree(&buffer);
			safefree(str);
			return (NULL);
		}
		buffer[r] = '\0';
		if (r == 0)
			break ;
		*temp = ft_strjoin(*str, buffer);
		safefree(str);
		*str = *temp;
	}
	safefree(&buffer);
	return (*str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str[fd])
		str[fd] = ft_strdup("");
	if (ft_read(&str[fd], &temp, fd) == NULL)
		return (NULL);
	if (ft_strchr(str[fd], '\n') == 1)
	{
		line = is_not_newline(&str[fd]);
		return (line);
	}
	line = is_newline(&str[fd]);
	return (line);
}
