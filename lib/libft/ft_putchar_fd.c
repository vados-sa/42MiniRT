/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:29:01 by pbencze           #+#    #+#             */
/*   Updated: 2023/12/03 13:46:50 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
// C program to illustrate write system Call
//standard file descriptors are 0, 1, 2
#include <fcntl.h>
int	main(void)
{
	int	fd;

	fd = open("test1.txt", O_WRONLY | O_CREAT);

	if (fd < 0)
	{
		perror("r1");
		exit(1);
	}

	ft_putchar_fd('a', fd);

	printf("called write(%i, 'a', 1)", fd);

	close(fd);
}
*/
