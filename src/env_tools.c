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
#include <errno.h>
#include <error_tools.h>
#include <other_tools.h>
#include <ft_ctype.h>

char **g_environ;
static int g_initialized = 0;

static int		copy_env(int expand)
{
	size_t	envlen;
	char	**envp;

	envlen = strarr_len(g_environ);
	if (!(envp = ft_calloc(envlen + expand + 1, sizeof(char *))))
		return (0);
	while (envlen--)
	{
		if (!(envp[envlen] = ft_strdup(g_environ[envlen])))
			return (strarr_free(envp + envlen));
	}
	if (g_initialized)
		strarr_free(g_environ);
	g_environ = envp;
	return (1);
	errno;
}

int				init_environ(char **envp)
{
	g_environ = envp;
	if (g_initialized)
		return (1);
	g_initialized = copy_env(0);
	return (g_initialized);
}

static char		**findenv(const char *name)
{
	size_t		namelen;
	char		**envp;
	char		*eq_char;

	msg_assert(g_initialized, "Use init_environ first");
	eq_char = ft_strchr(name, '=');
	namelen = eq_char ? eq_char - name : ft_strlen(name);
	envp = g_environ;
	while (envp && *envp != NULL)
	{
		if (!ft_strncmp(name, *envp, namelen))
			return (envp);
		envp++;
	}
	return (0);
}

char			*ft_getenv(const char *name)
{
	char **env;
	char *val;

	msg_assert(g_initialized, "Use init_environ first");
	if (!(env = findenv(name)))
		return (NULL);
	val = ft_strchr(*env, '=') + 1;
	return (val);
}

int				ft_unsetenv(const char *name)
{
	char **envp;

	msg_assert(g_initialized, "Use init_environ first");
	if (!(envp = findenv(name)))
		return (0);
	free(*envp);
	while ((envp[0] = envp[1]))
		envp++;
	return (1);
}

char			*ft_putenv(const char *string)
{
	char	**envp;
	size_t	envlen;

	msg_assert(g_initialized, "Use init_environ first");
	msg_assert(string, "String is NULL");
	if (!ft_isalpha(string[0]))
		return (NULL);
	if (!ft_unsetenv(string))
		copy_env(1);
	envlen = strarr_len(g_environ);
	return (g_environ[envlen] = ft_strdup(string));
}

char			*ft_setenv(const char *name, const char *value)
{
	char *tmp;
	char *ret;

	msg_assert(g_initialized, "Use init_environ first");
	msg_assert(value, "Pointers are NULL"); //TODO: possibility value == ""
	if (!(name = ft_strjoin(name, "=")))
		return (0);
	tmp = ft_strjoin(name, value);
	ret = ft_putenv(tmp);
	free(tmp);
	free((char *)name);
	return (ret);
}
