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

static int g_prev_pipe;
extern char **environ;

void child(const t_command *command, int *pipefd)
{
	dup2(g_prev_pipe, 0); //TODO:  fd leak? g_pipe == 0?!
	g_prev_pipe = 0;
	if(command->pipe)
	{
		g_prev_pipe = pipefd[1];
		dup2(pipefd[1], 1);
	}
	execve(command->name, command->params, environ);
	printf("CHILD: %s\n", strerror(errno));
	printf("HIT\n");
}

void process_one(const t_command *command)
{
	pid_t pid;
	int status;
	int pipefd[2];
	if (command->pipe)
		if (pipe(pipefd) == -1) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	pid = fork();

	if (pid == -1)
	{
		perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
	} else if (pid == 0) // Потомок
	{
		printf("CHILD");
		child(command, pipefd);
		exit(42);
	} else //предок
	{
		printf("PAR");
		if(!command->pipe)
			wait(&status);
		if (!errno)
			printf("ERROR: %s\n", strerror(errno));
	}
}

int process(const t_list *commands)
{
	while(commands)
	{
		process_one(commands->content);
		commands = commands->next;
	}
}

