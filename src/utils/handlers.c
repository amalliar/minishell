/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:49:46 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 20:56:34 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_stdio.h>
#include "prompt_tools.h"

extern int g_ret;

void		sigint_h(int n)
{
	(void)n;
	if (n == SIGINT)
	{
		ft_printf("\n%s", get_prompt());
		g_ret = 1;
	}
}

void		pass(int n)
{
	g_ret = 128 + n;
	if (n == SIGQUIT)
		ft_printf("Quit: %d\n", n);
	else if (n == SIGINT)
		ft_printf("\n");
}

void		set_default_signals(void)
{
	signal(SIGINT, pass);
	signal(SIGQUIT, pass);
}

void		set_bash_signals(void)
{
	signal(SIGINT, sigint_h);
	signal(SIGQUIT, SIG_IGN);
}
