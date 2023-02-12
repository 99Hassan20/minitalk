/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:56 by hoigag            #+#    #+#             */
/*   Updated: 2023/02/12 18:44:55 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	handlesig(int signum, siginfo_t *info, void *ucontext)
{
	static char	character;
	static int	index;
	static int	sender_pid;

	(void)ucontext;
	if (sender_pid != info->si_pid)
	{
		index = 0;
		character = 0;
		sender_pid = info->si_pid;
	}
	if (signum == SIGUSR1)
		index++;
	else
	{
		character |= (1 << index);
		index++;
	}
	if (index == 8)
	{
		write(1, &character, 1);
		index = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handlesig;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("PID : %d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
	}
	return (0);
}
