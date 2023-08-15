NAME = webserv

CPP = c++
#FLAGS = -Wall -Werror -Wextra -g
STD = -std=c++98

SRC_PATH = src/

<<<<<<< HEAD
SRCS = main.cpp WebServer.cpp Server.cpp Request.cpp Socket.cpp 
=======
SRCS = main.cpp Socket.cpp Server.cpp Request.cpp Response.cpp
>>>>>>> f6c5c02f513c1401bd19068fcdfbb819d3104672

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