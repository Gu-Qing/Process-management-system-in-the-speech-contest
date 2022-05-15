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


//菜单功能
void SpeechManager::ShowMenu() {
	cout << "************************************" << endl;
	cout << "********* 欢迎参加演讲比赛 *********" << endl;
	cout << "********** 1.开始演讲比赛 **********" << endl;
	cout << "********** 2.查看往届记录 **********" << endl;
	cout << "********** 3.清空比赛记录 **********" << endl;
	cout << "********** 0.退出比赛程序 **********" << endl;
	cout << "************************************" << endl;
	cout << endl;
}

//退出功能
void SpeechManager::ExitSystem() {
	cout << "欢迎下次使用！" << endl;
	exit(0);
}

//开始比赛
void SpeechManager::StartSpeech() {
	//第一轮比赛
	//1.抽签
	this->SpeechDraw();
	//2.比赛
	this->SpeechContest();
	//3.显示晋级结果
	this->ShowScore();

	//第二轮比赛
	++this->m_Index;
	//1.抽签
	this->SpeechDraw();
	//2.比赛
	this->SpeechContest();
	//3.显示决赛结果
	this->ShowScore();
	//4.把结果放入文件
	this->SaveRecord();

	//重置
	this->Init();

	cout << endl << "本届比赛完美谢幕！" << endl << endl;
	system("pause");
	system("cls");
}

//显示往届记录
void SpeechManager::ShowRecord() {
	//for (map<int, vector<string>>::iterator it = this->m_Record.begin(); it != this->m_Record.end(); it++) {
	//	cout << "第 " << it->first + 1 << "届：" << endl;
	//	cout << "冠军No：" << it->second[0] << "\t姓名：" << it->second[1] << "\t分数：" << it->second[2] << endl;
	//	cout << "亚军No：" << it->second[3] << "\t姓名：" << it->second[4] << "\t分数：" << it->second[5] << endl;
	//	cout << "季军No：" << it->second[6] << "\t姓名：" << it->second[7] << "\t分数：" << it->second[8] << endl;
	//}

	if (this->fileIsEmpty) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			cout << "第 " << i + 1 << " 届： " << endl;
			cout << "冠军No： " << this->m_Record[i][0] << "\t姓名：" << this->m_Record[i][1] << "\t分数：" << this->m_Record[i][2] << endl;
			cout << "亚军No： " << this->m_Record[i][3] << "\t姓名：" << this->m_Record[i][4] << "\t分数：" << this->m_Record[i][5] << endl;
			cout << "季军No： " << this->m_Record[i][6] << "\t姓名：" << this->m_Record[i][7] << "\t分数：" << this->m_Record[i][8] << endl;
		}
	}


	system("pause");
	system("cls");
}

//清空文件
void SpeechManager::ClearRecord() {
	cout << "是否确定清空文件？" << endl;
	cout << "- 1.是" << endl;
	cout << "- 2.否" << endl;
	int select;
	cin >> select;

	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc); //删除后重新创建
		ofs.close();

		this->Init();

		cout << "清空成功！" << endl;
	} 
	system("pause");
	system("cls");
}

//析构函数
SpeechManager::~SpeechManager() {

}



//重置比赛和比赛记录
void SpeechManager::Init() {
	this->InitSpeech();
	this->CreateSpeaker();
	this->LoadRecord();
}

//初始化容器和属性
void SpeechManager::InitSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1; //初始为第一轮
	this->fileIsEmpty = true;
	this->m_Record.clear();
}

//创建选手
void SpeechManager::CreateSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		//string name = "选手" + nameSeed[i];
		string name = "选手";
		name += nameSeed[i];
		Speaker speaker;
		speaker.setName(name);

		for (int j = 0; j < 2; j++) {
			speaker.setScore(0, j);
		}
		this->v1.push_back(i + 10001);
		//选手编号及对应的选手信息放入map容器
		this->m_Speaker.insert(make_pair(i + 10001, speaker));
	}
}

//输出vector中每一轮的人的编号
void SpeechManager::MyPrintVector(const vector<int>& v) {
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

//抽签
void SpeechManager::SpeechDraw() {
	cout << "第 << " << this->m_Index << " >> 轮选手正在抽签" << endl;
	cout << "----------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1) { //第一轮
		random_shuffle(v1.begin(), v1.end());
		this->MyPrintVector(v1);
	}
	else { //第二轮
		random_shuffle(v2.begin(), v2.end());
		this->MyPrintVector(v2);
	}

	cout << "----------------------------------" << endl;
}

//比赛
void SpeechManager::SpeechContest() {
	cout << endl;
	cout << "----------------- 第 " << this->m_Index << " 轮比赛正式开始-----------------" << endl;

	//准备一个临时容器 存放小组成绩
	multimap<double, int, greater<double>> groupScore; // key值是分数，value值是选手编号，从大到小排序

	int num = 0; //记录人员个数

	vector<int> v_Src; //比赛选手的容器

	if (this->m_Index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}

	//遍历所有选手 进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		
		++num;

		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++) { //10个评委
			double score = (rand() % 401 + 600) / 10.0f; //600 ~ 1000
			//cout << score << " ";
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>()); //从大到小
		d.pop_back(); //去除最低分
		d.pop_front(); //去除最高分

		double sum = accumulate(d.begin(), d.end(), 0.0f); //相加得总分
		double avg = sum / (1.0 * d.size()); //平均分

		//cout << "No." << *it << "\tName: " << this->m_Speaker[*it].getName() << "\tAverage: " << avg << endl;

		//将平均分放入容器
		//this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		this->m_Speaker[*it].setScore(avg, this->m_Index - 1);

		//将数据放入临时小组容器
		groupScore.insert(make_pair(avg, *it)); //key是得到的平均分，value是选手编号


		//每六人取出前三名
		if (!(num % 6)) {
			cout << "第 " << num / 6 << " 组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "No." << it->second << "\tName: " << this->m_Speaker[it->second].getName()
					<< "\tScore: " << this->m_Speaker[it->second].getScore(this->m_Index - 1) << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count++ < 3; it++) {
				if (this->m_Index == 1) {
					this->v2.push_back(it->second);
				}
				else {
					this->vVictory.push_back(it->second);
				}
			}

			//小组容器清空
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "----------------- 第 " << this->m_Index << " 轮比赛比赛完毕！-----------------" << endl;
	system("pause");
}

//显示得分
void SpeechManager::ShowScore() {
	cout << "----------------- 第 " << this->m_Index << " 轮晋级选手信息如下 -----------------" << endl;

	vector<int> v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << "No." << *it << "\t 姓名: " << this->m_Speaker[*it].getName() << "\t分数: " << this->m_Speaker[*it].getScore(this->m_Index - 1) << endl;
	}
	cout << endl;
	system("pause");
}

//将分数保存到表格
void SpeechManager::SaveRecord() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app); //用追加的方式写文件

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].getName() << "," << this->m_Speaker[*it].getScore(1) << ","; //表格中每一列是用，分隔的
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存!" << endl;
	//this->fileIsEmpty = false;
}

//读取记录分数
void SpeechManager::LoadRecord() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件

	//文件不存在
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	//文件被清空了的情况
	char ch;
	ifs >> ch; //只读入一个字符
	if (ifs.eof()) {
		//cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch); //将上面读取的单个字符放回来

	string data; //存放表格中的一行数据
	int index = 0; //第几届

	while (ifs >> data) {
		//10002,选手B,86.675,10009,选手I,81.3,10007,选手G,78.55,
		//cout << data << endl;

		vector<string> v; //存放9个string的字符串

		int pos = -1; //查找到","位置的变量
		int start = 0; //起始位置

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				break;
			}
			else {
				string temp = data.substr(start, pos - start); //每次取一个逗号区间的字符串
				//cout << temp << endl;
				v.push_back(temp);
				start = pos + 1;
			}

		}
		this->m_Record.insert(make_pair(index++, v));

	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
	//	cout << "第 " << it->first + 1 << "届：" << endl;
	//	cout << "冠军No：" << it->second[0] << "\t姓名：" << it->second[1] << "\t分数：" << it->second[2] << endl;
	//	cout << "亚军No：" << it->second[3] << "\t姓名：" << it->second[4] << "\t分数：" << it->second[5] << endl;
	//	cout << "季军No：" << it->second[6] << "\t姓名：" << it->second[7] << "\t分数：" << it->second[8] << endl;
	//}

}
