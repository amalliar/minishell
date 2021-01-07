/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 03:37:20 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/02 03:37:25 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_list.h>
#include <ft_stdlib.h>
#include <unistd.h>
#include <process.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ft_string.h>
#include "utils/msg_exit.h"

static int g_prev_pipe;
extern char **environ;

#define ERR_TEST \
do                 {\
if (!errno)\
fprintf(stderr,"ERROR: %s %s:%d function:%s\n", strerror(errno),__FILE__, __LINE__, __FUNCTION__ );\
} while (0)
static void dup2move(int old_fd, int new_fd)
{
	errno = 0;
	error_check(dup2(old_fd, new_fd), "dup2 in dup2move");
	errno = 0;
	error_check(close(old_fd), "close oldfd dup2");
}

static void configure_redirection(const t_command *command, int *pipefd)
{
	int tmp_fd;

	if (g_prev_pipe)
		dup2move(g_prev_pipe, 0); //TODO:  fd leak? g_pipe == 0?!
	if (command->pipe)
	{
		error_check(close(pipefd[0]), "close");
		dup2move(pipefd[1], 1);
	}
	if (command->f_stdout)
	{
		tmp_fd = open(command->new_stdout, O_WRONLY | O_CREAT | \
        ((command->f_stdout_append) ? O_APPEND : 0));
		error_check( tmp_fd, command->new_stdin);
		//TODO: new file has wrong user rights
		dup2move(tmp_fd, 1); //TODO: Add check
	}
	if (command->f_stdin)
	{
		tmp_fd = open(command->new_stdin, O_RDONLY);
		error_check( tmp_fd, command->new_stdin);
		dup2move(tmp_fd, 0);
	}
}

void child(const t_command *command, int *pipefd)
{
	int tmp_fd;

	configure_redirection(command, pipefd);
	//TODO : restore signal!!
	errno = 0;
	error_check(execve(command->name, command->params, environ), command->name);
	exit(EXIT_SUCCESS);
}

int parent(const t_command *command, int *pipefd, pid_t pid)
{
	static pid_t pids[100];
	int pid_it;
	int status;

	pid_it = 0;
	if (g_prev_pipe)
		close(g_prev_pipe);
	g_prev_pipe = 0;
	pids[pid_it++] = pid;
	if (command->pipe)
	{
		error_check(close(pipefd[1]), "close");
		g_prev_pipe = pipefd[0];
	} else
	{
		for (int i = 0; i < pid_it; i++)
		{
			waitpid(pids[i], &status, 0);
		}
		ft_memset(pids, 0, sizeof(pids));
	}
	return (0);
}

int process(const t_list *commands)
{
	pid_t pid;
	int status;
	int pipefd[2];
	t_command *command;

	while (commands && (command = commands->content))
	{
	//	if (!command->pipe && command->f_builtin)
	//	{
	//		commands = commands->next;
	//		continue;
	//	}
		errno = 0; //TODO : maybe delete errno=0 becose we are testing func_ret
		if (command->pipe)
			error_check(pipe(pipefd), "pipe");
		error_check(pid = fork(), "fork");
		if (pid == 0) // Потомок
			child(command, pipefd);
		if (pid > 0) //Предок
			parent(command, pipefd, pid); // error we
		commands = commands->next;
	}
	return (1);
}

