##
## Makefile for pamela in /home/costa_d/Documents/TEK3/pamela
## 
## Made by Arnaud Costa
## Login   <costa_d@epitech.net>
## 
## Started on  Wed Nov 22 13:50:18 2017 Arnaud Costa
## Last update Wed Nov 22 14:49:32 2017 Arnaud Costa
##

NAME	    =	libpamela.so

CC	        =	gcc

RM	        =	rm -rf

MK	        =	mkdir

CP          =   cp

SRC	    =   entryPoints.c		\
                userManager.c       	\
                tools.c             	\
                directoryManager.c  	\
                luksTools.c		\
		mountManager.c		\

SRC_TEST   =    src/tools.c             	\
                src/directoryManager.c  	\
                src/luksTools.c			\
		src/main.c


OBJDIR     	=	obj/

SRCDIR     	=   src/

OBJ	   	    =	$(addprefix $(OBJDIR), $(SRC:.c=.o))

CFLAGS		=	-Iinclude

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -shared -lcryptsetup -o $(NAME) $(OBJ)

$(OBJDIR)%.o:   $(SRCDIR)%.c
		@$(MK) -p $(OBJDIR)
		$(CC) -fPIC $(CFLAGS) -c $< -o $@

install:
	@echo -n "Installing libpamela.so\n"
	@$(CP) $(NAME) /lib/x86_64-linux-gnu/security
	@grep $(NAME) /etc/pam.d/common-auth || echo -n "auth\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-auth"
	@grep $(NAME) /etc/pam.d/common-password || echo -n "password\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-password"
	@grep $(NAME) /etc/pam.d/common-session || echo -n "session\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-session"


uninstall:
	@echo -n "Uninstalling libpamela.so\n"
	@$(RM) /lib/x86_64-linux-gnu/security/$(NAME)
	@$(RM) /root/.pamela_containers
	sed -i /'$(NAME)/d' /etc/pam.d/common-auth
	sed -i /'$(NAME)/d' /etc/pam.d/common-password
	sed -i /'$(NAME)/d' /etc/pam.d/common-session

check:
	@echo -n "Check libpamela.so\n"
	@$(CP) $(NAME) /lib/x86_64-linux-gnu/security
	@grep $(NAME) /etc/pam.d/common-auth || echo -n "auth\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-auth"
	@grep $(NAME) /etc/pam.d/common-password || echo -n "password\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-password"
	@grep $(NAME) /etc/pam.d/common-session || echo -n "session\toptional\t\t$(NAME)\n" >> "/etc/pam.d/common-session"

test:
	$(CC) $(SRC_TEST) -o test -Iinclude -lcryptsetup

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)
	$(RM) $(NAME)

re:		clean all

.PHONY:		all install uninstall check clean re
