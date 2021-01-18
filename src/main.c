/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/19 08:21:38 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "msh.h"
#include "lexer.h"
#include "ft_stdio.h"
#include "ft_list.h"
#include "ft_string.h"
#include "env_tools.h"
#include "error_tools.h"

char			*g_msh_prompt = NULL;

void			set_prompt(char *new_prompt)
{
	char	*new_prompt_dup;

	if (!(new_prompt_dup = ft_strdup(new_prompt)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	if (g_msh_prompt)
		free(g_msh_prompt);
	g_msh_prompt = new_prompt_dup;
}

char			*get_prompt(void)
{
	if (g_msh_prompt)
		return (g_msh_prompt);
	exit_failure(MSH_VERSION": g_msh_prompt not set\n");
	return (NULL);
}

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

int				main(int argc, char **argv, char **envp)
{
	int			ret;
	char		*line;
	t_token		*token_list;
	t_list		*command_list;

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
			token_list = lexer_proc(&line);
			/*
			command_list = parser_proc(token_list);
			if (process(command_list) != 0)
				; // print some error message and continue
			*/
			print_token_list(token_list);
			lexer_clear(token_list);
			//parser_clear(&command_list);
		}
	}
	return (0);
}
