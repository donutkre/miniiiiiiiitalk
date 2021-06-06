SERVER=server
CLIENT=client 

all: server client

server:
	gcc server.c  -o $(SERVER)

client:
	gcc client.c  -o $(CLIENT)

clean: 
	rm $(SERVER) $(CLIENT)

fclean: clean

re: clean all

BONUS_SERVER=server_bonus
BONUS_CLIENT=client_bonus

bonus: b_server b_client

b_server:
	gcc server_bonus.c -o $(BONUS_SERVER)

b_client:
	gcc client_bonus.c -o $(BONUS_CLIENT)

b_clean: 
	rm $(BONUS_SERVER) $(BONUS_CLIENT)

b_fclean: b_clean

b_re: bonus