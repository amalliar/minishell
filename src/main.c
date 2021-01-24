/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/22 13:24:04 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "msh.h"
#include "lexer.h"
#include "parser.h"
#include "ft_stdio.h"
#include "ft_list.h"
#include "ft_string.h"
#include "env_tools.h"
#include "error_tools.h"
#include "process.h"
#include "prompt_tools.h"
#include "handlers.h"


static void		read_loop_except(int ret)
{
	if (ret == 0)
	{
		// TODO: replace with msh_exit built-in.
		ft_printf("\nexit\n");
		exit(EXIT_SUCCESS);
	}
	exit_failure(MSH_VERSION": %s\n", strerror(errno));
}

int				main(int argc, char **argv, char **envp)
{
	int			ret;
	char		*line;
	t_token		*token_list;
	t_list		*command_list;

	signal(SIGINT, sigint_h);
	signal(SIGQUIT, sigint_h);
	set_prompt(MSH_VERSION"$ ");
	while (1)
	{
		ft_printf("%s", get_prompt());
		if ((ret = ft_get_next_line(STDIN_FILENO, &line)) <= 0)
			read_loop_except(ret);
		while (line)
		{
			if ((token_list = lexer_proc(&line)))
			{
				//print_token_list(token_list);
				if ((command_list = parser_proc(token_list)))
				{
					//print_command_list(command_list);
					if (process(command_list) != 0)
						; // print some error message and continue
					parser_clear(&command_list);
				}
				lexer_clear(token_list);
			}
		}
	}
	return (0);
}

// export _32
//declare -x a=ec
//declare -x b=ho
//msh-0.1$ $a$b hello
//export "Ha HA"=tr
//ЭКРАНИРОВАНИЕ!!!!!!!!!!!!!!!!!!
//%?
//норма!!!

