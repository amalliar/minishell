#include <ft_stdio.h>
#include "prompt_tools.h"

void sigint_h(int n)
{
	ft_printf("\n%s", get_prompt());
}