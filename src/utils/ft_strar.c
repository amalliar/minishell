/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chararr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 21:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/22 21:56:00 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int                                             strarr_free(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
	return (0);
}

size_t  										strarr_len(char **str_arr)
{
	size_t  len;

	len = 0;
	while (*(str_arr++))
		len++;
	return (len);
}
