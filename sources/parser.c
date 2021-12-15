#include "../minishell.h"

char **get_path(char **envp)
{
	char	**path;
	int		index;

	index = 0;
	while (envp[index])
	{
		if (!strncmp("PATH=", envp[index], 5))
			break ;
		index++;
	}
	if (!envp[index])
		return (NULL);
	path = ft_split(envp[index] + 5, ':');
	return (path);
}

t_command	**parse_string(char **envp, char *file)
{
	t_command	**command;
	char		**path;
	char		*absolute_path;
	int 		index;
	int			counter;

	index = 0;
	counter = 0;
	path = get_path(envp);
	if (!access(file, F_OK))
		printf("file is present\n");
	else
	{
		file = ft_strjoin("/", file);
		while (path[index])
		{
			absolute_path = ft_strjoin(path[index], file);
			if (!access(absolute_path, F_OK))
				printf("file is present\n");
			free(absolute_path);
			index++;
		}
	}
	command = malloc(sizeof(t_command *) * );
	command->command = file;
	command->flag = 0;
	return (command);
}
