/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:16:09 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 20:10:18 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error_tools.h>
#include <ft_stdio.h>
#include <ft_string.h>
#include <ft_stdlib.h>
#include "msh.h"

extern int g_ret;

int		bi_exit(int argc, char **argv, char **envp)
{
	(void)envp;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (argc == 1)
		exit(g_ret);
	if (!ft_strisnumeric(argv[1]))
	{
		ft_putstr_fd(MSH_VERSION": exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	if (argc > 2)
		return (putstr_err(MSH_VERSION": exit: too many arguments\n", 1));
	exit(ft_atoi(argv[1]));
}
