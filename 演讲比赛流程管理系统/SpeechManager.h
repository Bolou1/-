#pragma once
#include "string"
#include "algorithm"
#include "functional"
#include "numeric"
#include "iostream"
#include "vector"
#include "map"
#include "deque"
#include "Speaker.h"
#include "fstream"

using namespace std;


class SpeechManager {
public:
	//构造函数
	SpeechManager();
	//菜单界面
	void show_menu();
	//退出程序
	void exitSystem();
	//初始化容器 属性
	void initSpeech();
	//创建选手
	void createSpeaker();
	//开始比赛  演讲控制流程
	void startSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示比赛结果
	void showScore();
	//文件保存数据
	void saveRecord();
	//读取记录
	void loadRecord();
	// 判断文件是否为空
	bool fileIsEmpty;
	// 存放往届记录容器
	map<int, vector<string>> m_Record;
	//显示往届记录
	void showRecore();
	//清空记录
	void  clearRecord();
	//析构函数
	~SpeechManager();

	//成员属性
	vector<int> v1;  //第一轮选手编号  12

	vector<int> v2;  //第一轮晋级选手编号  6

	vector<int> vVictory;  //胜出前三名选手编号  3

	map<int, Speaker> m_Speaker;  //存放编号以及 对应选手 容器
	
	int m_index;//比赛轮数
};

