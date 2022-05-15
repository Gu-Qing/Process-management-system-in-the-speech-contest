#include <iostream>
#include <algorithm>
#include <vector>
#include "SpeechManager.h"

using namespace std;

void Test(map<int, Speaker> &m) {
	for (map<int, Speaker>::iterator it = m.begin(); it != m.end(); it++) {
		cout << "No." << it->first << " Name: " << it->second.getName() << " Score: " << it->second.getScore(0) << endl;
	}
}

int main() {

	srand((unsigned int)time(0));

	SpeechManager speechManager;
	map<int, Speaker> mm = speechManager.getSpeakerMap();

	while (1) {
		speechManager.ShowMenu();
		//Test(mm);
		int select;
		cout << "请输入您的选择：" << endl;
		cin >> select;
		switch (select) {
		case 1: //开始比赛
			speechManager.StartSpeech();
			break;
		case 2: //查看往届记录
			speechManager.ShowRecord();
			break;
		case 3: //清空比赛记录
			speechManager.ClearRecord();
			break;
		case 0: //退出
			speechManager.ExitSystem();
		default:
			cout << "输入数字错误，请重新输入！" << endl;
		}
	}

	system("pause");

	return 0;
}