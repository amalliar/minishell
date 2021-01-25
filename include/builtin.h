/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:54:10 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/10 02:54:11 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct	s_builtin
{
	char		*name;
	int			(*func)();
}				t_builtin;

const t_builtin *check_builtin(char *command);
int				run_builtin(char *command, char **argv, char **envp);
int				bi_cd(int argc, char **argv);
int				bi_pwd(int argc, char **argv, char **envp);
int				bi_env(int argc, char **argv, char **envp);
int				bi_exit(int argc, char **argv, char **envp);
int				bi_echo(int argc, char **argv, char **envp);
int				bi_unset(int argc, char **argv, char **envp);
int				bi_export(int argc, char **argv, char **envp);

#endif
