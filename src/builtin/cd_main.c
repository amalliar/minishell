/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 19:44:43 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <env_tools.h>
#include <error_tools.h>
#include <ft_string.h>
#include "msh.h"

int				bi_cd(int argc, char **argv)
{
	char		*path;
	char		*cur_path;

	if (argc > 2)
		return (putstr_err(MSH_VERSION": cd: too many arguments\n", 1));
	else if (argc == 1)
	{
		if (!((path = ft_getenv("HOME")) && *path))
			return (putstr_err(MSH_VERSION": cd: HOME not set\n", 1));
	}
	else
		path = argv[1];
	msg_assert(cur_path = getcwd(NULL, 0), "getcwd error");
	if (chdir(path) == -1)
	{
		free(cur_path);
		ft_perror(path);
		return (EXIT_FAILURE);
	}
	ft_setenv("OLDPWD", cur_path);
	free(cur_path);
	msg_assert(path = getcwd(NULL, 0), "getcwd error");
	ft_setenv("PWD", path);
	free(path);
	return (EXIT_SUCCESS);
}
