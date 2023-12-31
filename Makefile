# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfai <lfai@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 18:55:31 by lfai              #+#    #+#              #
#    Updated: 2023/08/07 17:21:17 by lfai             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PURPLE			= \033[38;5;141m
GREEN			= \033[38;5;46m
RED				= \033[0;31m
GREY			= \033[38;5;240m
RESET			= \033[0m
BOLD			= \033[1m
CLEAR			= \r\033[K

NAME			= philosophers

SRC_DIR			= src/

SRCS			= main.c monitoring.c utils.c init.c philo_utils.c

OBJ_DIR			= ./objs/
OBJS			= ${addprefix ${OBJ_DIR}, ${SRCS:.c=.o}}

CC				= gcc
CFLAGS			= -g -Wall -Wextra -Werror -pthread -I ./include/
RM				= rm -rf

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Compiling ${GREEN}%s${RESET}...${GREY}" ${notdir $<}
	@${CC} ${CFLAGS} -I${SRC_DIR} -c $< -o $@

all: 			$(NAME)

$(NAME): 		$(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "${CLEAR}${RESET}${GREY}──────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: ${RED}${BOLD}${NAME} ${RESET}compiled ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

${OBJS}:		| ${OBJ_DIR}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}


clean:
	@${RM} ${OBJ_DIR}
	@printf "${CLEAR}${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Objects cleaned ${GREEN}successfully${RESET}.\n${RESET}"

fclean: 		clean
	@${RM} ${NAME}
	@printf "${CLEAR}${RESET}${GREY}──────────────────────────────────────────\n${RESET}${GREEN}»${RESET} [${PURPLE}${BOLD}${NAME}${RESET}]: Project cleaned ${GREEN}successfully${RESET}.${GREY}\n${RESET}${GREY}────────────────────────────────────────────────────────────────────────────\n${RESET}"

re: fclean all

.SILENT: all clean fclean re
.PHONY: all clean fclean re
