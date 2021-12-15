
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

void show_path(char **path)
{
	while (*path)
	{
		printf("%s\n", *path);
		path++;
	}
}

char **get_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	temp = envp[i] + 6;
	path = ft_split(temp, ':');
	return (path);
}


t_command	*parse_string(char **envp, char *file)
{
	t_command	*command;
	char		**path;
	char		*absolute_path;
	int 		i;

	i = 0;
	path = get_path(envp);
	if (!access(file, F_OK))
		printf("file is present\n");
	else
	{
		file = ft_strjoin("/", file);
		while (path[i])
		{
			absolute_path = ft_strjoin(path[i], file);
			if (!access(absolute_path, F_OK))
				printf("file is present\n");
			free(absolute_path);
			i++;
		}
	}
	command = malloc(sizeof(t_command));
	command->command = file;
	command->flag = 0;
	return (command);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		str = readline("hello$ ");
		parse_string(envp, str);
		if (strlen(str) > 0)
			add_history(str);
	}
	return (0);
}