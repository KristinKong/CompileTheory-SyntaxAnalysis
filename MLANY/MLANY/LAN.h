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
	char Grammer[ROW][COL];   //存储文法
	char PreForm[COL][COL];   //存储优先关系表
	char FirVT[ROW][COL / 2]; //firsrvt
	char LasVT[ROW][COL / 2]; //lastvt
	char stack[ROW]; //符号栈
public:
	CLAN();
	~CLAN();

	/*各部分的功能函数*/
	bool Pre_Process(CString filepathname);        //预处理
	bool Init_PreForm(int j, int &m, char c);  //初始化优先关系表
	bool Fill_BackSpace_To_Pre();   //优先关系表多余部分填空格
	bool Get_FirstVT(int i);        //求firstvt
	bool Get_LastVT(int i);         //求lastvt
	bool Get_PreForm();            //得到优先关系表
	bool Fill_FirVT_To_Pre(char c, int i);  //将i的FirVT填入优先关系表
	bool Fill_LasVT_To_Pre(char c, int i);  //将i的FirVT填入优先关系表
	bool Is_Upa(char c1); //是大写字母
	int Find_Next(char c);  //寻找下一个求语法的开始
	int Find_Pos(char c1, char c2, int &row, int &col);  //寻找填入表的位置
	int Is_Head(char c1, char c2); //求firstvt,如果是|前后的两个产生式
	int Is_Tail(char c1, char c2); //求lastvt,如果是|前后的两个产生式
	bool Copy_FL(int &m, char c1[], char c2[]);  //将后一个集合复制到前一个集合里
	bool Get_Two_Set();     //求得firstvt和lastvt两个集合
	bool Fill_End_In_PreForm();   //把#号填入优先表
	bool Include_Process(CString s1,CString &aim);       //规约函数
	void Copy_All(int st,int ss,char op,CString s1, CString &aim);

	/*复制到编辑框的输出函数*/
	bool Print_Grammer(CString &gra);
	bool Print_LastVT(CString &Las);
	bool Print_FirsVT(CString &Fir);
	bool Print_PreForm(CString &pre);

	/*封装后的处理流程函数*/
	bool Main_Function(CString  filepathname, CString &gra, CString &fir, CString &las, CString &pre);
};

