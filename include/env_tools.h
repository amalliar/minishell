/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/22 17:02:41 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOOLS_H
# define ENV_TOOLS_H

int		init_environ(char **envp);
char	*ft_getenv(const char *name);
int		ft_unsetenv(const char *name);
char	*ft_putenv(const char *string);
char	*ft_setenv(const char *name, const char *value);

#endif
