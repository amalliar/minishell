#ifndef BUILTIN_H
# define BUILTIN_H
typedef struct	s_builtin
{
	char		*name;
	int			(*func)(int, char**, char**);
}				t_builtin;

const t_builtin *check_builtin(char *command);
int				run_builtin(char *command, char **argv, char **envp);
int				bi_cd(int argc, char **argv, char **envp);
int				bi_pwd(int argc, char **argv, char **envp);
int				bi_env(int argc, char **argv, char **envp);
int				bi_exit(int argc, char **argv, char **envp);
int				bi_echo(int argc, char **argv, char **envp);
int				bi_unset(int argc, char **argv, char **envp);
int				bi_export(int argc, char **argv, char **envp);

#endif
