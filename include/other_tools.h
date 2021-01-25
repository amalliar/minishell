/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:02:00 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/24 10:32:52 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#ifndef OTHER_TOOLS_H
# define OTHER_TOOLS_H

int			strarr_free(char **str_arr);
size_t		strarr_len(char **str_arr);
char		*get_full_name(char *bin_name);
bool		file_exists(char *filename);

#endif
