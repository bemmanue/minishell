#include <minishell.h>

static int	child(t_command *commands, int fd_out)
{
	int	temp;
	int	pid;

	pid = 0;
	if (fd_out != STD_VAL)
		dup2(fd_out, STDOUT_FILENO);
	else
		dup2(g_info.std_fd[1], STDOUT_FILENO);
	temp = chk_builtin(commands, NULL);
	if (temp == NONBLTN)
	{
		pid = fork();
		if (pid)
			return (pid);
		g_info.last_prcs = execve(commands->name, commands->argv, g_info.env);
		error(commands->name, 0);
	}
	else
		g_info.last_prcs = temp;
	return (pid);
}

static int	pipeline(t_command *commands, char **doc)
{
	pid_t	pid;
	int		fd_redir[2];
	int		status;

	redirect(commands->rdrct, fd_redir, &doc);
	if (check_fd_ret(fd_redir, NULL, &doc))
		return (-1);
	pid = child(commands, fd_redir[1]);
	if (pid < 0)
		return (-1);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_info.last_prcs = WEXITSTATUS(status);
	}
	return (pid);
}

int	last_fork(t_command *commands)
{
	int		pid;

	pid = pipeline(commands, NULL);
	if (pid < 0)
		return (-1);
	return (0);
}
