CC = cc
NAME = minitalk
CFLAGS = -Wall -Werror -Wextra

SERVER = server
CLIENT = client
SRCS = mandatory/ft_atoi.c 

NAME_BONUS = minitalk_bonus
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SRCS_BONUS = bonus/utils.c

all : $(NAME) 

bonus: $(NAME_BONUS)

$(NAME) : $(SERVER) $(CLIENT)
	
$(NAME_BONUS) : $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER) : $(SRCS) mandatory/server.c
	make -C ./libftprintf all
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(CLIENT) : $(SRCS) mandatory/client.c
	make -C ./libftprintf all
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(SERVER_BONUS) : $(SRCS_BONUS) bonus/server_bonus.c
	make -C ./libftprintf all
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(CLIENT_BONUS) : $(SRCS_BONUS) bonus/client_bonus.c
	make -C ./libftprintf all
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

clean:
	make -C ./libftprintf clean

fclean: clean
	make -C ./libftprintf fclean
	rm -f $(SERVER) $(CLIENT)
	rm -f $(SERVER_BONUS) $(CLIENT_BONUS)

re : fclean $(NAME)

.PHONY : all clean fclean re bonus