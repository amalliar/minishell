#include <errno.h>
#include <error_tools.h>
#include <unistd.h>

#include "fd_tools.h"


void		dup2move(int old_fd, int new_fd)
{
    errno = 0;
    error_check(dup2(old_fd, new_fd), "dup2 in dup2move");
    errno = 0;
    error_check(close(old_fd), "close oldfd dup2");
}



void save_fd(int *std_fds) {
    int			it;

    it = 0;
    if (std_fds[1])
        return ;
    while (it < 3)
    {
        error_check(std_fds[it] = dup(it), "save_fd: dup");
        it++;
    }
}

void			load_fd(int *std_fds)
{
    int			it;

    it = 0;
    while (it < 3)
    {
        error_check(dup2(std_fds[it], it), "load_fd: dup2");
        it++;
    }
}