/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbencze <pbencze@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:47:09 by pbencze           #+#    #+#             */
/*   Updated: 2024/02/02 15:29:53 by pbencze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

int	aux_putchar(int i);
int	aux_puthex(char specifier, unsigned int num);
int	aux_putnbr(int nb);
int	aux_putptr(unsigned long long ptradress);
int	aux_putstr(char *s);
int	aux_putunsigned(unsigned int n);
int	ft_printf(const char *str, ...);

#endif
