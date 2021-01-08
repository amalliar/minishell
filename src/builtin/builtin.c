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

#include "../utils/msg_exit.h"
#include "../utils/ft_strar.h"

#define BUILTINS_SIZE 3 // TODO: Remove it if u can!
static t_builtin builtins[] = {
		{"echo", bi_echo},
		{"pwd", bi_pwd},
		{"env", bi_env}
};

//static const int g_builtins_size = sizeof(builtins)/ sizeof(t_builtin);

const t_builtin * check_builtin(char *command)
{
	int i;

	i = 0;
	while (i < BUILTINS_SIZE)
	{
		if(!ft_strcmp(builtins[i].name, command))
			return (&(builtins[i]));
		i++;
	}
	return (NULL);
}

int run_builtin(char *command, char **argv, char **envp)
{
	const t_builtin *bi;
	int		ret;

	bi = check_builtin(command);
	msg_assert(bi, "Not builtin command");
	ret = bi->func(strarr_len(argv), argv, envp);
	//TODO: ADD RESTORE FD!!!!!!
	return (ret);
}
