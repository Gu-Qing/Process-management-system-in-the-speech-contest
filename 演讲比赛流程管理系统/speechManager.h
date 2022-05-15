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
	vector<int> v1; //����ѡ������ 12��
	vector<int> v2; //�������� 6��
	vector<int> vVictory; //ʤ����ǰ����
	//��ű���Լ���Ӧ����ѡ�ֵ�����
	map<int, Speaker> m_Speaker;
	int m_Index; //��¼��������
	bool fileIsEmpty; //�ж��ļ��Ƿ�Ϊ��
	map<int, vector<string>> m_Record; //��������¼������

	//���ñ����ͱ�����¼
	void Init();
	//��ʼ������������
	void InitSpeech();
	//����ѡ��
	void CreateSpeaker();
	//���vector��ÿһ�ֵ��˵ı��
	void MyPrintVector(const vector<int> &v);
	//��ǩ
	void SpeechDraw();
	//����
	void SpeechContest();
	//��ʾ�÷�
	void ShowScore(); 
	//������������
	void SaveRecord();
	//��ȡ��¼����
	void LoadRecord();

public :
	//���캯��
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

	//�˵�����
	void ShowMenu();
	//�˳�����
	void ExitSystem();
	//��ʼ����
	void StartSpeech();
	//��ʾ�����¼
	void ShowRecord();
	//��������¼
	void ClearRecord();
	//��������
	~SpeechManager();

};