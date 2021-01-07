/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:44:28 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/07 05:51:56 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdio.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	int	it;
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
	if (!n)
		ft_putchar('\n');
	return (0);
}
