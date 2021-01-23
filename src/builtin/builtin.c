/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 13:23:51 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/08 14:49:53 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>
#include <ft_string.h>

#include <error_tools.h>
#include <other_tools.h>


static t_builtin g_builtins[] = { \
								{"export", bi_export}, \
								{"echo", bi_echo}, \
								{"unset", bi_unset}, \
								{"exit", bi_exit}, \
								{"pwd", bi_pwd}, \
								{"env", bi_env}, \
								{"cd", bi_cd},
                                {NULL, NULL}
};

const t_builtin		*check_builtin(char *command)
{
	int i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(g_builtins[i].name, command))
			return (&(g_builtins[i]));
		i++;
	}
	return (NULL);
}

int					run_builtin(char *command, char **argv, char **envp)
{
	const t_builtin	*bi;
	int				ret;

	bi = check_builtin(command);
	msg_assert(bi, "Not builtin command");
	ret = bi->func(strarr_len(argv), argv, envp);
	return (ret);
}
