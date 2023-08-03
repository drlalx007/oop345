//Name: Daryl Alex
//Student ID: 143691202
//Email: dalex4@myseneca.ca
//Subject Code: ZAA
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include<string>
using namespace std;
#include "ProteinDatabase.h"
namespace sdds {
	ProteinDatabase::ProteinDatabase(){
        s_length = 0;
		arr = nullptr;
	}
	ProteinDatabase::ProteinDatabase(char* filename){
		ifstream f(filename);
        s_length = 0;
		arr = nullptr;
		if (!f)
			return;
		std::string line, name;
		while (std::getline(f,line).good()){
			if (line[0] == '>'){
                s_length++;
			}
		}
		f.clear();
		f.seekg(std::ios::beg);
		arr = new string[s_length];
		line.clear();
		int i = -1;
		while (getline(f,line).good()){
			if (line[0] == '>'){
				++i;
				name = line.substr(1);

			}
			else if (!name.empty()){
				arr[i] += line;
			}
		}
	}
	ProteinDatabase::ProteinDatabase(const ProteinDatabase& old){
        *this = old;
	}
    ProteinDatabase::~ProteinDatabase(){
        delete[] arr;
    }
    size_t ProteinDatabase::size(){
        return s_length;
    }
    std::string ProteinDatabase::operator[](size_t index){
        if (index < s_length)
            return arr[index];
        return "";
    }
    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src){
        if (this != &src) {
            delete[] arr;
            s_length = src.s_length;
            arr = new string[s_length]{};
            for (unsigned int i = 0; i < s_length; i++) {
                arr[i] = src.arr[i];
            }
        }
        return *this;
    }
	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src)
	{
		if (this != &src)
		{
			delete[] arr;
			arr = src.arr;

			src.arr = nullptr;
            s_length = src.s_length;

			src.s_length = 0;
		}
		return *this;
	}
	ProteinDatabase::ProteinDatabase(ProteinDatabase&& old)
	{
		*this = std::move(old);

	}
}