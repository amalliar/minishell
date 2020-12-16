/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2020/12/14 03:34:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#define DIRMAX 100

int		main(int argc, char **argv)
{
	char dir[DIRMAX];

	printf("%s\n", getcwd(dir, DIRMAX)); //TODO: Delete ft_printf
	return (0);
}
