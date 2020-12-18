/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:44:28 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/18 20:19:40 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdio.h>
#include <stdbool.h>

int	main(int argc, char **argv, char **envp)
{
	while (*envp)
	{
		ft_putstr(*envp);
		ft_putchar('\n');
		envp++;
	}
	return (0);
}
