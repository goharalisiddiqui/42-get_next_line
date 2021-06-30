/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:45:16 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/06/30 19:12:20 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (dst != NULL || src != NULL))
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

int	ft_gnl_reader(char **str, int fd)
{
	char	*str2;
	int		flag;
	char	*str3;

	*str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	flag = read(fd, *str, BUFFER_SIZE);
	if (flag >= 0)
		*(*str + flag) = '\0';
	while (ft_strchr(*str, '\n') == NULL && flag == BUFFER_SIZE)
	{
		str2 = malloc(BUFFER_SIZE * sizeof(char));
		flag = read(fd, str2, BUFFER_SIZE);
		if (flag == 0)
		{
			free(str2);
			return (0);
		}
		str3 = malloc((ft_strlen(*str) + flag + 1) * sizeof(char));
		ft_memcpy(str3, *str, ft_strlen(*str));
		ft_memcpy(str3 + ft_strlen(*str), str2, flag);
		*(str3 + ft_strlen(*str) + flag) = '\0';
		free(*str);
		free(str2);
		*str = str3;
	}
	return (flag);
}

void	ft_gnl_addpre(t_vlist **vault, int fd, char **str)
{
	t_vlist	*elem;
	char	*pre;
	char	*whole;

	elem = ft_vlstlocdel(vault, fd, 0);
	pre = (*elem).content;
	whole = malloc((ft_strlen(*str) + ft_strlen(pre) + 1) * sizeof(char));
	ft_memcpy(whole, pre, ft_strlen(pre));
	ft_memcpy(whole + ft_strlen(pre), *str, ft_strlen(*str) + 1);
	free(*str);
	*str = whole;
}

int	ft_gnl_checker(t_vlist **lst, char **str, int fd)
{
	t_vlist	*elem;
	int		flag;

	elem = ft_vlstlocdel(lst, fd, 0);
	if (elem != NULL && ft_strchr((*elem).content, '\n') != NULL)
	{
		*str = ft_strdup((*elem).content);
		return (1);
	}
	flag = ft_gnl_reader(str, fd);
	if (flag > 0 && flag < BUFFER_SIZE && ft_strchr(*str, '\n') == NULL)
		flag = 0;
	if (flag >= 0 && ft_vlstlocdel(lst, fd, 0) != NULL)
		ft_gnl_addpre(lst, fd, str);
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	char			*str;
	char			*rem;
	static t_vlist	*vault = NULL;
	int				flag;

	flag = ft_gnl_checker(&vault, &str, fd);
	//printf("STR=%s\n",str);
	if (flag > -1 && *str != '\0')
	{
		rem = ft_strchr(str, '\n');
		if ((rem == NULL || *(rem + 1) == '\0') && ft_vlstlocdel(&vault, fd, 0) != NULL)
			ft_vlstlocdel(&vault, fd, 1);
		else if (rem != NULL && ft_strlen(rem) > 1)
		{
			ft_vlstadd(&vault, fd, ft_strdup(rem + 1));
			*rem = '\0';
		}
		if (rem != NULL)
			*rem = '\0';
	}
	if (flag < 0)
		*line = NULL;
	else
		*line = ft_strdup(str);
	free(str);
	if (flag > 0)
		return (1);
	return (flag);
}
