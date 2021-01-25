/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:02:00 by sbashir           #+#    #+#             */
/*   Updated: 2021/01/25 18:27:12 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTHER_TOOLS_H
# define OTHER_TOOLS_H

# include <stdbool.h>

int			strarr_free(char **str_arr);
size_t		strarr_len(char **str_arr);
char		*get_full_name(char *bin_name);
bool		file_exists(char *filename);

#endif
