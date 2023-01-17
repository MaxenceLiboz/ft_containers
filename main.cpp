#include "main.hpp"

void open_file(std::ofstream& ofs, const std::string& name)
{
	std::string file_name;
	file_name += name;
	file_name += FILE_NAME;
	file_name += ".txt";
	ofs.open(file_name);

	if (!ofs.is_open())
		exit (1);
}

int main(void)
{
	std::ofstream ofs;
	open_file(ofs, "random_test");

    { // Test basic functions
		CURRENT_NAMESPACE::vector<float> v;
		
		for (int i = 0; i < 15; i++)
		{
			v.insert(v.end(), i);
		}
		write_result(ofs, v);

		v.insert(v.begin(), v.begin(), v.end());
		write_result(ofs, v);
		write_result(ofs, v[5]);
		write_result(ofs, v.at(5));

		CURRENT_NAMESPACE::vector<float>::iterator it = v.erase(v.end() - 1);
        if (it == v.end()) {
			ofs << "END" << std::endl;
        }
		write_result(ofs, v);
		
		v.clear();
		write_result(ofs, v);

		v.clear();
		write_result(ofs, v);

		v.clear();
		write_result(ofs, v);

		v.insert(v.end(), 42.42);
		write_result(ofs, v);
	}
	{ // Test pop_back

		CURRENT_NAMESPACE::vector<int> v;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}	
		write_result(ofs, v);

		v.pop_back();
		write_result(ofs, v);

		for (int i = 0; i < 4; i++)
		{
			v.pop_back();
		}
		write_result(ofs, v);

        for (CURRENT_NAMESPACE::vector<int>::const_reverse_iterator crit = v.rbegin(); crit != v.rend(); ++crit) {
            write_result(ofs, *crit);
        }
	}
	{ // Test basic functions

		CURRENT_NAMESPACE::vector<int> v;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}	
		write_result(ofs, v);

		CURRENT_NAMESPACE::vector<int>::iterator it = v.insert(v.begin(), 123);
		write_result(ofs, *it);
		write_result(ofs, v.front());
		write_result(ofs, v.back());
		write_result(ofs, v.empty() == true);
		
		v.clear();
		write_result(ofs, v);

		v.resize(50, 2);
		write_result(ofs, v);

		v.assign(11, 4);
		write_result(ofs, v);

		v.erase(v.begin(), v.begin() + 10);
		write_result(ofs, v);

		v.assign(v.begin() + 2, v.begin() + 6);
		write_result(ofs, v);
	}
	{ // Test comparisons

		CURRENT_NAMESPACE::vector<double> v;
		CURRENT_NAMESPACE::vector<double> v1;

		v.assign(10, 421);
		write_result(ofs, v == v1);
		write_result(ofs, v != v1);
		write_result(ofs, v > v1);
		write_result(ofs, v < v1);
		write_result(ofs, v >= v1);
		write_result(ofs, v <= v1);
	}
	{// Test exception for at
		CURRENT_NAMESPACE::vector<double> v;

		v.assign(10, 333);

		try {
			try {
				write_result(ofs, v.at(24));
			} catch (std::out_of_range &e) {
				ofs << "OUT OF RANGE" << std::endl;
			}
		} catch (...) {
			ofs << "UNHANDLED EXCEPTION" << std::endl;
		}

	}

	CURRENT_NAMESPACE::map<double, double> m;
	for (int i = 0; i < 20; i++) {
		m.insert(CURRENT_NAMESPACE::make_pair(i, i));
	}

	{ //Insert and erase
		CURRENT_NAMESPACE::map<double, double>    map(m);
		map.erase(map.begin(), map.end());
		write_result(ofs, map);
		for (int i = 0; i < 20; i++) {
			map.insert(CURRENT_NAMESPACE::make_pair(i, i));
		}
		write_result(ofs, map);
		map.insert(map.end(), CURRENT_NAMESPACE::make_pair(5235235, 21));
		write_result(ofs, map);
		map.erase(map.begin(), map.end());
		write_result(ofs, map);
	}
	{ // iterator tests
		CURRENT_NAMESPACE::map<double, double>    map(m);
		CURRENT_NAMESPACE::map<double, double>::iterator it = map.begin();


		if (it == map.end()) ofs << "END" << std::endl;
		else write_result(ofs, *it);

		it = map.find(10);
		if (it == map.end()) ofs << "END" << std::endl;
		else write_result(ofs, *it);

		it = map.insert(it, CURRENT_NAMESPACE::make_pair(10, 10));
		if (it == map.end()) ofs << "END" << std::endl;
		else write_result(ofs, *it);

		it = map.lower_bound(10);
		if (it == map.end()) ofs << "END" << std::endl;
		else write_result(ofs, *it);

		it = map.upper_bound(10);
		if (it == map.end()) ofs << "END" << std::endl;
		else write_result(ofs, *it);
	}
	{ //modifier tests
		CURRENT_NAMESPACE::map<double, double>    map(m);
		CURRENT_NAMESPACE::map<double, double>    map1(m);

		map.swap(map1);
		write_result(ofs, map);
		write_result(ofs, map1);
		map.insert(map1.begin(), map1.end());
		map.swap(map1);
		map.erase(map.begin(), map.end());
		write_result(ofs, map);
		map.swap(map1);
		write_result(ofs, map1);
		write_result(ofs, map);
		map.clear();
		write_result(ofs, map);
	}
}
