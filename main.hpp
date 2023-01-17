#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <map>
#include <vector>
#include <stack>

#include "containers/map.hpp"
#include "containers/vector.hpp"
#include "containers/stack.hpp"

#ifndef NAMESPACE
# define NAMESPACE 0
#endif

#if NAMESPACE==0
	#define FILE_NAME "_std"
	#define CURRENT_NAMESPACE std
#else
	#define FILE_NAME "_ft"
	#define CURRENT_NAMESPACE ft
#endif

namespace std {

	template <class T, class U>
	std::string to_string(const CURRENT_NAMESPACE::map<T, U>& m) {
		std::string str;
		typename CURRENT_NAMESPACE::map<T, U>::const_iterator it;
		for (it = m.begin(); it != m.end(); ++it)
		{
			str += std::to_string(it->first);
			str += ":";
			str += std::to_string(it->second);
			str += "\n";
		}
		return str;
	}

	template <typename T, typename C>
	std::string to_string(CURRENT_NAMESPACE::stack<T, C> stack) {
		std::string str;
		while (stack.empty() == false)
		{
			str += std::to_string(stack.pop());
			stack.pop();
		}
		return str;
	}

	template <typename T>
	std::string to_string(const CURRENT_NAMESPACE::vector<T>& v) {
		std::string str;
		for (int i = 0; i < v.size(); i++)
			str += std::to_string(v[i]);
		return str;
	}

	template <typename U, typename T>
	std::string to_string(const CURRENT_NAMESPACE::pair<U, T>& p) {
		return (std::string(std::to_string(p.first) + " " + std::to_string(p.second)));
	}
	
}

template <typename T>
void write_result(std::ofstream& ofs, const T& val)
{
	ofs << std::to_string(val) << std::endl;
}

template <typename T>
void write_result(std::ofstream& ofs, const CURRENT_NAMESPACE::vector<T>& vector, const bool printContent=true) {
	ofs << "size: " + std::to_string(vector.size()) << std::endl;
	ofs << "capacity: " + std::to_string(vector.capacity()) << std::endl;
	ofs << "empty: " + std::to_string(vector.empty()) << std::endl;
	if (printContent)
		for (int i = 0; i < vector.size(); i++)
			ofs << std::to_string(vector[i]) << std::endl;
}

template <typename T, typename C>
void write_result(std::ofstream& ofs, CURRENT_NAMESPACE::stack<T, C> stack, const bool printContent=true) {
	ofs << "size: " + std::to_string(stack.size()) << std::endl;
	ofs << "empty: " + std::to_string(stack.empty()) << std::endl;
	if (printContent)
		while (stack.empty() == false)
		{
			ofs << std::to_string(stack.top()) << std::endl;
			stack.pop();
		}
}
template <class T, class U>

void write_result(std::ofstream& ofs, const CURRENT_NAMESPACE::map<T, U>& map, const bool printContent=true) {
	ofs << "size: " + std::to_string(map.size()) << std::endl;
	ofs << "empty: " + std::to_string(map.empty()) << std::endl;
	if (printContent)
		ofs << std::to_string(map);
}



