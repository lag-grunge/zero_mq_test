#ifndef TEST_ZERO_MQ_HTTP_STUDENT_HPP
#define TEST_ZERO_MQ_HTTP_STUDENT_HPP

class Student
{
private:
	int m_num;
	std::string m_name;
	std::string m_name2;
	std::string m_birth_date;
public:
	Student() {}
	Student(std::string s) {
		std::stringstream ss(s);
		ss >> m_num;
		ss >> m_name;
		ss >> m_name2;
		ss >> m_birth_date;
	}
	void fprintline(std::ofstream &f)
	{
		f << m_num << " " << m_name << " " << m_name2 << " " << m_birth_date << "\n";
	}
	void printline()
	{
		std::cout << m_num << " " << m_name << " " << m_name2 << " " << m_birth_date << "\n";
	}

	friend bool operator==(const Student &st1, const Student &st2);
	friend bool operator<(const Student &st1, const Student &st2);
};

bool operator==(const Student &st1, const Student &st2)
{
	return ((st1.m_name == st2.m_name) and (st1.m_name2 == st2.m_name2) and (st1.m_birth_date == st2.m_birth_date));
}

bool operator<(const Student &st1, const Student &st2)
{
	if (st1.m_name2 < st2.m_name2)
		return (true);
	else if ((st1.m_name2 == st2.m_name2) and (st1.m_name < st2.m_name))
		return (true);
	return (false);
}

void addstudent(std::vector<Student> &vs, std::string &s)
{
	Student cur = Student(s);

	for (Student &st : vs)
	{
		if (cur == st)
			return ;
	}
	vs.push_back(cur);
}

bool ascending(Student &st1, Student &st2)
{
	if (st1 < st2)
		return (true);
	return (false);
}

void swapstudents(std::vector<Student> &vs, int i, int j)
{
	Student	tmp;

	if (i == j)
		return;
	tmp = vs.at(j);
	vs.at(j) = vs.at(i);
	vs.at(i) = tmp;
}

void sortstudent(std::vector<Student> &vs, bool (*Cmpr)(Student &st1, Student &st2))
{
	int n = vs.size();

	for (int i = 0, sw = 0; i < n - 1; i++, sw = i)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (Cmpr(vs.at(j), vs.at(sw)))
				sw = j;
		}
		swapstudents(vs, i, sw);
	}
}

#endif
