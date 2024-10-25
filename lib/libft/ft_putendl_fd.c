/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:31:07 by pbencze           #+#    #+#             */
/*   Updated: 2023/11/21 15:10:59 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	int	fd;

	fd = open("test3.txt", O_CREAT | O_WRONLY);

	if (fd < 0)
	{
		perror("r1");
		exit(1);
	}

	ft_putendl_fd("World", fd);

	close (fd);

	return (0);
}
*/
