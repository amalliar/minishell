#ifndef CMSH_FD_TOOLS_H
#define CMSH_FD_TOOLS_H

void			save_fd(int *std_fds);
void		    dup2move(int old_fd, int new_fd);
void			load_fd(int *std_fds);
#endif
