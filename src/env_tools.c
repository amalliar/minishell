/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbashir <mi243@ya.ru>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:56:00 by sbashir           #+#    #+#             */
/*   Updated: 2020/12/22 17:02:41 by sbashir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_stdlib.h>
#include "utils/msg_exit.h"
#include "utils/ft_strar.h"


extern char **environ;
static int initialized = 0;

int init_environ()
{
	size_t envlen;
	char **envp;

	if (initialized)
		return (1);
	envlen = strarr_len(environ);
	if(!(envp = ft_calloc(sizeof(char *), envlen + 1)))
		return (0);
	while(envlen--)
	{
		if(!(envp[envlen] = ft_strdup(environ[envlen])))
			return (strarr_free(envp + envlen));
	}
	environ = envp;
	initialized = 1;
	return (0);
}

static char **findenv(const char *name)
{
	size_t namelen;
	char **envp;

	namelen = name - ft_strchr(name, '=');
	namelen = namelen ? namelen : ft_strlen(name);
	envp = environ;
	while (*envp)
	{
		if (ft_strncmp(name, *envp, namelen))
			return envp;
		envp++;
	}

	return (0);
}
char *ft_getenv(const char *name)
{
	char *env;

	if (!(env = *findenv(name)))
		return (0); //TODO: Better is empty string
	return (ft_strchr(env, '=') + 1); //TODO: possible problems on realocation
}

int  ft_unsetenv(const char *name)
{
	char **envp;

	msg_exit(initialized, "You need to initialize environ first");
	if (!(envp = findenv(name)))
		return (1);
	free(*envp);
	while ((envp[0] = envp[1]))
		envp++;
	return (1); //TODO: What should be returned?
}

char *ft_setenv(const char *name, const char *value)
{
	char **envp;
	msg_exit(initialized, "You need to initialize environ first");

	envp = ft_calloc();
	ft_unsetenv(name);
}

char *ft_putenv(const char *string)
{

}



#ifdef TEST
/*
  * Stand-alone program for test purposes.
  */

/* printenv - display environment */

static void printenv()
{
    char  **envp;

    for (envp = environ; envp && *envp; envp++)
	printf("%s\n", *envp);
}

int     main(argc, argv)
int     argc;
char  	**argv;
{
    char   *cp;
    int     changed = 0;

    if (argc < 2) {
	printf("usage: %s name[=value]...\n", argv[0]);
	return (1);
    }
    while (--argc && *++argv) {
	if (argv[0][0] == '-') {		/* unsetenv() test */
	    unsetenv(argv[0] + 1);
	    changed = 1;
	} else if (strchr(argv[0], '=') == 0) {	/* getenv() test */
	    cp = getenv(argv[0]);
	    printf("%s: %s\n", argv[0], cp ? cp : "not found");
	} else {				/* putenv() test */
	    if (putenv(argv[0])) {
		perror("putenv");
		return (1);
	    }
	    changed = 1;
	}
    }
    if (changed)
	printenv();
    return (0);
}

#endif /* TEST */