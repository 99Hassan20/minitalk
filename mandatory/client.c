/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoigag <hoigag@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:53 by hoigag            #+#    #+#             */
/*   Updated: 2023/02/12 18:44:59 by hoigag           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	error_log(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			error_log("the pid should be an int");
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

static void	send_char(char c, int pid)
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

	if (argc != 3)
		error_log("Usage : ./client pid message\npid : process id to send the message to\
\nmessage : the text to send");
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		error_log("0 signal and negative signals are not acceptable");
	if (!(kill(pid, 0) == 0))
		error_log("invalid pid");
	message = argv[2];
	i = 0;
	while (message[i])
	{
		send_char(message[i], pid);
		i++;
	}
	return (0);
}
