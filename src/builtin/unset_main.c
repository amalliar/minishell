/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:33:49 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/10 17:33:51 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env_tools.h>

int bi_unset(int argc, char **argv, char **envp)
{
	int it;

	it = 1;
	while (it < argc)
	{
		ft_unsetenv(argv[it]);
		it++;
	}
	return (0);
}