#define  _CRT_SECURE_NO_WARNINGS 1
#include "SpeechManager.h"




//构造函数
SpeechManager::SpeechManager() {
	//初始化容器 属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//记录往届数据
	this->loadRecord();
}

//菜单界面
void SpeechManager::show_menu() {
	cout << "---------------------------------" << endl;
	cout << "--------欢迎参加演讲比赛---------" << endl;
	cout << "--------1.开始演讲比赛-----------" << endl;
	cout << "--------2.查看往届记录-----------" << endl;
	cout << "--------3.清空比赛记录-----------" << endl;
	cout << "--------0.退出比赛---------------" << endl;
	cout << "---------------------------------" << endl;
	cout << endl;
}

//退出程序
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//初始化容器属性
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	this->m_index = 1;
}

//创建选手
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[0] = 0;
		}
		//12名选手编号
		this->v1.push_back(i + 10001);

		//选手  对应的编号  放入map
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//抽签
void SpeechManager::speechDraw() {
	cout << "第《" << this->m_index << "》轮比赛选手抽取" << endl;
	cout << "----------------------------" << endl;
	cout << "抽取后演讲顺序如下：" << endl;

	if (this->m_index == 1)
	{
		//第一轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "----------------------------" << endl;
	system("pause");
}

//比赛
void SpeechManager::speechContest() {
	cout << "第《" << this->m_index << "》轮比赛开始" << endl;
	cout << "----------------------------" << endl;
	multimap<double, int, greater<double>> groupScore; //临时容器  key=avg  value = 选手编号
	int num = 0;  //记录人数  每六个一组
	//创建比赛人员容器
	vector<int> v_Src;
	if (this->m_index ==1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//遍历比赛人员
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//给比赛人员打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			//每个人都有10个 分数
			double Score = (rand() % 401 + 600)/10.f;//600-1000   / 10
			d.push_back(Score);
		}
		//排序
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//去除最高
		d.pop_back();//去除最低

		double sum = accumulate(d.begin(), d.end(), 0.0f);//总分
		double avg = sum / (double)d.size(); //平均分

		//把分 放入map
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;
		
		//每6给人一组  用临时容器存入
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second
					<< " 姓名：" << this->m_Speaker[it->second].m_name
					<< "分数：" << this->m_Speaker[it->second].m_Score[this->m_index - 1] << endl;
			}

			int count = 0;//记录 取前三名
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&& count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();//清空  防止下一组打印出12个人一组
			cout << endl;
		}
		
		
	}
	cout << "第《" << this->m_index << "》轮比赛结束" << endl;
	system("pause");
}

//显示比赛结果
void SpeechManager::showScore() {
	cout << "第《" << this->m_index << "》轮比赛结果" << endl;
	vector<int> v;
	if (this->m_index==1)
	{
		v = v2;
	}
	else
	{
		v = vVictory; 
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_name 
			<< " 成绩：" << this->m_Speaker[*it].m_Score[this->m_index-1] <<
			endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_menu();
}

//文件保存数据
void SpeechManager::saveRecord() {
	//写文件
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs <<  *it << ","
			<<  this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录保存完毕" << endl;

	//有记录了，文件不为空
	this->fileIsEmpty = false;
}

//开始比赛
void SpeechManager::startSpeech() {
	//第一轮比赛
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();

	this->m_index++;
	//第二轮比赛
	//1.抽签
	this->speechDraw();

	//2.比赛
	this->speechContest();

	//3.显示结果
	this->showScore();

	//4.记录数据
	this->saveRecord();

	//初始化容器 属性
	this->initSpeech();
	//创建选手
	this->createSpeaker();
	//记录往届数据
	this->loadRecord();

	cout << "比赛out" << endl;
	system("pause");
	system("cls");

}

//读取记录
void SpeechManager::loadRecord() {
	//文件不存在
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	ifs.putback(ch);//放回
	string data;
	vector<string> v;
	int index = 0;
	while (ifs>>data)
	{
		//cout << data << endl;
		//10002,86.675,10009,81.3,10007,78.55,
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start); 
			//cout << temp << endl;
			v.push_back(temp);  //把数据存入  v容器
			start = pos + 1;
		}
		index++; 
		this->m_Record.insert(make_pair(index, v));  //把存入数据的v容器  放入 map容器 key = 第几届 
		
		
		
	}
	ifs.close();
}

//显示往届记录
void SpeechManager::showRecore() {
	if (this->fileIsEmpty)
	{
		cout << "文件为空或记录不存在" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
			cout << "第" << it->first << "届 冠军编号：" << it->second[0] << " 成绩：" << it->second[1] << " "
				<< "亚军编号：" << it->second[2] << " 成绩：" << it->second[3] << " "
				<< "季军编号：" << it->second[4] << " 成绩：" << it->second[5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager:: clearRecord() {
	cout << "确定清空？" << endl;
	int choice = 0;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	cin >> choice;
	if (choice ==1)
	{
		ofstream ofs("speech.csv", ios::trunc);

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "欧克" << endl;
	}
	
	system("pause");
	system("cls");
}


//析构函数
SpeechManager::~SpeechManager() {

	
}
