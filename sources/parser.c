
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_command
{
	char		*command;
	int 		flag;
}				t_command;

char **get_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	temp = envp[i] + 5;
	path = ft_split(temp, ':');
	return (path);
}

t_command	*parse_string(char **envp, char **argv)
{
	t_command	*command;
	char		**path;

	path = get_path(envp);
	while ()


	return (command);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;

	while (1)
	{
		str = readline("hello$ ");
		parse_string(envp, argv);
		if (strlen(str) > 0)
			add_history(str);
	}
	return (0);
}