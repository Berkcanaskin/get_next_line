/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baskin <baskin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:23:09 by baskin            #+#    #+#             */
/*   Updated: 2024/11/25 17:51:30 by baskin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(char *s);
int		ft_strchr(char *s);
char	*ft_strjoin(char *left_str, char *buff);
char	*ft_line(char *left_str);
char	*ft_new_str(char *left_str);
char	*get_next_line(int fd);
char	*my_malloc(int n);

#endif