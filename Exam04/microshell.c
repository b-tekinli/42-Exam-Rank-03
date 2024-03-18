#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	fd2(char *str, char *arg)
{
    while (*str)
        write(2, str++, 1);
    if (arg)
        while (*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
    return (1);
}

int    ft_exec(char **av, int i, int tmp, char **env)
{
    av[i] = 0;
    dup2(tmp, 0);
    close(tmp);
    execve(av[0], av, env);
    return (fd2("error: cannot execute ", av[0]));
}

int    main(int ac, char **av, char **env)
{
    int    i = 0, pid = 0, fd[2], tmp = dup(0);

    (void)ac;
    while (av[i] && av[i + 1])
    {
        av = &av[i + 1];
        i = 0;
        while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
            i++;
        if (!strcmp(av[0], "cd"))
        {
            if (i != 2)
                fd2("error: cd: bad arguments", 0);
            else if (chdir(av[1]) != 0)
                fd2("error: cd: cannot change directory to ", av[1]);
        }
        else if (i && (!av[i] || !strcmp(av[i], ";")))
        {
            pid = fork();
            if (!pid)
            {
                if (ft_exec(av, i, tmp, env))
                    return (1);
            }
            else
            {
                close(tmp);
                while (waitpid(-1, 0, 0) != -1)
                    ;
                tmp = dup(0);
            }
        }
        else if(i && !strcmp(av[i], "|"))
        {
            pipe(fd);
            pid = fork();
            if (!pid)
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
                if (ft_exec(av, i, tmp, env))
                    return (1);
            }
            else
            {
                close(fd[1]);
                close(tmp);
                tmp = fd[0];
            }
        }
    }
    close(tmp);
    return(0);
}
