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
		//���Դ���
		/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++)
		{
			cout << "��ţ�" << it->first 
				 << " ������" << it->second.m_name 
				 << " ������" << it->second.m_Score[sm.m_index - 1] 
				 << endl;
		}*/
		cout << "������ѡ�" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1://��ʼ����
			sm.startSpeech();
			break;
		case 2://�鿴�����¼
			sm.showRecore();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳�
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