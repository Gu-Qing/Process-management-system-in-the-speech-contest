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
		cout << "����������ѡ��" << endl;
		cin >> select;
		switch (select) {
		case 1: //��ʼ����
			speechManager.StartSpeech();
			break;
		case 2: //�鿴�����¼
			speechManager.ShowRecord();
			break;
		case 3: //��ձ�����¼
			speechManager.ClearRecord();
			break;
		case 0: //�˳�
			speechManager.ExitSystem();
		default:
			cout << "�������ִ������������룡" << endl;
		}
	}

	system("pause");

	return 0;
}