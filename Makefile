CC = cc
NAME = minitalk
CFLAGS = -Wall -Werror -Wextra

SERVER = server
CLIENT = client

NAME_BONUS = minitalk_bonus
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SRCS_BONUS = bonus/utils.c

all : ftprintf $(NAME) 

bonus: ftprintf $(NAME_BONUS)

ftprintf:
	make -C ./printf all

$(NAME) : $(SERVER) $(CLIENT)
	
	
$(NAME_BONUS) : $(SERVER_BONUS) $(CLIENT_BONUS)


$(SERVER) : mandatory/server.c
	$(CC) $(CFLAGS) $^ -L./printf -lftprintf -o $@

$(CLIENT) : mandatory/client.c
	$(CC) $(CFLAGS) $^ -L./printf -lftprintf -o $@

$(SERVER_BONUS) : $(SRCS_BONUS) bonus/server_bonus.c
	$(CC) $(CFLAGS) $^ -L./printf -lftprintf -o $@

$(CLIENT_BONUS) : $(SRCS_BONUS) bonus/client_bonus.c
	$(CC) $(CFLAGS) $^ -L./printf -lftprintf -o $@

clean:
	make -C ./printf clean

fclean: clean
	make -C ./printf fclean
	rm -f $(SERVER) $(CLIENT)
	rm -f $(SERVER_BONUS) $(CLIENT_BONUS)

re : fclean $(NAME)

.PHONY : all clean fclean re bonus