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
	//���캯��
	SpeechManager();
	//�˵�����
	void show_menu();
	//�˳�����
	void exitSystem();
	//��ʼ������ ����
	void initSpeech();
	//����ѡ��
	void createSpeaker();
	//��ʼ����  �ݽ���������
	void startSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�������
	void showScore();
	//�ļ���������
	void saveRecord();
	//��ȡ��¼
	void loadRecord();
	// �ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	// ��������¼����
	map<int, vector<string>> m_Record;
	//��ʾ�����¼
	void showRecore();
	//��ռ�¼
	void  clearRecord();
	//��������
	~SpeechManager();

	//��Ա����
	vector<int> v1;  //��һ��ѡ�ֱ��  12

	vector<int> v2;  //��һ�ֽ���ѡ�ֱ��  6

	vector<int> vVictory;  //ʤ��ǰ����ѡ�ֱ��  3

	map<int, Speaker> m_Speaker;  //��ű���Լ� ��Ӧѡ�� ����
	
	int m_index;//��������
};

