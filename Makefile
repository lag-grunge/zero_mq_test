NAME = server
NAME2 = client

CFLAGS = 

all : ${NAME} ${NAME2}

${NAME} : server.cpp student.hpp zhelpers.hpp
	g++ -o $@ $< -lzmq -I.

${NAME2} : client.cpp student.hpp zhelpers.hpp
	g++ -o $@ $< -lzmq -I.

clean :
	${RM} ${NAME} ${NAME2}

re:	clean all

.PHONY: all clean re

