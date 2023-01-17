END=$'\x1b[0m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
BLUE=$'\x1b[34m
ERASE=\033[2K\r

HEADPATH			=	-I containers					\
						-I iterators					\
						-I tree							\
						-I includes


CONTAINERS_DIR		= containers
INCLUDES_DIR		= includes
ITERATORS_DIR		= iterators
TREE_DIR			= tree

SRCS		=	main.cpp								

INCLUDES	=	${CONTAINERS_DIR}/vector.hpp						\
				${CONTAINERS_DIR}/stack.hpp							\
				${CONTAINERS_DIR}/map.hpp							\
																	\
				${INCLUDES_DIR}/distance.hpp						\
				${INCLUDES_DIR}/chooseConst.hpp						\
				${INCLUDES_DIR}/enable_if.hpp						\
				${INCLUDES_DIR}/equal.hpp							\
				${INCLUDES_DIR}/is_integral.hpp						\
				${INCLUDES_DIR}/lexicographical_compare.hpp			\
				${INCLUDES_DIR}/pair.hpp							\
																	\
				${ITERATORS_DIR}/iterator.hpp						\
				${ITERATORS_DIR}/iterator_traits.hpp				\
				${ITERATORS_DIR}/random_access_iterator.hpp			\
				${ITERATORS_DIR}/reverse_random_access_iterator.hpp	\
				${ITERATORS_DIR}/tree_iterator.hpp					\
				${ITERATORS_DIR}/reverse_bidirectional_iterator.hpp	\
																	\
				${TREE_DIR}/Node.hpp								\
				${TREE_DIR}/tree.hpp								\
				main.hpp										

CC					=	c++
FLAGS				=	-std=c++98 -Wall -Wextra -Werror
RM					=	rm -rf

NAME 	=	ft_containers

.PHONY: all
all: $(NAME) run

.PHONY: $(NAME)
$(NAME): 
	@make $(NAME)-ft -s -j4
	@make $(NAME)-std -s -j4

$(NAME)-ft: ${SRCS} ${INCLUDES}
	@$(CC) -D NAMESPACE=1 ${SRCS} ${HEADPATH} -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $@]$(END)"

$(NAME)-std: ${SRCS} ${INCLUDES}
	@$(CC) -D NAMESPACE=0 ${SRCS} ${HEADPATH} -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $@]$(END)"

.PHONY: run
run: $(NAME)
	@./$(NAME)-ft
	@./$(NAME)-std
	@echo "$(ERASE)$(GREEN)[Launching tests ... ]$(END)"
	@diff random_test_ft.txt random_test_std.txt > diff || exit 0
	@if [ -s diff ]; \
    then \
		echo "$(RED)[KO]$(END)"; \
		echo "$(GREEN)To check the diff use: cat diff$(END)";\
		cat diff;\
	else \
		echo "$(GREEN)[OK]$(END)";\
		cat diff;\
		${RM} diff;\
    fi
	@${RM} *.txt diff
	

.PHONY: clean
clean:
	@${RM} .objects
	@echo "${RED}[DELETED]${END} .objects"

.PHONY: fclean
fclean: clean
	@${RM}	$(NAME)-ft
	@echo "${RED}[DELETED]${END} $(NAME)-ft"
	@${RM}	$(NAME)-std
	@echo "${RED}[DELETED]${END} $(NAME)-std"

.PHONY: re
re:			fclean all
