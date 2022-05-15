#pragma once

#include <iostream>
using namespace std;

class Speaker {
private:
	string m_Name;
	double m_Score[2]; //有两轮分数

public :
	string getName() const{
		return this->m_Name;
	}
	void setName(string name) {
		this->m_Name = name;
	}
	double getScore(int ind){
		return this->m_Score[ind];
	}
	void setScore(double score, int ind) {
		this->m_Score[ind] = score;
	}
};