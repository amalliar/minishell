/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:44:28 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/18 19:06:27 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdio.h>
#include <stdbool.h>

int	main(int argc, char **argv)
{
	int	it;
	bool	n;

	n = !ft_strcmp(argv[1], "-n");
	it = 1 + n;
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
