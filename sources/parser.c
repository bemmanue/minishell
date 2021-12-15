
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_command
{
	char				*name;
	struct s_command	*next;
}						t_command;

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
	int		i;

	i = 0;
	if (is_builtin_command(file))
		return (fill_command(file));
	path = get_path(envp);
	if (!access(file, F_OK))
		return (fill_command(file));
	else
	{
		file = ft_strjoin("/", file);
		while (path[i])
		{
			absolute_path = ft_strjoin(path[i], file);
			if (!access(absolute_path, F_OK))
				return (fill_command(absolute_path));
			free(absolute_path);
			i++;
		}
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char 		*str;
	t_command	*command;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		str = readline("hello$ ");
		command = parse_string(envp, str);
		if (strlen(str) > 0)
			add_history(str);
	}
	return (0);
}