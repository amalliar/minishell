/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 03:33:51 by amalliar          #+#    #+#             */
/*   Updated: 2021/01/08 13:20:28 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <ft_stdio.h>
#include <stdio.h>
#define DIRMAX 1024

int		bi_pwd(int argc, char **argv, char **envp)
{
	char dir[DIRMAX];
	ft_printf("%s\n", getcwd(dir, DIRMAX));
	return (0);
}
