/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:30:35 by yboutsli          #+#    #+#             */
/*   Updated: 2024/02/10 15:49:55 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_putstr(int fd, char *str);
int		ft_putchar(int fd, char c);
int		ft_putnbr(int fd, int nb);
int		ft_putnbrhexa(int fd, unsigned long nb, char casef);
int		ft_printforma(int fd, va_list args, const char format);
int		ft_printf(int fd, const char *format, ...);
int		ft_putpointer(int fd, unsigned long adress);
int		ft_putunsigned(int fd, unsigned int nb);
void	check(int x, int *count);
#endif
