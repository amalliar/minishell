#include <ft_stdio.h>
#include "prompt_tools.h"

void sigint_h(int n)
{
	(void)n;
	ft_printf("\n%s", get_prompt());
}