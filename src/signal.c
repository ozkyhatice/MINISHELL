#include "../include/minishell.h"

// void	ft_sigint(int sig)
// {
// 	(void)sig;
// 	if (g_signal == IN_HEREDOC)
// 	{
// 		write(1, "\033[A", 3);
// 		ioctl(0, TIOCSTI, "\n");
// 		g_signal = AFTER_HEREDOC;
// 	}
// 	else if (g_signal == IN_CMD)
// 	{
// 		rl_on_new_line();
// 		write(1, "\n", 1);
// 		g_signal = AFTER_CMD;
// 	}
// 	else
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

void	ft_init_signals(void)
{
	//signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
}