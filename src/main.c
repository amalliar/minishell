/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2020/12/14 03:34:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "utils/msg_exit.h"
#include <ft_string.h>
#include <env_tools.h>
#include <ft_stdio.h>

#include <process.h>
#include <ft_list.h>

extern char **g_environ;

void testAll()
{
	char **envp;
	char **envp_new;

	envp = g_environ;
	envp_new = g_environ;
	ft_getenv("sadf");
	while (*envp || *envp_new)
		msg_assert(!ft_strcmp(*(envp++), *(envp_new++)), "init_environ error");
	char *save_path = ft_getenv("PATH");
	msg_assert(!ft_strcmp(ft_putenv("TEST=HELLO"), "TEST=HELLO"), "problem in putenv");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), "HELLO"), "problem in getenv");
	msg_assert(!ft_strcmp(ft_setenv("TEST", "HELL"), "TEST=HELL"), "problem in setenv");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), "HELL"), "problem in getenv");
	ft_unsetenv("TEST");
	ft_getenv("sadf");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), ""),"problem in unsetenv");
	msg_assert(!ft_strcmp(ft_getenv("PATH"), save_path), "problem in unsetenv or set env in PATH");
	ft_unsetenv("TEST");
	msg_assert(!ft_strcmp(ft_getenv("TEST"), ""),"problem in unsetenv (TEST)");
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
