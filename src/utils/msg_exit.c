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
#include <string.h>
#include <errno.h>

void	msg_exit(int i, char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(i);
}

void	msg_assert(_Bool exp, char *msg)
{
	if (!exp)
		msg_exit(EXIT_FAILURE, msg);
}

void ft_perror(const char *msg)
{
	if(msg && *msg)
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void error_check(int ret_of_func, const char *err_msg)
{
	if (ret_of_func != -1)
		return;
	ft_perror(err_msg);
	exit(ret_of_func);
}
