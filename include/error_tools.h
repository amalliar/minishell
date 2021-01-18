/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.tu>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:21:12 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/19 08:21:19 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_TOOLS_H
# define ERROR_TOOLS_H

void	msg_exit(int i, char *msg);
void	msg_assert(_Bool exp, char *msg);
void	ft_perror(const char *msg);
void	error_check(int ret_of_func, const char *err_msg);
void	exit_failure(char *format, ...);

#endif
