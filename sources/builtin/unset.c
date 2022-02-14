
#include <builtin.h>

static int  is_unset(char *envp, char **argv)
{
    char    *env;
    int     i;

    env = ft_strcut(envp, "=");
    i = 1;
    while (argv[i])
    {
        if (getenv(argv[i]) && !ft_strncmp(argv[i], env, ft_strlen(argv[i])))
            return (1);
        i++;
    }
    return (0);
}

static int  ft_count(char **argv, char **envp)
{
    int count;
    int i;

    count = 0;
    while (envp[count])
        count++;
    i = 1;
    while (argv[i])
    {
        if (getenv(argv[i]))
            count--;
        i++;
    }
    return (i);
}

int ft_unset(char **argv, char ***envp)
{
    int     count;
    char    **temp;
    int     i;
    int     j;

    i = 0;
    j = 0;
    count = ft_count(argv, *envp);
    temp = malloc(sizeof(char *) * (count + 1));
    while ((*envp)[i])
    {
        if (!is_unset((*envp)[i], argv))
            temp[j++] = (*envp)[i];
        i++;
    }
    temp[j] = NULL;
    *envp = temp;
    return (0);
}
