/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:48:02 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/06/29 16:50:35 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (*str)
	{
		size++;
		str++;
	}
	return (size);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;

	str = malloc((1 + ft_strlen((char *)s1)) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i))
	{
		*(str + i) = *(s1 + i);
		i++;
	}
	*(str + i) = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	ind;

	ind = 0;
	while (*(s + ind))
	{
		if (*(s + ind) == c)
			return ((char *)s + ind);
		ind++;
	}
	if (*(s + ind) == c)
		return ((char *)s + ind);
	return (NULL);
}

void	ft_vlstadd(t_vlist **lst, int id, char *str)
{
	t_vlist	*elem;
	t_vlist	*lastelem;

	elem = ft_vlstlocdel(lst, id, 0);
	if (elem == NULL)
	{
		elem = malloc(sizeof(t_vlist));
		(*elem).idt = id;
		(*elem).next = NULL;
		if (*lst == NULL)
			*lst = elem;
		else
		{
			lastelem = *lst;
			while ((*lastelem).next != NULL)
				lastelem = (*lastelem).next;
			(*lastelem).next = elem;
		}
	}
	else
		free((*elem).content);
	(*elem).content = ft_strdup(str);
}

t_vlist	*ft_vlstlocdel(t_vlist **lst, int fd, int ident)
{
	t_vlist	*elem;
	t_vlist	*nneighb;

	if (ident == 1)
	{
		elem = ft_vlstlocdel(lst, fd, 0);
		if (elem != NULL)
		{
			free((*elem).content);
			nneighb = (*elem).next;
			free(elem);
			elem = nneighb;
		}
	}
	else if (ident == 0)
	{
		elem = *lst;
		while (elem != NULL && (*elem).idt != fd)
			elem = (*elem).next;
		return (elem);
	}
	return (NULL);
}
