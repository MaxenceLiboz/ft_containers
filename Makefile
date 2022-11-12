END=$'\x1b[0m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
BLUE=$'\x1b[34m
ERASE=\033[2K\r
export END
export RED
export GREEN
export BLUE
export ERASE

HEADPATH			=	-I containers					\
						-I iterators					\
						-I tests/own					\
						-I tests/own/vector				\
						-I includes
export HEADPATH


CONTAINERS_DIR		= containers
INCLUDES_DIR		= includes
ITERATORS_DIR		= iterators
TESTS_DIR			= tests
VECTOR_TESTS_DIR 	= ${TESTS_DIR}/vector

SRCS		=	main.cpp								\
				${VECTOR_TESTS_DIR}/constructors.cpp	\
				${VECTOR_TESTS_DIR}/operator_equal.cpp	\
				${VECTOR_TESTS_DIR}/assign.cpp

INCLUDES	=	${CONTAINERS_DIR}/vector.hpp					\
				${INCLUDES_DIR}/enable_if.hpp					\
				${INCLUDES_DIR}/equal.hpp						\
				${INCLUDES_DIR}/is_integral.hpp					\
				${INCLUDES_DIR}/lexicographical_compare.hpp		\
				${INCLUDES_DIR}/pair.hpp						\
				${ITERATORS_DIR}/iterator.hpp					\
				${ITERATORS_DIR}/iterator_traits.hpp			\
				${ITERATORS_DIR}/random_access_iterator.hpp		\
				${ITERATORS_DIR}/reverse_iterator_vector.hpp	\
				${TESTS_DIR}/main.hpp							\
				${VECTOR_TESTS_DIR}/vector_prelude.hpp	

CC					=	c++
FLAGS				=	-std=c++98 -Wall -Wextra -Werror -MD
RM					=	rm -rf
export CC
export FLAGS
export RM

NAME 	=	ft_containers

.PHONY: all
all: $(NAME) run

.PHONY: $(NAME)
$(NAME): 
	@make $(NAME)-ft -s -j4
	@make $(NAME)-std -s -j4

$(NAME)-ft: ${SRCS} ${INCLUDES}
	@$(CC) -D NP=ft -D FT=1 ${SRCS} ${HEADPATH} -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $@]$(END)"

$(NAME)-std: ${SRCS} ${INCLUDES}
	@$(CC) -D NP=std -D FT=0 ${SRCS} ${HEADPATH} -o $@
	@echo "$(ERASE)$(GREEN)[CREATED $@]$(END)"

.PHONY: run
run: $(NAME)
	@./$(NAME)-ft > out
	@./$(NAME)-std > out1
	@diff out out1 > diff; \
	if [ $$? -ne 0 ]; \
    then \
		echo "$(RED)[KO]$(END)"; \
		echo "$(GREEN)Check the diff: cat ./diff$(END)";\
	else \
		echo "$(GREEN)[OK]$(END)";\
		${RM} diff;\
    fi

	@${RM} out out1
	

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
