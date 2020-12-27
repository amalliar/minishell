/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/10 21:05:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <error_tools.h>
#include <ft_string.h>
#include <env_tools.h>
#include <ft_stdio.h>

#include <process.h>
#include <ft_list.h>

/*
extern char **g_environ;

void testAll()
{
	char **envp;
	char **envp_new;

	envp = g_environ;
	envp_new = g_environ;
	ft_getenv("sadf");
//	while (*envp || *envp_new)
//		msg_assert(!ft_strcmp(*(envp++), *(envp_new++)), "init_environ error");
	char *save_path = ft_strdup(ft_getenv("PATH"));
	ft_printf("[%s]\n", ft_getenv("PATH"));
	msg_assert(!ft_strcmp(ft_putenv("TEST=HELLO"), "TEST=HELLO"), "problem in putenv");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), "HELLO"), "problem in getenv");
	msg_assert(!ft_strcmp(ft_setenv("TEST", "HELL"), "TEST=HELL"), "problem in setenv");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), "HELL"), "problem in getenv");
	ft_unsetenv("TEST");
	ft_getenv("sadf");
	ft_printf("[%s]\n{%s}\n",save_path, ft_getenv("PATH"));
	msg_assert(ft_getenv("TEST") ==  NULL,"problem in unsetenv");
	msg_assert(!ft_strcmp(ft_getenv("PATH"), save_path), "problem in unsetenv or set env in PATH");
	ft_unsetenv("TEST");
	msg_assert(ft_getenv("TEST") == NULL,"problem in unsetenv (TEST)");
}

void preset(char **envp)
{
	init_environ(envp);
}

int main(int argc, char **argv, char **envp)
{
//	signal(SIGINT, SIG_IGN); //TODO : add /n when runnig blah blah blah
	preset(envp);
	testAll();
	(void)argc;
	(void)argv;

	t_command command = {"/usr/bin/yes", argv, 1, 0,0,0};
	t_command command1 = {"/bin/cat", ft_split("cat -e", ' '), 1, 0,0,0};
	t_command command2 = {"/bin/head", ft_split("head", ' '), 0,0,0,0, "test", "test1"};


	t_command command3 = {"/usr/bin/yes", argv, 1, 0,0,0};
	t_command command4 = {"/bin/head", ft_split("head", ' '), 0, 0,0,0};

	t_command command5 = {"echo", ft_split("echo -n -n -n -n HELLO_WORLD", ' '), 1, 0,0,0};
	t_command command6 = {"/bin/cat", ft_split("cat -e", ' '), 0, 0,0,0};


	t_list *head = ft_lstnew(&command);
	ft_lstadd_back(&head, ft_lstnew(&command1));
	ft_lstadd_back(&head, ft_lstnew(&command2));
	ft_lstadd_back(&head, ft_lstnew(&command3));
	ft_lstadd_back(&head, ft_lstnew(&command4));
	ft_lstadd_back(&head, ft_lstnew(&command5));
	ft_lstadd_back(&head, ft_lstnew(&command6));
	//read line
	//parse line
	process(head);
	//write bash$:...
	// goto: read line

	//while(1)
	//{
	//	ft_printf("hello\n");
	//	sleep(2);
	//}
	return 0;
}
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ft_stdio.h"
#include "ft_list.h"
#include "ft_string.h"
#include "msh.h"
#include "lexer.h"

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

char	**alloc_dynamic_envp(char **envp)
{
	int		i;
	char	**envp_dup;

	i = 0;
	while (envp[i])
		++i;
	if (!(envp_dup = malloc(i * sizeof(char *))))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	envp_dup[i--] = NULL;
	while (i >= 0)
	{
		if (!(envp_dup[i] = ft_strdup(envp[i])))
			exit_failure(MSH_VERSION": %s\n", strerror(errno));
		--i;
	}
	return (envp_dup);
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

	envp = alloc_dynamic_envp(envp);
	set_prompt(MSH_VERSION"$ ");
	while (1)
	{
		ft_printf("%s", get_prompt());
		if ((ret = ft_get_next_line(STDIN_FILENO, &line)) <= 0)
			read_loop_except(ret);
		token_list = lexer_proc(line);
		free(line);
		//exec_token_list() or need to build an AST first?
		lexer_clear(&token_list);
	}
	return (0);
}
