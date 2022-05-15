#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>
#include "Speaker.h"

using namespace std;

#define FILENAME "speech.csv"

class SpeechManager {
private:
	vector<int> v1; //比赛选手容器 12人
	vector<int> v2; //晋级容器 6人
	vector<int> vVictory; //胜出的前三名
	//存放编号以及对应具体选手的容器
	map<int, Speaker> m_Speaker;
	int m_Index; //记录比赛轮数
	bool fileIsEmpty; //判断文件是否为空
	map<int, vector<string>> m_Record; //存放往届记录的容器

	//重置比赛和比赛记录
	void Init();
	//初始化容器和属性
	void InitSpeech();
	//创建选手
	void CreateSpeaker();
	//输出vector中每一轮的人的编号
	void MyPrintVector(const vector<int> &v);
	//抽签
	void SpeechDraw();
	//比赛
	void SpeechContest();
	//显示得分
	void ShowScore(); 
	//保存分数到表格
	void SaveRecord();
	//读取记录分数
	void LoadRecord();

public :
	//构造函数
	SpeechManager();

	vector<int> getVecotor1() const;
	void setVector1(vector<int>& v);
	vector<int> getVector2() const;
	void setVector2(vector<int>& v);
	vector<int> getVictory() const;
	void setVictory(vector<int>& v);
	map<int, Speaker> getSpeakerMap() const;
	void setSpeakerMap(map<int, Speaker> &m);
	int getIndex() const;
	void setIndex(int index);
	bool getFileIsEmpty() const;
	void setFileIsEmpty(bool flag);
	map<int, vector<string>> getRecord() const;
	void setRecord(map<int, vector<string>>& m);

	//菜单功能
	void ShowMenu();
	//退出功能
	void ExitSystem();
	//开始比赛
	void StartSpeech();
	//显示往届记录
	void ShowRecord();
	//清空往届记录
	void ClearRecord();
	//析构函数
	~SpeechManager();

};