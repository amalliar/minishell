/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 19:54:51 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_TOOLS_H
# define ENV_TOOLS_H

int		init_environ(void);
char	*ft_getenv(const char *name);
int		ft_unsetenv(const char *name);
char	*ft_putenv(const char *string);
char	*ft_setenv(const char *name, const char *value);
char	**findenv(const char *name);

#endif
