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

// TODO: remove from final version.
static void		print_token_list(t_token *token_list)
{
	while (token_list)
	{
		ft_printf("[%s]", token_list->data);
		if (token_list->type == TT_PIPE)
			ft_printf("[%s]\n", "TT_PIPE");
		else if (token_list->type == TT_LEFT_AB)
			ft_printf("[%s]\n", "TT_LEFT_AB");
		else if (token_list->type == TT_RIGHT_AB)
			ft_printf("[%s]\n", "TT_RIGHT_AB");
		else if (token_list->type == TT_RIGHT_DAB)
			ft_printf("[%s]\n", "TT_RIGHT_DAB");
		else if (token_list->type == TT_WORD)
			ft_printf("[%s]\n", "TT_WORD");
		else if (token_list->type == TT_NULL)
			ft_printf("[%s]\n", "TT_NULL");
		token_list = token_list->next;
	}
}

// TODO: remove from final version.
static void		print_params(char **params)
{
	int		count;

	count = 0;
	while (*params)
		ft_printf("arg_%d [%s]\n", count++, *params++);
}

static void		print_command_list(t_list *command_list)
{
	t_command		*cmd;
	int				cmd_idx;
	static int		batch_idx = 0;

	cmd_idx = 0;
	while (command_list)
	{
		cmd = command_list->content;
		if (!cmd_idx)
			ft_printf("-------------------- NEXT_BATCH --------------------\n", batch_idx++);
		ft_printf("CMD_%d\n", cmd_idx++);
		if (cmd->name)
			ft_printf("name [%s]\n", cmd->name);
		if (cmd->params)
			print_params(cmd->params);
		if (cmd->f_stdin)
			ft_printf("< [%s]\n", cmd->new_stdin);
		if (cmd->f_stdout)
			ft_printf("> [%s]\n", cmd->new_stdout);
		if (cmd->f_stdout_append)
			ft_printf(">> [%s]\n", cmd->new_stdout);
		if (cmd->pipe)
			ft_printf("pipe\n");
		ft_printf("\n");
		if (!command_list->next)
			ft_printf("\n");
		command_list = command_list->next;
	}
}



int				main(int argc, char **argv, char **envp)
{
	int			ret;
	char		*line;
	t_token		*token_list;
	t_list		*command_list;

	signal(SIGINT, sigint_h);
	signal(SIGQUIT, sigint_h);
	if (!init_environ(envp))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
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
				//	print_command_list(command_list);
					if (process(command_list) != 0);
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

