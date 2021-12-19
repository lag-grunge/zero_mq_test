#include <iostream>
#include <fstream>
#include <zmq.h>
#include <zmq.hpp>
#include "zhelpers.hpp"
#include <string>
#include <unistd.h>
#include "student.hpp"

void union_students(const char *outfile)
{
	std::ifstream			file1("student_file_1.txt");
	std::ifstream 			file2("student_file_2.txt");
	std::ofstream 			ofile(outfile);
	std::vector<Student>	vs = {};

	if (!file1.is_open())
		std::cout << "student_file_1.txt" << " failed to open!" << "\n";
	if (!file2.is_open())
		std::cout << "student_file_2.txt" << " failed to open!" << "\n";
	if (!ofile.is_open())
		std::cout << outfile << " failed to open!" << "\n";
	for (std::string s; std::getline(file1, s); )
		addstudent(vs, s);
	file1.close();
	for (std::string s; std::getline(file2, s); )
		addstudent(vs, s);
	file2.close();
	for (Student &st : vs)
		st.fprintline(ofile);
	ofile.close();
}

int main() {
	void *context = zmq_ctx_new();
	zmq_ctx_set (context, ZMQ_IO_THREADS, 2);
	void *socket = zmq_socket(context, ZMQ_PUB);
	assert (socket);
	int rc = zmq_bind(socket, "tcp://*:5563");
	assert(rc == 0);

	union_students("../students_join_file.txt");
	std::ifstream fstudents("../students_join_file.txt");
	std::string 	s;
	const char *c;

	sleep(5);
	for	(; std::getline(fstudents, s); )
	{
		c = s.c_str();
		s_send(socket, c, 0) ;
		sleep(1);
	}
	s = "eof";
	c = s.c_str();
	s_send(socket, c, 0);
	return 0;
}
