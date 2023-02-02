/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/02/02 16:53:34 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

static void	reset_vars(int *index, char *character)
{
	*index = 0;
	*character = 0;
}

static void	send_back(int pid, int signum)
{
	int	status;

	status = kill(pid, signum);
	if (status == -1)
		error_log("Could not send the signal");
}

static void	handlesig(int signum, siginfo_t *info, void *ucontext)
{
	static char	character;
	static int	index;
	static int	sender_pid;

	(void)ucontext;
	if (sender_pid != info->si_pid)
	{
		reset_vars(&index, &character);
		sender_pid = info->si_pid;
	}
	if (signum == SIGUSR2)
	{
		character |= (1 << index);
		index++;
	}
	else
		index++;
	if (index == 8)
	{
		if (character == '\0')
			send_back(info->si_pid, SIGUSR1);
		write(1, &character, 1);
		reset_vars(&index, &character);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handlesig;
	sa.sa_flags = SA_RESTART;
	ft_printf(" PID : %d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
	}
	return (0);
}
