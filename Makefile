NAME = webserv

CPP = c++
#FLAGS = -Wall -Werror -Wextra -g
STD = -std=c++98

SRC_PATH = src/

SRCS = main.cpp WebServer.cpp Server.cpp Request.cpp Socket.cpp Responce.cpp


OBJS = $(addprefix $(SRC_PATH), $(SRCS:.cpp=.o))

HDRS = $(wildcard $(SRC_PATH)*.hpp)

$(SRC_PATH)%.o: $(SRC_PATH)%.cpp $(HDRS)
	@$(CPP) $(FLAGS) $(STD) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) $(STD) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all