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
#include <builtin.h>

#include <sys/wait.h>
#include <fcntl.h>
#include <ft_string.h>
#include <error_tools.h>
#include <stdbool.h>
#include "fd_tools.h"

static int g_prev_pipe;
unsigned char g_question;

static void		configure_redirection(const t_command *command, int *pipefd)
{
	int			tmp_fd;
	int			flag;

	if (g_prev_pipe)
		dup2move(g_prev_pipe, 0);
	if (command->pipe)
	{
		error_check(close(pipefd[0]), "bash: close");
		dup2move(pipefd[1], 1);
	}
	if (command->f_stdout || command->f_stdout_append)
	{
		flag = command->f_stdout_append ? O_APPEND : O_TRUNC;
		tmp_fd = open(command->new_stdout, O_WRONLY | O_CREAT | flag, 0664);
		error_check(tmp_fd, command->new_stdin);
		dup2move(tmp_fd, 1);
	}
	if (command->f_stdin)
	{
		tmp_fd = open(command->new_stdin, O_RDONLY);
		error_check(tmp_fd, command->new_stdin);
		dup2move(tmp_fd, 0);
	}
}

int				child(const t_command *cmd, int *pipefd, bool run_fork)
{
	extern char	**g_environ;
	int			ret;

	ret = EXIT_SUCCESS;
	configure_redirection(cmd, pipefd);
	if (check_builtin(cmd->name))
		ret = run_builtin(cmd->name, cmd->params, g_environ);
	else
		error_check(execve(cmd->name, cmd->params, g_environ), cmd->name);
	if (run_fork)
		exit(ret);
	return (ret);
}

int				parent(const t_command *command, int *pipefd, pid_t pid)
{
	static pid_t	pids[1024];
	static int		pid_it;
	int				status;
	int				it;

	if (g_prev_pipe)
		close(g_prev_pipe);
	g_prev_pipe = 0;
	pids[pid_it++] = pid;
	if (command->pipe)
	{
		error_check(close(pipefd[1]), "bash: close");
		g_prev_pipe = pipefd[0];
		return (EXIT_SUCCESS);
	}
	it = 0;
	while (it < pid_it)
		waitpid(pids[it++], &status, 0);
	pid_it = 0;
	ft_memset(pids, 0, sizeof(pids));
	return (g_question = status);
}


int				process(const t_list *commands)
{
	pid_t		pid;
	int			pipefd[2];
	static int	std_fds[3];
	t_command	*cmd;
	bool		run_fork;

	save_fd(std_fds);
	while (commands && (cmd = commands->content))
	{
		pid = 0;
		run_fork = cmd->pipe || g_prev_pipe || !check_builtin(cmd->name);
		if (run_fork)
		{
			if (cmd->pipe)
				error_check(pipe(pipefd), "pipe");
			error_check(pid = fork(), "fork");
		}
		if (pid == 0)
			child(cmd, pipefd, run_fork);
		if (pid > 0)
			parent(cmd, pipefd, pid);
		load_fd(std_fds);
		commands = commands->next;
	}
	return (1);
}
