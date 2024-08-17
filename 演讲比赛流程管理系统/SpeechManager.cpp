#define  _CRT_SECURE_NO_WARNINGS 1
#include "SpeechManager.h"




//���캯��
SpeechManager::SpeechManager() {
	//��ʼ������ ����
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//��¼��������
	this->loadRecord();
}

//�˵�����
void SpeechManager::show_menu() {
	cout << "---------------------------------" << endl;
	cout << "--------��ӭ�μ��ݽ�����---------" << endl;
	cout << "--------1.��ʼ�ݽ�����-----------" << endl;
	cout << "--------2.�鿴�����¼-----------" << endl;
	cout << "--------3.��ձ�����¼-----------" << endl;
	cout << "--------0.�˳�����---------------" << endl;
	cout << "---------------------------------" << endl;
	cout << endl;
}

//�˳�����
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//��ʼ����������
void SpeechManager::initSpeech() {
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
	this->m_index = 1;
}

//����ѡ��
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_Score[0] = 0;
		}
		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//ѡ��  ��Ӧ�ı��  ����map
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}

//��ǩ
void SpeechManager::speechDraw() {
	cout << "�ڡ�" << this->m_index << "���ֱ���ѡ�ֳ�ȡ" << endl;
	cout << "----------------------------" << endl;
	cout << "��ȡ���ݽ�˳�����£�" << endl;

	if (this->m_index == 1)
	{
		//��һ��
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ���
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

//����
void SpeechManager::speechContest() {
	cout << "�ڡ�" << this->m_index << "���ֱ�����ʼ" << endl;
	cout << "----------------------------" << endl;
	multimap<double, int, greater<double>> groupScore; //��ʱ����  key=avg  value = ѡ�ֱ��
	int num = 0;  //��¼����  ÿ����һ��
	//����������Ա����
	vector<int> v_Src;
	if (this->m_index ==1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}
	//����������Ա
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��������Ա���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			//ÿ���˶���10�� ����
			double Score = (rand() % 401 + 600)/10.f;//600-1000   / 10
			d.push_back(Score);
		}
		//����
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//ȥ�����
		d.pop_back();//ȥ�����

		double sum = accumulate(d.begin(), d.end(), 0.0f);//�ܷ�
		double avg = sum / (double)d.size(); //ƽ����

		//�ѷ� ����map
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;
		
		//ÿ6����һ��  ����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second
					<< " ������" << this->m_Speaker[it->second].m_name
					<< "������" << this->m_Speaker[it->second].m_Score[this->m_index - 1] << endl;
			}

			int count = 0;//��¼ ȡǰ����
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

			groupScore.clear();//���  ��ֹ��һ���ӡ��12����һ��
			cout << endl;
		}
		
		
	}
	cout << "�ڡ�" << this->m_index << "���ֱ�������" << endl;
	system("pause");
}

//��ʾ�������
void SpeechManager::showScore() {
	cout << "�ڡ�" << this->m_index << "���ֱ������" << endl;
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
		cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_name 
			<< " �ɼ���" << this->m_Speaker[*it].m_Score[this->m_index-1] <<
			endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_menu();
}

//�ļ���������
void SpeechManager::saveRecord() {
	//д�ļ�
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs <<  *it << ","
			<<  this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�������" << endl;

	//�м�¼�ˣ��ļ���Ϊ��
	this->fileIsEmpty = false;
}

//��ʼ����
void SpeechManager::startSpeech() {
	//��һ�ֱ���
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();

	this->m_index++;
	//�ڶ��ֱ���
	//1.��ǩ
	this->speechDraw();

	//2.����
	this->speechContest();

	//3.��ʾ���
	this->showScore();

	//4.��¼����
	this->saveRecord();

	//��ʼ������ ����
	this->initSpeech();
	//����ѡ��
	this->createSpeaker();
	//��¼��������
	this->loadRecord();

	cout << "����out" << endl;
	system("pause");
	system("cls");

}

//��ȡ��¼
void SpeechManager::loadRecord() {
	//�ļ�������
	ifstream ifs;
	ifs.open("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	ifs.putback(ch);//�Ż�
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
			v.push_back(temp);  //�����ݴ���  v����
			start = pos + 1;
		}
		index++; 
		this->m_Record.insert(make_pair(index, v));  //�Ѵ������ݵ�v����  ���� map���� key = �ڼ��� 
		
		
		
	}
	ifs.close();
}

//��ʾ�����¼
void SpeechManager::showRecore() {
	if (this->fileIsEmpty)
	{
		cout << "�ļ�Ϊ�ջ��¼������" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
			cout << "��" << it->first << "�� �ھ���ţ�" << it->second[0] << " �ɼ���" << it->second[1] << " "
				<< "�Ǿ���ţ�" << it->second[2] << " �ɼ���" << it->second[3] << " "
				<< "������ţ�" << it->second[4] << " �ɼ���" << it->second[5] << endl;
		}
	}
	
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager:: clearRecord() {
	cout << "ȷ����գ�" << endl;
	int choice = 0;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	cin >> choice;
	if (choice ==1)
	{
		ofstream ofs("speech.csv", ios::trunc);

		this->initSpeech();

		this->createSpeaker();

		this->loadRecord();

		cout << "ŷ��" << endl;
	}
	
	system("pause");
	system("cls");
}


//��������
SpeechManager::~SpeechManager() {

	
}
