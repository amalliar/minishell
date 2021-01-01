/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/22 17:02:41 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdlib.h>
#include "utils/msg_exit.h"
#include "utils/ft_strar.h"
#include <stdio.h>

extern char **environ;
static char **ft_env;
static int initialized = 0;

static int copy_env(int expand)
{
	size_t envlen;
	char **envp;

	envlen = strarr_len(environ);
	if(!(envp = ft_calloc(envlen + expand + 1,sizeof(char *))))
		return (0);
	while(envlen--)
	{
		if(!(envp[envlen] = ft_strdup((initialized ? ft_env : environ)[envlen])))
			return (strarr_free(envp + envlen));
	}
	if(initialized)
		strarr_free(ft_env);
	ft_env = envp;
	return (1);
}

int init_environ()
{
	if (initialized)
		return (1);
	initialized = copy_env(0);
	return (initialized);
}

#include "ft_stdio.h"

static char **findenv(const char *name)
{
	size_t namelen;
	char **envp;
	char *eq_char;

	eq_char = ft_strchr(name, '=');
	namelen = eq_char ? eq_char - name : ft_strlen(name);
	envp = ft_env;
	while (envp && *envp != NULL)
	{
		printf("[%s\n]"	, *envp);
		if (!ft_strncmp(name, *envp, namelen))
			return envp;
		envp++;
	}
//	write (2, "ЭТО ПРИНТФ БЕЗ КОТОРОГО ОШИБКА\n", 20);
// TODO: WTF??? working with printf
	return (0);
}


char *ft_getenv(const char *name)
{
	char *env;
	char *val;

	//printf("asdf: %s\n", name);
	if (!(env = *findenv(name)))
	{
		//printf("asdf\n");
		return (ft_strdup(""));
	}
	//printf("asdf: %s\n", name);
	val = ft_strdup(ft_strchr(env, '=') + 1);
	return (val);
}

int  ft_unsetenv(const char *name)
{
	char **envp;

	msg_assert(initialized, "You need to initialize environ first");
	if (!(envp = findenv(name)))
		return (0);
	free(*envp);
	while ((envp[0] = envp[1]))
		envp++;
	return (1);
}

char *ft_putenv(const char *string)
{
	char **envp;
	size_t envlen;

	msg_assert(initialized, "You need to initialize environ first");
	msg_assert(string, "String is NULL");
	if(!ft_unsetenv(string))
		copy_env(1);
	envlen = strarr_len(ft_env);
	return (ft_env[envlen] = ft_strdup(string));
}


char *ft_setenv(const char *name, const char *value)
{
	char *tmp;
	char *ret;

	msg_assert(name && value, "Pointers are NULL");
	if(!(name = ft_strjoin(name, "=")))
		return (0);
	tmp = ft_strjoin(name, value);
	ret = ft_putenv(tmp);
	free(tmp);
	free((char *)name);
	return ret;
}
