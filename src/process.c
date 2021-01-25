/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 03:37:20 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 19:58:55 by amalliar         ###   ########.fr       */
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
#include <other_tools.h>
#include <errno.h>
#include "fd_tools.h"
#include "handlers.h"
#include "msh.h"

static int g_prev_pipe;
extern int g_ret;

static void		configure_redirection(const t_command *command, int *pipefd)
{
	int			tmp_fd;
	int			flag;

	if (g_prev_pipe)
		dup2move(g_prev_pipe, 0);
	if (command->pipe)
	{
		error_check(close(pipefd[0]), MSH_VERSION": close");
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
	if (run_fork)
		set_default_signals();
	configure_redirection(cmd, pipefd);
	if (!cmd->params)
		ret = 0;
	else if (check_builtin(cmd->name))
		ret = run_builtin(cmd->name, cmd->params, g_environ);
	else if (!ft_strchr(cmd->name, '/'))
	{
		putstr_err(MSH_VERSION": ", 1) && putstr_err(cmd->name, 1);
		ret = putstr_err(": command not found\n", 127);
	}
	else if ((ret = execve(cmd->name, cmd->params, g_environ)) == -1)
	{
		ft_perror(cmd->name);
		exit((errno == 2) ? 127 : 126);
	}
	if (run_fork)
		exit(ret);
	return (ret);
}

static void		interpret_status(int status)
{
	if (WIFEXITED(status) && !WEXITSTATUS(status))
		g_ret = 0;
	else if (WIFEXITED(status) && WEXITSTATUS(status))
		g_ret = WEXITSTATUS(status);
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
		error_check(close(pipefd[1]), MSH_VERSION": close");
		g_prev_pipe = pipefd[0];
		return (EXIT_SUCCESS);
	}
	it = 0;
	set_default_signals();
	while (it < pid_it && waitpid(pids[it++], &status, 0))
		interpret_status(status);
	set_bash_signals();
	pid_it = 0;
	ft_memset(pids, 0, sizeof(pids));
	return (status);
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
		if ((run_fork = cmd->pipe || g_prev_pipe || !check_builtin(cmd->name)))
		{
			if (cmd->pipe)
				error_check(pipe(pipefd), "pipe");
			error_check(pid = fork(), "fork");
		}
		if (pid == 0)
			g_ret = child(cmd, pipefd, run_fork);
		if (pid > 0)
			parent(cmd, pipefd, pid);
		load_fd(std_fds);
		commands = commands->next;
	}
	return (1);
}
