/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvoicu <fvoicu@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:26:30 by fvoicu            #+#    #+#             */
/*   Updated: 2023/10/02 13:03:37 by fvoicu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	get_token(char input)
{
	if (input == '%')
		return (0);
	else if ('1' <= input && input <= '9')
		return (1);
	else if (input == '\0')
		return (2);
	else if (input == '.')
		return (3);
	else if (input == '*')
		return (4);
	else if (input == '-')
		return (5);
	else if (input == '0')
		return (6);
	else if (input == '+')
		return (7);
	else if (input == '#')
		return (8);
	else if (input == ' ')
		return (9);
	else if (input == 'c' || input == 's' || input == 'p' || input == 'd' \
		|| input == 'i' || input == 'u' || input == 'x' || input == 'X')
		return (10);
	else
		return (11);
}

static int	get_state(int previous_state, int token)
{
	static int	state_trans_table[96] = {2, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
							2, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
							8, 3, -1, 5, 4, 2, 2, 2, 2, 2, 8, -1, \
							8, 3, -1, 5, -1, -1, 3, -1, -1, -1, 8, -1, \
							8, -1, -1, 5, -1, -1, -1, -1, -1, -1, 8, -1, \
							8, 6, -1, -1, 7, -1, 6, -1, -1, -1, 8, -1, \
							8, 6, -1, -1, -1, -1, 6, -1, -1, -1, 8, -1, \
							8, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1};

	return (state_trans_table[(12 * previous_state) + token]);
}

static void	process(char input, t_info *info, int *state)
{
	if (*state == 1)
		put_char(input, info);
	else if (*state == 2)
		process_2(input, info);
	else if (*state == 3)
		process_3(input, info);
	else if (*state == 4)
		process_4(info);
	else if (*state == 5)
		info->format.precision = 0;
	else if (*state == 6)
		process_6(input, info);
	else if (*state == 7)
		process_7(info);
	else if (*state == 8)
	{
		*state = 0;
		info->spec = input;
		process_8(info);
	}
}

int	ft_printf(const char *format, ...)
{
	t_info	info;
	int		state;
	int		previous_state;
	int		token;

	va_start(info.arg, format);
	reset_info(&info);
	info.count = 0;
	state = 0;
	while (*format && state != 10)
	{
		previous_state = state;
		token = get_token(*format);
		state = get_state(previous_state, token);
		if (state == -1)
			return (0);
		process(*format, &info, &state);
		++format;
	}
	va_end(info.arg);
	return (info.count);
}

void	reset_info(t_info *info)
{
	info->flag.left_justify = false;
	info->flag.zero_padd = false;
	info->format.width = 0;
	info->format.precision = -1;
	info->flag.show_sign = false;
	info->flag.space = false;
	info->flag.alt_form = false;
	info->printed.sign = false;
	info->printed.prefix = false;
}
