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

static int g_prev_pipe;
extern char **environ;


#define ERR_TEST \
do                 {\
if (!errno)\
fprintf(stderr,"ERROR: %s %s:%d function:%s\n", strerror(errno),__FILE__, __LINE__, __FUNCTION__ );\
} while (0)
static int dup2move(int old_fd, int new_fd)
{
	dup2(old_fd,new_fd);
	close(old_fd);
	return 0; // TODO: ADD CHECK
}

void child(const t_command *command, int *pipefd)
{
	int tmp_fd;
	if(g_prev_pipe)
	{
		dup2move(g_prev_pipe, 0); //TODO:  fd leak? g_pipe == 0?!
		close(g_prev_pipe);
	}
	if(command->pipe)
	{
		close(pipefd[0]);
		dup2move(pipefd[1], 1);
		ERR_TEST;
	}
	if(command->f_stdout)
	{
		tmp_fd = open(command->new_stdout, O_WRONLY | O_CREAT | \
		((command->f_stdout_append) ? O_APPEND : 0)); //TODO: add open check
		//TODO: new file has wrong user rights
		dup2move(tmp_fd, 1); //TODO: Add check
	}
	if (command->f_stdin)
	{
		tmp_fd = open(command->new_stdin, O_RDONLY); //TODO: add open check
		dup2move(tmp_fd, 0); // TODO: add check
	}
	execve(command->name, command->params, environ);
	ERR_TEST;
	exit(42);
}

void handle(int val)
{
	ERR_TEST;
	fprintf(stderr, "handle_func!!!\n");
	exit(val);
}

int process(const t_list *commands)
{
	//signal(SIGPIPE, handle);
	signal(SIGSTOP, handle);
	pid_t pid;
	pid_t pids[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	int status;
	int pipefd[2];
	t_command *command;

	//save_std();
	int pid_it = 0;
	while(commands)
	{
		command = commands->content;
		if (command->pipe)
			if (pipe(pipefd) == -1)
			{
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
			signal(SIGINT, handle);
			child(command, pipefd);
		} else //предок
		{
			if(g_prev_pipe)
				close(g_prev_pipe);
			g_prev_pipe = 0;
			pids[pid_it++ ] = pid;
			if (command->pipe)
			{
				close(pipefd[1]);
				g_prev_pipe = pipefd[0];
			}
			else
			{
				for (int i = 0;i < pid_it;i++)
				{
					waitpid(pids[i], &status, 0);
				}
				ft_memset(pids, 0, sizeof(pids));
			}
		}
		commands = commands->next;
	}
	return 1;
}

