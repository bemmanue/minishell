
#include <builtin.h>

int ft_arrlen(char **array)
{
    int i;

    if (!array)
        return (0);
    i = 0;
    while (array[i])
        i++;
    return (i);
}

void    change_env(char *new, char ***envp, char *name)
{
    int     count;
    char    **temp;

    count = ft_arrlen(*envp);
    temp = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    while ((*envp)[i])
    {
        if (!ft_strncmp(name, ft_strcut((*envp)[i], "="), ft_strlen(name)))
            temp[i] = ft_strdup(new);
        else
            temp[i] = ft_strdup((*envp)[i]);
        i++;
    }
    temp[i] = NULL;
    *envp = temp;
}

void    add_env(char *new, char ***envp)
{
    int     count;
    char    **temp;

    count = ft_arrlen(*envp) + 1;
    temp = malloc(sizeof(char *) * (count + 1));
    int i = 0;
    while ((*envp)[i])
    {
        temp[i] = ft_strdup((*envp)[i]);
        i++;
    }
    temp[i++] = ft_strdup(new);
    temp[i] = NULL;
    *envp = temp;
}

int ft_export(char **argv, char ***envp)
{
    char    *name;

    (void)envp;
    (void)argv;
    int i;

    i = 1;
    while (argv[i])
    {
        if (ft_strchr(argv[i], '='))
        {
            name = ft_strcut(argv[i], "=");
            if (!getenv(name))
                add_env(argv[i], envp);
            else
                change_env(argv[i], envp, name);
        }
        i++;
    }
    return (0);
}
