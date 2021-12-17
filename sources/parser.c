
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

int	count_argv(char **argv)
{
	int i;

	i = 0;
	if (!argv)
		return (-1);
	while (argv[i])
		i++;
	return (i);
}

char	*full_path(char *str, char **path)
{
	char	*absolute_path;
	int		index;

	index = 0;
	if (is_builtin_command(str))
		return (str);
	if (!access(str, F_OK))
		return (str);
	else
	{
		str = ft_strjoin("/", str);
		while (path[index])
		{
			absolute_path = ft_strjoin(path[index], str);
			if (!access(absolute_path, F_OK))
				return (absolute_path);
			free(absolute_path);
			index++;
		}
	}
	return (NULL);
}

t_command	*new_command(char **argv, char **path)
{
	t_command	*command;
	int			number_of_args;
	int			i;

	i = 0;
	command = malloc(sizeof(t_command));
	command->name = full_path(argv[0], path);
	number_of_args = count_argv(argv) - 1;
	command->argv = malloc(sizeof(char *) * number_of_args);
	while (i < number_of_args)
	{
		command->argv[i] = argv[i + 1];
		i++;
	}
	command->next = NULL;
	return (command);
}

t_command	*parse_string(char **envp, char *str)
{
	char		**commands;
	int			i;
	char		**argv;
	t_command	*command;
	t_command	*temp;
	char		**path;

	i = 0;
	path = get_path(envp);
	commands = ft_split(str, '|');
	argv = ft_split(commands[i++], ' ');
	command = new_command(argv, path);
	free(argv);
	temp = command;
	while (commands[i])
	{
		argv = ft_split(commands[i], ' ');
		temp->next = new_command(argv, path);
		temp = temp->next;
		free(argv);
		i++;
	}
	return (command);
}
