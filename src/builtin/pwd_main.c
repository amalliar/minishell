/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/08 13:20:28 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_stdio.h>
#include <error_tools.h>

int		bi_pwd(int argc, char **argv, char **envp)
{
	char *path;

	(void)argc;
	(void)argv;
	(void)envp;
	if (!(path = getcwd(NULL, 0)))
		return (putstr_err("pwd: getcwd: error", 1));
	ft_printf("%s\n", getcwd(0, 0));
	free(path);
	return (EXIT_SUCCESS);
}
