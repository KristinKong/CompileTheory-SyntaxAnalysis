#include "stdafx.h"
#include "LAN.h"

#define DEBUG

CLAN::CLAN()
{
	count_VT = 0;
}

CLAN::~CLAN()
{
}

/*���ȹ�ϵ����ಿ����ո�*/
bool CLAN::Fill_BackSpace_To_Pre()
{
	int i, j;
	for (i = 1; i <= count_VT; i++)
	{
		for ( j = 1; j <= count_VT; j++)
			PreForm[i][j] = ' ';
	}
	PreForm[0][0] = ' ';
	return true;
}
/*���Ƽ���*/
bool CLAN::Copy_FL(int &m, char c1[], char c2[])
{
	int i, j;
	bool cop;
	for (j = 2; c2[j] != '\r'; j++)
	{
		cop = true;
		for (i = 2; c1[i] != '\r'; i++){
			if (c1[i] == c2[j])
				cop = false;
		}
		if (cop){
			c1[m++] = c2[j];
			c1[m] = '\r';     //����������һλ
		}
	}
	return true;
}

/*�ж��Ƿ�����������д��ĸ*/
bool CLAN::Is_Upa(char c1)
{
	if (c1 >= 'A'&&c1 <= 'Z')
		return true;
	else return false;
}

/*�鿴�Ƿ�P->a|Qa��ģʽ*/
int CLAN::Is_Head(char c1, char c2)
{
	if (c1 == '>' || c1 == '|'){
		if (!Is_Upa(c2))       //����firstvt
			return 1;
		else
			return 2;         //������
	}
	else
		return 3;    //������һ��
}

/*�鿴�Ƿ�P->a|aQ��ģʽ*/
int CLAN::Is_Tail(char c1, char c2)
{
	if (c2 == '|' || c2 == '\r'){
		if (!Is_Upa(c1))      //����lastvt 
			return 1;
		else
			return 2;         //������
	}
	else
		return 3;    //������һ��
}

/*��#���������ȹ�ϵ��*/
bool CLAN::Fill_End_In_PreForm()
{
	int i, j, row, col, res, temp;
	char c1, c2,c3;
	for (i = 1; i <= count_line; i++)
	{
		c1 = Grammer[i][3];
		c2 = Grammer[i][4];
		c3 = Grammer[i][5];
		for (j = 3; c2 != '\r'; j++, c1 = Grammer[i][j], c2 = Grammer[i][j + 1])
		{
			/*��С��*/
			res = Is_Head(c1, c2);
			if (res == 1)  {//c1Ϊͷ��c2Ϊ�ս��,��#<c2�������
				temp = Find_Pos('#', c2, row, col);
				if (temp)
					PreForm[row][col] = '<';
			}
			else if (res == 2){//c1Ϊͷ��c2Ϊ���ս��,��#<first��c2���������
				temp = Find_Next(c2);
				Fill_FirVT_To_Pre('#', temp);
				c3 = Grammer[i][j + 2];
				if (c3 != '|' || c3 != '\r'){  //c3Ϊ�ս��,��#<c3
					Find_Pos('#', c3, row, col);
					PreForm[row][col] = '<';
				}
			}
			else;

			/*�����*/
			res = Is_Tail(c1, c2);
			if (res == 1)  {//c1Ϊ�ս��,c2Ϊβ����c1>#�������
				temp = Find_Pos(c1, '#', row, col);
				if (temp)
					PreForm[row][col] = '>';
			}
			else if (res == 2){//c1Ϊ���ս��,c2Ϊβ����last(c1)>#�������
				temp = Find_Next(c1);
				Fill_LasVT_To_Pre('#', temp);
				c3 = Grammer[i][j-1]; 
				if (c3 != '|' || c3 != '\r'){  //c0Ϊ�ս��,��c0>#
					Find_Pos(c3, '#', row, col);
					PreForm[row][col] = '>';
				}
			}
			else;
		}
	}
	PreForm[count_VT][count_VT] = '='; //##�����
	return 1;
}

/*�����ս�������ȹ�ϵ��*/
bool  CLAN::Init_PreForm(int j, int &m, char c)
{
	bool cop;
	int i;
	if (!Is_Upa(c) && c != '|'&&j > 3){      //c����Ч�ս��
		cop = true;
		for (i = 0; PreForm[0][i] != '\r'; i++)
		{
			if (PreForm[0][i] == c)
				cop = false;
		}
		if (cop){
			PreForm[0][m] = c;
			PreForm[m++][0] = c;
			PreForm[0][++i] = '\r';     //����������һλ
			return true;
		}
	}
	return false;
}
/*Ѱ����һ�����﷨�Ŀ�ʼ*/
int CLAN::Find_Next(char c)
{
	for (int i = 1; i <= count_line; i++)
	if (c == Grammer[i][1])
		return i;
	return 0;
}

/*�õ�firstvt����*/
bool CLAN::Get_FirstVT(int i)
{
	if (!FirVT[i][0]){      //û�����first����
		int m = 1, j = 4;
		char c1 = Grammer[i][j], c2;
		FirVT[i][m++] = Grammer[i][1];
		for (; c1 != '\r'; j++, c1 = Grammer[i][j])
		{
			int k = Is_Head(Grammer[i][j - 1], c1);
			if (k == 1){
				FirVT[i][m++] = c1;        //����P->a�����뼯��
				FirVT[i][m] = '\r';
			}
			else if (k == 2){            //����P->A...��������
				c2 = Grammer[i][j + 1];
				if (c2 != '\r'&&c2 != '|'){
					FirVT[i][m++] = c2;        //����P->Aa��a���뼯��
					FirVT[i][m] = '\r';
				}
				int z = Find_Next(c1);
				if (z){
					if (z != i){   //�����Լ�����
						Get_FirstVT(z);
						Copy_FL(m, FirVT[i], FirVT[z]);
					}
				}
				else break;
			}
			else;
		}
		FirVT[i][++m] = '\n';
		FirVT[i][0] = ' ';
	}
	return true;
}

/*�õ�lastvt����*/
bool CLAN::Get_LastVT(int i)
{
	if (!LasVT[i][0]){      //û�����last����
		int m = 1, j = 4;
		char c1 = Grammer[i][j], c0;
		LasVT[i][m++] = Grammer[i][1];
		for (; c1 != '\r'; j++, c1 = Grammer[i][j])
		{
			int k = Is_Tail(c1, Grammer[i][j + 1]);
			if (k == 1){                 //����P->a�����뼯��
				LasVT[i][m++] = c1;
				LasVT[i][m] = '\r';
			}
			else if (k == 2){          //����P->aQ��������
				c0 = Grammer[i][j - 1];
				if (c0 != '\r'&&c0 != '|'){
					LasVT[i][m++] = c0;
					LasVT[i][m] = '\r';
				}
				int z = Find_Next(c1);
				if (z){
					if (z != i){     //�����Լ�����
						Get_LastVT(z);
						Copy_FL(m, LasVT[i], LasVT[z]);
					}
				}
				else break;
			}
			else;
		}
		LasVT[i][++m] = '\n';
		LasVT[i][0] = true;
	}
	return true;
}

/*���firstvt��lastvt��������*/
bool CLAN::Get_Two_Set()
{
	int i;
	for (i = 1; i <= count_line; i++)
	{
		if (!FirVT[i][0])Get_FirstVT(i);
		if (!LasVT[i][0])Get_LastVT(i);
	}
	return true;
}

/*Ѱ��������λ��*/
int CLAN::Find_Pos(char c1, char c2, int &row, int &col)
{
	int i;
	row = 0;
	col = 0;
	for (i = 1; PreForm[0][i] != '\r'; i++)
	{
		if (c1 == PreForm[0][i])row = i;
		if (c2 == PreForm[0][i])col = i;
	}
	if (row&&col)
		return 1;
	else
		return 0;
}

/*��i��FirVT�������ȹ�ϵ��*/
bool CLAN::Fill_FirVT_To_Pre(char c, int i)
{
	int row, col, j;
	for (j = 2; FirVT[i][j] != '\r'; j++)
	{
		if (Find_Pos(c, FirVT[i][j], row, col)){
			PreForm[row][col] = '<';
		}
		else
			cout << "Fill FirstVT Error" << endl;
	}
	return true;
}

/*/��i��LasVT�������ȹ�ϵ��*/
bool CLAN::Fill_LasVT_To_Pre(char c, int i)
{
	int row, col, j;
	for (j = 2; LasVT[i][j] != '\r'; j++)
	{
		if (Find_Pos(LasVT[i][j], c, row, col)){
			PreForm[row][col] = '>';
		}
		else
			cout << "Fill LastVT Error" << endl;
	}
	return true;
}

/*������ȹ�ϵ��*/
bool CLAN::Get_PreForm()
{
	int i, j, row, col, res, temp;
	char c1, c2, c3;
	Fill_BackSpace_To_Pre();
	for (i = 1; i <= count_line; i++)
	{
		c1 = Grammer[i][4];
		c2 = Grammer[i][5];
		for (j = 4; c2 != '\r'; j++, c1 = Grammer[i][j], c2 = Grammer[i][j + 1])
		{
			if (!Is_Upa(c1) && c1 != '|')  //iΪ�ս��
			{
				if (c2 != '|')
				{
					if (!Is_Upa(c2)){  //i+1ҲΪ�ս��
						res = Find_Pos(c1, c2, row, col);
						if (res)
							PreForm[row][col] = '=';
						else
							cout << "GetPreform Error" << endl;
					}
					else{     //i+1Ϊ���ս��
						temp = Find_Next(c2);
						Fill_FirVT_To_Pre(c1, temp);
					}
					c3 = Grammer[i][j + 2];
					if (c3 != '|'&&c3 != '\r'&&!Is_Upa(c3)){   //i+2Ϊ�ս��
						res = Find_Pos(c1, c3, row, col);
						if (res)
							PreForm[row][col] = '=';
						else
							cout << "GetPreform Error" << endl;
					}
				}
			}
			else{     //iΪ���ս��,i+1λ�ս��
				if (c1 != '|'&&c2 != '|'&&!Is_Upa(c2)){   //lastvt[c1]>c2
					temp = Find_Next(c1);
					Fill_LasVT_To_Pre(c2, temp);
				}
			}
		}
	}
	Fill_End_In_PreForm();
	return 1;
}

/*��ȡ�ļ�������Ԥ����,�ж��Ƿ���������ķ�*/
bool CLAN::Pre_Process(CString filepathname)
{
	ifstream infile(filepathname, ios::in);
	if (!infile){
		return false;
	}
	int i, j, pre = 1;
	char c;
	infile.get(c);
	PreForm[0][1] = '\r';    //��ʼ��
	for (i = 1; c != ';'; i++)
	{
		while (c == '\n')infile.get(c);  //������
		if (c == ';')
			break;
		Grammer[i][0] =' ';     //������־λ
		for (j = 1; c != '\n'; j++, infile.get(c))
		{
			while (c == ' ')infile.get(c);  //���ո�
			Grammer[i][j] = c;
			if (Is_Upa(Grammer[i][j - 1]) && Is_Upa(c))   //������������д��ĸ
				return false;
			if (Init_PreForm(j, pre, c))  //��ʼ�����ȹ�ϵ��
				++count_VT;
		}
		Grammer[i][j] = '\r';
		Grammer[i][j + 1] = '\n';
		FirVT[i][0] = 0;
		FirVT[i][2] = '\r';
		LasVT[i][0] = 0;
		LasVT[i][2] = '\r';
	}
	count_line = i - 1;
#ifdef DEBUG
	++count_VT;
	PreForm[0][count_VT] = '#';
	PreForm[count_VT][0] = '#';
	PreForm[0][count_VT+1] = '\r';
#endif
	infile.close();
	return true;
}

/*����ķ�*/
bool CLAN::Print_Grammer(CString &gra)
{
	gra = "\r\n";
	for (int i = 1; i <= count_line; i++)
		gra+= Grammer[i];
	gra+= "\r\n\r\n\r\n���ķ�����������ķ�\r\n";
	return true;
}

/*���LasVT*/
bool CLAN::Print_LastVT(CString &Las)
{
	Las = "\r\n";
	for (int i = 1; i <= count_line; i++)
	{
		Las += "LastVT(";
		Las += FirVT[i][1];
		Las += ")= {";
		for (int j = 1; LasVT[i][j] != '\r'; j++)
		{
			Las += LasVT[i][j];
			Las += "  ";
		}
		Las += "}";
		Las += "\r\n";
	}
	return true;
}

/*���FirstVT*/
bool CLAN::Print_FirsVT(CString &Fir)
{
	Fir = "\r\n";
	for (int i = 1; i <= count_line; i++)
	{
		Fir += "FistVT(";
		Fir += FirVT[i][1];
		Fir += ")= {";
		for (int j = 2; FirVT[i][j] != '\r'; j++)
		{
			Fir += FirVT[i][j];
			Fir += "  ";
		}
		Fir += "}";
		Fir += "\r\n";
	}
	return true;
}

/*������ȹ�ϵ��*/
bool CLAN::Print_PreForm(CString &pre)
{
	pre = "\r\n";
	for (int i = 0; i <= count_VT; i++)
	{
		for (int j = 0;  j <= count_VT; j++)
		{
			pre +=PreForm[i][j];
			pre += '\t';
		}
		pre+= "\r\n";
	}
	return true;
}

/*��Լ���̺���*/
bool CLAN::Include_Process(CString s1, CString &aim)
{
	int i, j,k=1,row,col;
	char a,op,q;
	bool ju = true;
	stack[k] = '#';
	aim = "����ջ\t��ϵ\t���봮\t����\r\n";
	for (i = 0, a = s1[i]; a != '#'&&ju; i++)
	{
		//����һ���ַ�����a��
		a = s1[i];
		if (!Is_Upa(stack[k])) //ջ��Ϊ�ս��
			j = k;
		else
			j = k - 1;
		if (!Find_Pos(stack[j], a, row, col)){
			ju = false;
			break;
		}  
		op = PreForm[row][col]; 
		while(op == '>')//��s[j]>aʱ
		{
			do{
				q = stack[j];
				if (!Is_Upa(stack[j - 1]))
					j = j - 1;
				else
					j = j - 2;
				if (!Find_Pos(stack[j], q, row, col)){
					ju = false;
					break;
				}	
			} while (PreForm[row][col] != '<');
			Copy_All(k, i, '>', s1,aim);
			aim += "\t��Լ\r\n";
			k = j + 1;
			stack[k] = 'N';
			if (!Find_Pos(stack[j], a, row, col)){
				ju = false;
				break;
			}
			op = PreForm[row][col];
		}
		if (op == '<' || op == '='){
			Copy_All(k, i, op, s1, aim);
			aim += "\t�ƽ�\r\n";
			k = k + 1;
			stack[k] = a;
		}
	}
	if (stack[k] == '#'&&ju)
		aim += "\r\n\r\n�÷��Ŵ�������������ķ�\r\n";
	else
		aim += "\r\n\r\n�÷��Ŵ���������������ķ�\r\n";
	return true;
}

/*��������*/
void CLAN::Copy_All(int st,int ss, char op,CString s1, CString &aim)
{
	int j ;
	for (j = 1; j <= st; j++)
		aim +=stack[j];
	aim += "\t";
	aim += op;
	aim+="\t";
	for (j = ss; s1[j] != '\0'; j++)
		aim += s1[j];
}

/*��װ��Ĵ������̺���*/
bool CLAN::Main_Function(CString  filepathname, CString &gra, CString &fir, CString &las, CString &pre )
{
	if (!Pre_Process(filepathname)){  //Ԥ����
		gra = "���ķ�������������ķ�\r\n";
	}
	else{
		Get_Two_Set();      //�õ�firsvt��lastvt
		Get_PreForm();    //������ȹ�ϵ��
		Print_FirsVT(fir);
		Print_LastVT(las);
		Print_Grammer(gra);
		Print_PreForm(pre);
	}
	return true;
}