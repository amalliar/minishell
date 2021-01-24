/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_tools.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 10:32:06 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/24 10:32:30 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMSH_FD_TOOLS_H
# define CMSH_FD_TOOLS_H

void		save_fd(int *std_fds);
void		dup2move(int old_fd, int new_fd);
void		load_fd(int *std_fds);

#endif
