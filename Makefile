CC = cc
NAME = minitalk
CFLAGS = -Wall -Werror -Wextra

SERVER = server
CLIENT = client

NAME_BONUS = minitalk_bonus
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SRCS_BONUS = bonus/utils.c

all : printf $(NAME) 

bonus: printf $(NAME_BONUS)

printf:
	make -C ./libftprintf all

$(NAME) : $(SERVER) $(CLIENT)
	
	
$(NAME_BONUS) : $(SERVER_BONUS) $(CLIENT_BONUS)


$(SERVER) : mandatory/server.c
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(CLIENT) : mandatory/client.c
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(SERVER_BONUS) : $(SRCS_BONUS) bonus/server_bonus.c
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

$(CLIENT_BONUS) : $(SRCS_BONUS) bonus/client_bonus.c
	$(CC) $(CFLAGS) $^ -L./libftprintf -lftprintf -o $@

clean:
	make -C ./libftprintf clean

fclean: clean
	make -C ./libftprintf fclean
	rm -f $(SERVER) $(CLIENT)
	rm -f $(SERVER_BONUS) $(CLIENT_BONUS)

re : fclean $(NAME)

.PHONY : all clean fclean re bonus