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
#include <error_tools.h>
#include <env_tools.h>

char **g_environ;
extern int g_ret;

int				ft_unsetenv(const char *name)
{
	char **envp;

	init_environ();
	if (!(envp = findenv(name)))
		return (0);
	free(*envp);
	while ((envp[0] = envp[1]))
		envp++;
	return (1);
}

char			*ft_setenv(const char *name, const char *value)
{
	char *tmp;
	char *ret;

	init_environ();
	msg_assert(value, "Pointers are NULL");
	if (!(name = ft_strjoin(name, "=")))
		return (0);
	tmp = ft_strjoin(name, value);
	ret = ft_putenv(tmp);
	free(tmp);
	free((char *)name);
	return (ret);
}
