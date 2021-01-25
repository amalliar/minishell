/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:35:09 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 20:05:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/stat.h>
#include <env_tools.h>
#include <ft_string.h>
#include <error_tools.h>
#include <other_tools.h>
#include <builtin.h>
#include "msh.h"

#define MSH_V	MSH_VERSION

bool				file_exists(char *filename)
{
	struct stat		buffer;

	return (stat(filename, &buffer) == 0);
}

static char			*find_in_path(char *bin_name)
{
	char			*path;
	char			**splitted;
	char			**walker;
	char			*tmp;
	char			*tmp2;

	path = ft_getenv("PATH");
	if (!path)
		return (NULL);
	splitted = ft_split(path, ":");
	msg_assert(walker = splitted, MSH_V": bad allocation");
	while (walker && *walker)
	{
		msg_assert(tmp2 = ft_strjoin(*walker, "/"), MSH_V": bad allocation");
		msg_assert(tmp = ft_strjoin(tmp2, bin_name), MSH_V": bad allocation");
		free(tmp2);
		if (file_exists(tmp))
			break ;
		free(tmp);
		tmp = NULL;
		walker++;
	}
	strarr_free(splitted);
	return (tmp);
}

static char			*kostil(char *bin_name)
{
	if (check_builtin(bin_name))
		return (NULL);
	if (!ft_strchr(bin_name, '/'))
		return (find_in_path(bin_name));
	return (NULL);
}

char				*get_full_name(char *bin_name)
{
	char *ret;

	if (!(ret = kostil(bin_name)))
		return (ft_strdup(bin_name));
	return (ret);
}
