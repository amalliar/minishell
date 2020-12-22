/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:21:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/10/14 21:21:00 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdio.h>

void	msg_exit(int i, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(i);
}

void	msg_arg_exit(int i, char *msg, char *problem)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("[", 2);
	ft_putstr_fd(problem, 2);
	ft_putstr_fd("]:", 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(i);
}

void	msg_assert(_Bool exp, char *msg)
{
	if (!exp)
		msg_exit(42, msg);
}
