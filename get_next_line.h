/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:45:42 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/06/29 15:57:32 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct th_list
{
	int				idt;
	char			*content;
	struct th_list	*next;
}	v_list;



int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
char	*ft_strdup(const char *s1);
void	ft_vlstadd(v_list **lst, int id, char *str);
v_list	*ft_vlstlocdel(v_list **vault, int fd, int ident);
char	*ft_strchr(const char *s, int c);

#endif