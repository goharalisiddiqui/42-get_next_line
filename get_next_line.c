/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:45:16 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/06/29 16:39:21 by gsiddiqu         ###   ########.fr       */
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

int		ft_gnl_reader(char **str, int fd)
{
	char	*str2;
	int 	flag;
	char 	*str3;

	*str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	flag = read(fd, *str, BUFFER_SIZE);
	if (flag == -1)
		return (-1);
	*(*str + flag) = '\0';
	while (ft_strchr(*str, '\n') == NULL && flag == BUFFER_SIZE)
	{
		str2 = malloc(BUFFER_SIZE * sizeof(char));	
		flag = read(fd, str2, BUFFER_SIZE);
		if (flag > 0)
		{
			str3 = malloc((ft_strlen(*str) + flag + 1) * sizeof(char));
			ft_memcpy(str3, *str, ft_strlen(*str));
			ft_memcpy(str3 + ft_strlen(*str), str2, flag);
			*(str3 + ft_strlen(*str) + flag) = '\0';
			free(*str);
			free(str2);
			*str = str3;
		}
	}
	return (flag);
}

void	ft_gnl_addpre(v_list **vault, int fd, char **str)
{
	v_list	*elem;
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

int	ft_gnl_checker(v_list **lst, char **str, int fd)
{
	v_list	*elem;

	elem = ft_vlstlocdel(lst, fd, 0);
	if (elem != NULL && ft_strchr((*elem).content, '\n') != NULL)
	{
		*str = ft_strdup((*elem).content);
		return 1;
	}
	else
		return (ft_gnl_reader(str, fd));
	
}

int		get_next_line(int fd, char **line)
{
	char			*str;
	char			*rem;
	static v_list	*vault = NULL;
	int 			flag;

	flag = ft_gnl_checker(&vault, &str, fd);
	if (flag != -1)
	{
		if (ft_vlstlocdel(&vault, fd, 0) != NULL)
			ft_gnl_addpre(&vault, fd, &str);
		rem = ft_strchr(str, '\n');
		if (rem == NULL && ft_vlstlocdel(&vault, fd, 0) != NULL)
			{ft_vlstlocdel(&vault, fd, 1);printf("\nPOINT1\n");fflush(stdout);}
		else
		{
			ft_vlstadd(&vault, fd, ft_strdup(rem + 1));
			*rem = '\0';
		}
		*line = ft_strdup(str);
	}
	free(str);
	if (flag > 0)
		return (1);
	return (flag);
}