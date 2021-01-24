/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/08 13:20:28 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <env_tools.h>
#include <error_tools.h>
#include <ft_string.h>

int				bi_cd(int argc, char **argv, char **envp)
{
	char		*path;

	if (argc > 2)
		return (putstr_err("bash: cd: too many arguments\n", 1));
	else if (argc == 1)
	{
		if (!((path = ft_getenv("HOME")) && *path))
			return (putstr_err("bash: cd: HOME not set\n", 1));
	}
	else
		path = argv[1];
	if (chdir(path) == -1)
	{
		ft_perror(path);
		return (EXIT_FAILURE);
	}
	ft_setenv("OLDPWD", ft_getenv("PWD"));
	msg_assert(path = getcwd(NULL, 0), "getcwd error");
	ft_setenv("PWD", path);
	free(path);
	return (EXIT_SUCCESS);
}
