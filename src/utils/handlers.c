#include <ft_stdio.h>
#include "prompt_tools.h"

void sigint_h(int n)
{
	extern int g_ret;

	(void)n;
	ft_printf("\n%s", get_prompt());
	g_ret = 1;
}

void sigint_h_2(int n)
{
	extern int g_ret;

	(void)n;
	g_ret = 130;
}