/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:33:49 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/10 17:33:51 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env_tools.h>
#include <ft_string.h>
#include <stdbool.h>
#include <ft_ctype.h>
#include <error_tools.h>

static bool check(char *str)
{
	bool check_ = !ft_strchr(str, '=') && !ft_strchr(str, ' ');
	check_ = check_ && (ft_isalpha(str[0]) ||  str[0] == '_');
	return check_;
}

int		bi_unset(int argc, char **argv, char **envp)
{
	int it;

	(void)envp;
	it = 1;
	while (it < argc)
	{
		if(!check(argv[it]))
		{
			putstr_err("unset: '",1);
			putstr_err(argv[it++],1);
			putstr_err("': not a valid identifier", 1);
			continue;
		}
		ft_unsetenv(argv[it]);
		it++;
	}
	return (0);
}
