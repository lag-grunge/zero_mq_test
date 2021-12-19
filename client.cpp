#include <iostream>
#include <fstream>
#include <zmq.hpp>
#include <zmq.h>
#include "zhelpers.hpp"
#include <string>
#include "student.hpp"

int main() {
	std::vector<Student> vs = {};
	void *context = zmq_ctx_new();
	zmq_ctx_set (context, ZMQ_IO_THREADS, 2);
	void *socket = zmq_socket(context, ZMQ_SUB);
	assert (socket);
	int rc = zmq_connect(socket, "tcp://localhost:5563");
	assert(rc == 0);
	zmq_setsockopt(socket, ZMQ_SUBSCRIBE, NULL, 0);

	for	(;;)
	{
		std::string s;
		char 		*buf;

		buf = s_recv(socket, 0);
		if (!buf)
		{
			std::cout << "Recieve failed" << std::endl;
			return (1);
		}
		s = std::string(buf);
		if (s == "eof")
			break ;
		addstudent(vs, s);
	}
	sortstudent(vs, ascending);
	for (Student &st : vs)
		st.printline();
	return 0;
}
