/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/16 05:59:52 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ft_stdio.h"
#include "ft_list.h"
#include "ft_string.h"
#include "msh.h"
#include "lexer.h"
#include "env_tools.h"

char	*g_msh_prompt = NULL;

void	set_prompt(char *new_prompt)
{
	char	*new_prompt_dup;

	if (!(new_prompt_dup = ft_strdup(new_prompt)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	if (g_msh_prompt)
		free(g_msh_prompt);
	g_msh_prompt = new_prompt_dup;
}

char	*get_prompt(void)
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

int		main(int argc, char **argv, char **envp)
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
			command_list = parser_proc(token_list);
			if (process(command_list) != 0)
				; // print some error message and continue
			lexer_clear(&token_list);
			parser_clear(&command_list);
		}
	}
	return (0);
}
