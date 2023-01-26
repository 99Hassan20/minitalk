/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:53 by hoigag            #+#    #+#             */
/*   Updated: 2023/01/26 12:43:57 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	check_is_valid_pid(int pid)
{
	return (kill(pid, 0) == 0);
}

void	sighandler(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("signal received successfully\n");
}

void	send_char(char c, int pid)
{
	int		i;
	char	bit;
	int		status;

	i = 0;
	while (i < 8)
	{
		bit = (c >> i) & 1;
		if (bit == 0)
			status = kill(pid, SIGUSR1);
		else
			status = kill(pid, SIGUSR2);
		if (status == -1)
			error_log("Could not send the signal");
		usleep(200);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;
	int		i;

	signal(SIGUSR1, &sighandler);
	if (argc != 3)
		error_log("Usage : ./client pid message\npid : process id to send the message to\
\nmessage : the text to send");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		error_log("0 signal and non negative signals are not acceptable");
	if (!check_is_valid_pid(pid))
		error_log("invalid pid");
	message = argv[2];
	i = 0;
	while (message[i])
	{
		send_char(message[i], pid);
		i++;
	}
	send_char(message[i], pid);
	return (0);
}
