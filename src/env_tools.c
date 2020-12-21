/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/21 17:56:00 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

extern char **environ;

char *ft_getenv(const char *name);
char *ft_setenv(const char *name, const char *value, int overwrite);
char *ft_putenv(const char *string);
int  clearenv(void);
