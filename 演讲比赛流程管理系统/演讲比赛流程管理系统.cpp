#define  _CRT_SECURE_NO_WARNINGS 1
#include "iostream"
#include "SpeechManager.h"
using namespace std;


int main() {
	srand((unsigned int)time(NULL));
	int choice = 0;
	SpeechManager sm;
	while (true)
	{
		sm.show_menu();
		//测试代码
		/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
		{
			cout << "编号：" << it->first 
				 << " 姓名：" << it->second.m_name 
				 << " 分数：" << it->second.m_Score[sm.m_index - 1] 
				 << endl;
		}*/
		cout << "请输入选项：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://开始比赛
			sm.startSpeech();
			break;
		case 2://查看往届记录
			sm.showRecore();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}