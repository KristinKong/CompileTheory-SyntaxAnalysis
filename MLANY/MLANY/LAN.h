#pragma once
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
#define ROW 50
#define COL 20
#define DEBUG
class CLAN
{
public:
	int count_line;
	int count_VT;
	char Grammer[ROW][COL];   //�洢�ķ�
	char PreForm[COL][COL];   //�洢���ȹ�ϵ��
	char FirVT[ROW][COL / 2]; //firsrvt
	char LasVT[ROW][COL / 2]; //lastvt
	char stack[ROW]; //����ջ
public:
	CLAN();
	~CLAN();

	/*�����ֵĹ��ܺ���*/
	bool Pre_Process(CString filepathname);        //Ԥ����
	bool Init_PreForm(int j, int &m, char c);  //��ʼ�����ȹ�ϵ��
	bool Fill_BackSpace_To_Pre();   //���ȹ�ϵ����ಿ����ո�
	bool Get_FirstVT(int i);        //��firstvt
	bool Get_LastVT(int i);         //��lastvt
	bool Get_PreForm();            //�õ����ȹ�ϵ��
	bool Fill_FirVT_To_Pre(char c, int i);  //��i��FirVT�������ȹ�ϵ��
	bool Fill_LasVT_To_Pre(char c, int i);  //��i��FirVT�������ȹ�ϵ��
	bool Is_Upa(char c1); //�Ǵ�д��ĸ
	int Find_Next(char c);  //Ѱ����һ�����﷨�Ŀ�ʼ
	int Find_Pos(char c1, char c2, int &row, int &col);  //Ѱ��������λ��
	int Is_Head(char c1, char c2); //��firstvt,�����|ǰ�����������ʽ
	int Is_Tail(char c1, char c2); //��lastvt,�����|ǰ�����������ʽ
	bool Copy_FL(int &m, char c1[], char c2[]);  //����һ�����ϸ��Ƶ�ǰһ��������
	bool Get_Two_Set();     //���firstvt��lastvt��������
	bool Fill_End_In_PreForm();   //��#���������ȱ�
	bool Include_Process(CString s1,CString &aim);       //��Լ����
	void Copy_All(int st,int ss,char op,CString s1, CString &aim);

	/*���Ƶ��༭����������*/
	bool Print_Grammer(CString &gra);
	bool Print_LastVT(CString &Las);
	bool Print_FirsVT(CString &Fir);
	bool Print_PreForm(CString &pre);

	/*��װ��Ĵ������̺���*/
	bool Main_Function(CString  filepathname, CString &gra, CString &fir, CString &las, CString &pre);
};

