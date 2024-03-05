/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfranca <anfranca@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:40:15 by anfranca          #+#    #+#             */
/*   Updated: 2024/03/05 12:07:14 by anfranca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_read(char *s)
{
	char	*line;
	int		i;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = (char *)malloc(i * sizeof(char) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*reset_start(char *s)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	i += (s[i] == '\n');
	newbuffer = (char *)malloc(ft_strlen(s) - i + 1);
	if (!newbuffer)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		newbuffer[j] = s[i + j];
		j++;
	}
	newbuffer[j] = '\0';
	free(s);
	return (newbuffer);
}

void	handle_read_error(char *tmp, char **str)
{
	free(tmp);
	free(*str);
	*str = NULL;
}

char	*get_next_line(int fd)
{
	int			fdread;
	char		*tmp;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fdread = 1;
	tmp = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!tmp)
		return (NULL);
	while (!(ft_strchr(str, '\n')) && fdread != 0)
	{
		fdread = read(fd, tmp, BUFFER_SIZE);
		if (fdread == -1)
		{
			handle_read_error(tmp, &str);
			return (0);
		}
		tmp[fdread] = '\0';
		str = ft_strjoin(str, tmp);
	}
	free(tmp);
	tmp = line_read(str);
	str = reset_start(str);
	return (tmp);
}
