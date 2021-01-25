#include <ft_stdio.h>
#include "prompt_tools.h"


extern int g_ret;

void sigint_h(int n)
{
	(void)n;
	if(n == SIGINT)
	{
		ft_printf("\n%s", get_prompt());
		g_ret = 1;
	}
}

void pass(int n)
{
	g_ret = 128 + n;
	if(n == SIGQUIT)
		ft_printf("Quit: %d\n", n);
}

void set_default_signals()
{
	signal(SIGINT, pass);
	signal(SIGQUIT, pass);
}

void set_bash_signals()
{
	signal(SIGINT, sigint_h);
	signal(SIGQUIT, SIG_IGN);
}