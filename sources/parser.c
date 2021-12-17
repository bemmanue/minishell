#include "../minishell.h"

char **get_path(char **envp)
{
	char	**path;
	int		index;

	index = 0;
	while (envp[index])
	{
		if (!ft_strncmp("PATH=", envp[index], 5))
			break ;
		index++;
	}
	if (!envp[index])
		return (NULL);
	path = ft_split(envp[index] + 6, ':');
	return (path);
}

int	is_builtin_command(char *name)
{
	if (!strncmp("echo", name, ft_strlen(name)))
		return (1);
	if (!strncmp("cd", name, ft_strlen(name)))
		return (1);
	if (!strncmp("pwd", name, ft_strlen(name)))
		return (1);
	if (!strncmp("export", name, ft_strlen(name)))
		return (1);
	if (!strncmp("unset", name, ft_strlen(name)))
		return (1);
	if (!strncmp("env", name, ft_strlen(name)))
		return (1);
	if (!strncmp("exit", name, ft_strlen(name)))
		return (1);
	return (0);
}

t_command	*fill_command(char *name)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->name = name;
	return (command);
}

t_command	*parse_string(char **envp, char *file)
{
	char	**path;
	char	*absolute_path;
	int		index;

	index = 0;
	if (is_builtin_command(file))
		return (fill_command(file));
	path = get_path(envp);
	if (!access(file, F_OK))
		return (fill_command(file));
	else
	{
		file = ft_strjoin("/", file);
		while (path[index])
		{
			absolute_path = ft_strjoin(path[index], file);
			if (!access(absolute_path, F_OK))
				return (fill_command(absolute_path));
			free(absolute_path);
			index++;
		}
	}
	return (NULL);
}
