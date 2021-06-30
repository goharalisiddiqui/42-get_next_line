/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsiddiqu <gsiddiqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 17:45:42 by gsiddiqu          #+#    #+#             */
/*   Updated: 2021/06/30 20:43:26 by gsiddiqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_vlist
{
	int				idt;
	char			*content;
	struct s_vlist	*next;
}	t_vlist;

int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
char	*ft_strdup(const char *s1);
void	ft_vlstadd(t_vlist **lst, int id, char *str);
t_vlist	*ft_vlstlocdel(t_vlist **vault, int fd, int ident);
char	*ft_strchr(const char *s, int c);

#endif