##
## Makefile for Zappy in /home/lamart_m/rendu/PSU_2014_zappy
## 
## Made by Maxime Lamarthe
## Login   <lamart_m@epitech.net>
## 
## Started on  Mon Jun  8 11:05:07 2015 Maxime Lamarthe
## Last update Fri Jul  3 10:53:13 2015 Maxime Lamarthe
##

all: client
	@(cd Sources/Serveur && $(MAKE) $@)

serveur:
	@(cd Sources/Serveur && $(MAKE))

client:
	ln -sf Sources/Client/Client.php zappy_ai
clean:
	@(cd Sources/Serveur && $(MAKE) $@)

fclean_client:
	rm -f ./zappy_ai

fclean: fclean_client
	@(cd Sources/Serveur && $(MAKE) $@)

re: fclean_client client
	@(cd Sources/Serveur && $(MAKE) $@)
