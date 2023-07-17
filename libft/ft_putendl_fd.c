/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amenesca <amenesca@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:36:49 by amenesca          #+#    #+#             */
/*   Updated: 2022/05/30 15:45:28 by amenesca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	nl;

	nl = '\n';
	while (*s != '\0')
	{
		write(fd, &(*s), 1);
		s++;
	}
	write(fd, &nl, 1);
}