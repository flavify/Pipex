/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:17:07 by flaviav           #+#    #+#             */
/*   Updated: 2023/09/20 15:03:19 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_flags
{
	bool		left_justify;
	bool		zero_padd;
	bool		show_sign;
	bool		space;
	bool		alt_form;
}	t_flags;

typedef struct s_format
{
	int			width;
	int			precision;
}	t_format;

typedef struct number
{
	int			sign;
	int			base;
	int			len;
}	t_number;

typedef struct s_printed
{
	bool		sign;
	bool		prefix;
}	t_printed;

typedef struct s_info
{
	t_flags		flag;
	t_format	format;
	t_number	nbr;
	t_printed	printed;
	int			count;
	char		spec;
	va_list		arg;
}				t_info;

// ft_printf.c
int		ft_printf(const char *format, ...);
void	reset_info(t_info *info);

// process.c
void	process_2(char c, t_info *info);
void	process_3(char c, t_info *info);
void	process_4(t_info *info);
void	process_6(char c, t_info *info);
void	process_7(t_info *info);
void	process_8(t_info *info);

//print_letters.c
void	print_char(char c, t_info *info);
void	print_str(char *str, t_info *info);
void	print_padding(t_info *info, int n);

//print_nbr.c
void	print_nbr(size_t n, t_info *info);

//print_nbr_utils.c
void	adjust_padding(size_t nbr, t_info *info, \
	int *len_to_print_padding);
void	handle_special_flags(size_t nbr, t_info *info);

//utils.c
void	put_char(char c, t_info *info);
int		get_sign(size_t *nbr, char type);
int		get_base(char type);
char	*base_set(char type);
int		get_number_len(size_t get_number_len, int base);

// libft_functions.c
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *str, int fd);

#endif
