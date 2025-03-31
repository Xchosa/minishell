/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poverbec <poverbec@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:06:07 by poverbec          #+#    #+#             */
/*   Updated: 2025/01/29 16:00:56 by poverbec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr_pr(int n);
int	ft_putchar_pr(char c);

int	ft_putstr_pr(char *s);
int	ft_put_unsig_int(unsigned int n);
int	ft_put_hex_lower(unsigned long c);
int	ft_put_hex_lower_int(unsigned int c);
int	ft_put_hex_upper(unsigned int c);
int	ft_put_pointer(unsigned long p);

int	ft_error_check_char(char c);
int	ft_error_check_nbr(int n);

int	ft_parse(va_list args, char c);

#endif