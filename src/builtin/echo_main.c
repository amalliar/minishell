/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:44:28 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/08 13:13:17 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdio.h>
#include <stdbool.h>

int	bi_echo(int argc, char **argv, char **envp)
{
	int		it;
	bool	n_option;

	it = 1;
	n_option = false;
	while (it < argc && !ft_strcmp(argv[it], "-n") && it++)
		n_option = true;
	while (it < argc)
	{
		ft_putstr(argv[it]);
		if (it + 1 != argc)
			ft_putchar(' ');
		it++;
	}
	if (!n_option)
		ft_putchar('\n');
	return (0);
}
