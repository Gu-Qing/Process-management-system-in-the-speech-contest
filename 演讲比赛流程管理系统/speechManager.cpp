#include "SpeechManager.h"

SpeechManager::SpeechManager() {
	this->Init();
}

vector<int> SpeechManager::getVecotor1() const {
	return this->v1;
}
void SpeechManager::setVector1(vector<int>& v) {
	this->v1 = v;
}
vector<int> SpeechManager::getVector2() const {
	return this->v2;
}
void SpeechManager::setVector2(vector<int>& v) {
	this->v2 = v;
}
vector<int> SpeechManager::getVictory() const {
	return this->vVictory;
}
void SpeechManager::setVictory(vector<int>& v) {
	this->vVictory = v;
}
map<int, Speaker> SpeechManager::getSpeakerMap() const {
	return this->m_Speaker;
}
void SpeechManager::setSpeakerMap(map<int, Speaker>& m) {
	this->m_Speaker = m;
}
int SpeechManager::getIndex() const {
	return this->m_Index;
}
void SpeechManager::setIndex(int index) {
	this->m_Index = index;
}
bool SpeechManager::getFileIsEmpty() const{
	return this->fileIsEmpty;
}
void SpeechManager::setFileIsEmpty(bool flag) {
	this->fileIsEmpty = flag;
}
map<int, vector<string>> SpeechManager::getRecord() const {
	return this->m_Record;
}
void SpeechManager::setRecord(map<int, vector<string>>& m) {
	this->m_Record = m;
}


//�˵�����
void SpeechManager::ShowMenu() {
	cout << "************************************" << endl;
	cout << "********* ��ӭ�μ��ݽ����� *********" << endl;
	cout << "********** 1.��ʼ�ݽ����� **********" << endl;
	cout << "********** 2.�鿴�����¼ **********" << endl;
	cout << "********** 3.��ձ�����¼ **********" << endl;
	cout << "********** 0.�˳��������� **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//�˳�����
void SpeechManager::ExitSystem() {
	cout << "��ӭ�´�ʹ�ã�" << endl;
	exit(0);
}

//��ʼ����
void SpeechManager::StartSpeech() {
	//��һ�ֱ���
	//1.��ǩ
	this->SpeechDraw();
	//2.����
	this->SpeechContest();
	//3.��ʾ�������
	this->ShowScore();

	//�ڶ��ֱ���
	++this->m_Index;
	//1.��ǩ
	this->SpeechDraw();
	//2.����
	this->SpeechContest();
	//3.��ʾ�������
	this->ShowScore();
	//4.�ѽ�������ļ�
	this->SaveRecord();

	//����
	this->Init();

	cout << endl << "�����������лĻ��" << endl << endl;
	system("pause");
	system("cls");
}

//��ʾ�����¼
void SpeechManager::ShowRecord() {
	//for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++) {
	//	cout << "�� " << it->first + 1 << "�죺" << endl;
	//	cout << "�ھ�No��" << it->second[0] << "\t������" << it->second[1] << "\t������" << it->second[2] << endl;
	//	cout << "�Ǿ�No��" << it->second[3] << "\t������" << it->second[4] << "\t������" << it->second[5] << endl;
	//	cout << "����No��" << it->second[6] << "\t������" << it->second[7] << "\t������" << it->second[8] << endl;
	//}

	if (this->fileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "�� " << i + 1 << " �죺 " << endl;
			cout << "�ھ�No�� " << this->m_Record[i][0] << "\t������" << this->m_Record[i][1] << "\t������" << this->m_Record[i][2] << endl;
			cout << "�Ǿ�No�� " << this->m_Record[i][3] << "\t������" << this->m_Record[i][4] << "\t������" << this->m_Record[i][5] << endl;
			cout << "����No�� " << this->m_Record[i][6] << "\t������" << this->m_Record[i][7] << "\t������" << this->m_Record[i][8] << endl;
		}
	}


	system("pause");
	system("cls");
}

//����ļ�
void SpeechManager::ClearRecord() {
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "- 1.��" << endl;
	cout << "- 2.��" << endl;
	int select;
	cin >> select;

	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc); //ɾ�������´���
		ofs.close();

		this->Init();

		cout << "��ճɹ���" << endl;
	} 
	system("pause");
	system("cls");
}

//��������
SpeechManager::~SpeechManager() {

}



//���ñ����ͱ�����¼
void SpeechManager::Init() {
	this->InitSpeech();
	this->CreateSpeaker();
	this->LoadRecord();
}

//��ʼ������������
void SpeechManager::InitSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1; //��ʼΪ��һ��
	this->fileIsEmpty = true;
	this->m_Record.clear();
}

//����ѡ��
void SpeechManager::CreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		//string name = "ѡ��" + nameSeed[i];
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker speaker;
		speaker.setName(name);

		for (int j = 0; j < 2; j++) {
			speaker.setScore(0, j);
		}
		this->v1.push_back(i + 10001);
		//ѡ�ֱ�ż���Ӧ��ѡ����Ϣ����map����
		this->m_Speaker.insert(make_pair(i + 10001, speaker));
	}
}

//���vector��ÿһ�ֵ��˵ı��
void SpeechManager::MyPrintVector(const vector<int>& v) {
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

//��ǩ
void SpeechManager::SpeechDraw() {
	cout << "�� << " << this->m_Index << " >> ��ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1) { //��һ��
		random_shuffle(v1.begin(), v1.end());
		this->MyPrintVector(v1);
	}
	else { //�ڶ���
		random_shuffle(v2.begin(), v2.end());
		this->MyPrintVector(v2);
	}

	cout << "----------------------------------" << endl;
}

//����
void SpeechManager::SpeechContest() {
	cout << endl;
	cout << "----------------- �� " << this->m_Index << " �ֱ�����ʽ��ʼ-----------------" << endl;

	//׼��һ����ʱ���� ���С��ɼ�
	multimap<double, int, greater<double>> groupScore; // keyֵ�Ƿ�����valueֵ��ѡ�ֱ�ţ��Ӵ�С����

	int num = 0; //��¼��Ա����

	vector<int> v_Src; //����ѡ�ֵ�����

	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//��������ѡ�� ���б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		
		++num;

		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++) { //10����ί
			double score = (rand() % 401 + 600) / 10.0f; //600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>()); //�Ӵ�С
		d.pop_back(); //ȥ����ͷ�
		d.pop_front(); //ȥ����߷�

		double sum = accumulate(d.begin(), d.end(), 0.0f); //��ӵ��ܷ�
		double avg = sum / (1.0 * d.size()); //ƽ����

		//cout << "No." << *it << "\tName: " << this->m_Speaker[*it].getName() << "\tAverage: " << avg << endl;

		//��ƽ���ַ�������
		//this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		this->m_Speaker[*it].setScore(avg, this->m_Index - 1);

		//�����ݷ�����ʱС������
		groupScore.insert(make_pair(avg, *it)); //key�ǵõ���ƽ���֣�value��ѡ�ֱ��


		//ÿ����ȡ��ǰ����
		if (!(num % 6)) {
			cout << "�� " << num / 6 << " ��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "No." << it->second << "\tName: " << this->m_Speaker[it->second].getName()
					<< "\tScore: " << this->m_Speaker[it->second].getScore(this->m_Index - 1) << endl;
			}
			//ȡ��ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count++ < 3; it++) {
				if (this->m_Index == 1) {
					this->v2.push_back(it->second);
				}
				else {
					this->vVictory.push_back(it->second);
				}
			}

			//С���������
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------------- �� " << this->m_Index << " �ֱ���������ϣ�-----------------" << endl;
	system("pause");
}

//��ʾ�÷�
void SpeechManager::ShowScore() {
	cout << "----------------- �� " << this->m_Index << " �ֽ���ѡ����Ϣ���� -----------------" << endl;

	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "No." << *it << "\t ����: " << this->m_Speaker[*it].getName() << "\t����: " << this->m_Speaker[*it].getScore(this->m_Index - 1) << endl;
	}
	cout << endl;
	system("pause");
}

//���������浽���
void SpeechManager::SaveRecord() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app); //��׷�ӵķ�ʽд�ļ�

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].getName() << "," << this->m_Speaker[*it].getScore(1) << ","; //�����ÿһ�����ã��ָ���
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�ѱ���!" << endl;
	//this->fileIsEmpty = false;
}

//��ȡ��¼����
void SpeechManager::LoadRecord() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�

	//�ļ�������
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	//�ļ�������˵����
	char ch;
	ifs >> ch; //ֻ����һ���ַ�
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ�գ�" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch); //�������ȡ�ĵ����ַ��Ż���

	string data; //��ű���е�һ������
	int index = 0; //�ڼ���

	while (ifs >> data) {
		//10002,ѡ��B,86.675,10009,ѡ��I,81.3,10007,ѡ��G,78.55,
		//cout << data << endl;

		vector<string> v; //���9��string���ַ���

		int pos = -1; //���ҵ�","λ�õı���
		int start = 0; //��ʼλ��

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			else {
				string temp = data.substr(start, pos - start); //ÿ��ȡһ������������ַ���
				//cout << temp << endl;
				v.push_back(temp);
				start = pos + 1;
			}

		}
		this->m_Record.insert(make_pair(index++, v));

	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
	//	cout << "�� " << it->first + 1 << "�죺" << endl;
	//	cout << "�ھ�No��" << it->second[0] << "\t������" << it->second[1] << "\t������" << it->second[2] << endl;
	//	cout << "�Ǿ�No��" << it->second[3] << "\t������" << it->second[4] << "\t������" << it->second[5] << endl;
	//	cout << "����No��" << it->second[6] << "\t������" << it->second[7] << "\t������" << it->second[8] << endl;
	//}

}
