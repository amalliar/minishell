/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 09:53:18 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 09:53:33 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <msh.h>
#include <ft_string.h>
#include <error_tools.h>
#include <errno.h>
#include <string.h>
#include "prompt_tools.h"

static char		*g_msh_prompt = NULL;

void			set_prompt(char *new_prompt)
{
	char	*new_prompt_dup;

	if (!(new_prompt_dup = ft_strdup(new_prompt)))
		exit_failure(MSH_VERSION": %s\n", strerror(errno));
	if (g_msh_prompt)
		free(g_msh_prompt);
	g_msh_prompt = new_prompt_dup;
}

char			*get_prompt(void)
{
	if (g_msh_prompt)
		return (g_msh_prompt);
	exit_failure(MSH_VERSION": g_msh_prompt not set\n");
	return (NULL);
}
