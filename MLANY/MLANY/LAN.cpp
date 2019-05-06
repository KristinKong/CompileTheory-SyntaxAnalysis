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

/*优先关系表多余部分填空格*/
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
/*复制集合*/
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
			c1[m] = '\r';     //结束符后移一位
		}
	}
	return true;
}

/*判断是否两个连续大写字母*/
bool CLAN::Is_Upa(char c1)
{
	if (c1 >= 'A'&&c1 <= 'Z')
		return true;
	else return false;
}

/*查看是否P->a|Qa的模式*/
int CLAN::Is_Head(char c1, char c2)
{
	if (c1 == '>' || c1 == '|'){
		if (!Is_Upa(c2))       //加入firstvt
			return 1;
		else
			return 2;         //迭代求
	}
	else
		return 3;    //跳到下一个
}

/*查看是否P->a|aQ的模式*/
int CLAN::Is_Tail(char c1, char c2)
{
	if (c2 == '|' || c2 == '\r'){
		if (!Is_Upa(c1))      //加入lastvt 
			return 1;
		else
			return 2;         //迭代求
	}
	else
		return 3;    //跳到下一个
}

/*把#号填入优先关系表*/
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
			/*填小于*/
			res = Is_Head(c1, c2);
			if (res == 1)  {//c1为头，c2为终结符,将#<c2填入表中
				temp = Find_Pos('#', c2, row, col);
				if (temp)
					PreForm[row][col] = '<';
			}
			else if (res == 2){//c1为头，c2为非终结符,将#<first（c2）填入表中
				temp = Find_Next(c2);
				Fill_FirVT_To_Pre('#', temp);
				c3 = Grammer[i][j + 2];
				if (c3 != '|' || c3 != '\r'){  //c3为终结符,置#<c3
					Find_Pos('#', c3, row, col);
					PreForm[row][col] = '<';
				}
			}
			else;

			/*填大于*/
			res = Is_Tail(c1, c2);
			if (res == 1)  {//c1为终结符,c2为尾，将c1>#填入表中
				temp = Find_Pos(c1, '#', row, col);
				if (temp)
					PreForm[row][col] = '>';
			}
			else if (res == 2){//c1为非终结符,c2为尾，将last(c1)>#填入表中
				temp = Find_Next(c1);
				Fill_LasVT_To_Pre('#', temp);
				c3 = Grammer[i][j-1]; 
				if (c3 != '|' || c3 != '\r'){  //c0为终结符,置c0>#
					Find_Pos(c3, '#', row, col);
					PreForm[row][col] = '>';
				}
			}
			else;
		}
	}
	PreForm[count_VT][count_VT] = '='; //##填等于
	return 1;
}

/*复制终结符到优先关系表*/
bool  CLAN::Init_PreForm(int j, int &m, char c)
{
	bool cop;
	int i;
	if (!Is_Upa(c) && c != '|'&&j > 3){      //c是有效终结符
		cop = true;
		for (i = 0; PreForm[0][i] != '\r'; i++)
		{
			if (PreForm[0][i] == c)
				cop = false;
		}
		if (cop){
			PreForm[0][m] = c;
			PreForm[m++][0] = c;
			PreForm[0][++i] = '\r';     //结束符后移一位
			return true;
		}
	}
	return false;
}
/*寻找下一个求语法的开始*/
int CLAN::Find_Next(char c)
{
	for (int i = 1; i <= count_line; i++)
	if (c == Grammer[i][1])
		return i;
	return 0;
}

/*得到firstvt集合*/
bool CLAN::Get_FirstVT(int i)
{
	if (!FirVT[i][0]){      //没有求过first集合
		int m = 1, j = 4;
		char c1 = Grammer[i][j], c2;
		FirVT[i][m++] = Grammer[i][1];
		for (; c1 != '\r'; j++, c1 = Grammer[i][j])
		{
			int k = Is_Head(Grammer[i][j - 1], c1);
			if (k == 1){
				FirVT[i][m++] = c1;        //满足P->a，加入集合
				FirVT[i][m] = '\r';
			}
			else if (k == 2){            //满足P->A...，迭代求
				c2 = Grammer[i][j + 1];
				if (c2 != '\r'&&c2 != '|'){
					FirVT[i][m++] = c2;        //满足P->Aa，a加入集合
					FirVT[i][m] = '\r';
				}
				int z = Find_Next(c1);
				if (z){
					if (z != i){   //是它自己则不做
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

/*得到lastvt集合*/
bool CLAN::Get_LastVT(int i)
{
	if (!LasVT[i][0]){      //没有求过last集合
		int m = 1, j = 4;
		char c1 = Grammer[i][j], c0;
		LasVT[i][m++] = Grammer[i][1];
		for (; c1 != '\r'; j++, c1 = Grammer[i][j])
		{
			int k = Is_Tail(c1, Grammer[i][j + 1]);
			if (k == 1){                 //满足P->a，加入集合
				LasVT[i][m++] = c1;
				LasVT[i][m] = '\r';
			}
			else if (k == 2){          //满足P->aQ，迭代求
				c0 = Grammer[i][j - 1];
				if (c0 != '\r'&&c0 != '|'){
					LasVT[i][m++] = c0;
					LasVT[i][m] = '\r';
				}
				int z = Find_Next(c1);
				if (z){
					if (z != i){     //是它自己则不做
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

/*求得firstvt和lastvt两个集合*/
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

/*寻找填入表的位置*/
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

/*将i的FirVT填入优先关系表*/
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

/*/将i的LasVT填入优先关系表*/
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

/*获得优先关系表*/
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
			if (!Is_Upa(c1) && c1 != '|')  //i为终结符
			{
				if (c2 != '|')
				{
					if (!Is_Upa(c2)){  //i+1也为终结符
						res = Find_Pos(c1, c2, row, col);
						if (res)
							PreForm[row][col] = '=';
						else
							cout << "GetPreform Error" << endl;
					}
					else{     //i+1为非终结符
						temp = Find_Next(c2);
						Fill_FirVT_To_Pre(c1, temp);
					}
					c3 = Grammer[i][j + 2];
					if (c3 != '|'&&c3 != '\r'&&!Is_Upa(c3)){   //i+2为终结符
						res = Find_Pos(c1, c3, row, col);
						if (res)
							PreForm[row][col] = '=';
						else
							cout << "GetPreform Error" << endl;
					}
				}
			}
			else{     //i为非终结符,i+1位终结符
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

/*读取文件并进行预处理,判断是否算符优先文法*/
bool CLAN::Pre_Process(CString filepathname)
{
	ifstream infile(filepathname, ios::in);
	if (!infile){
		return false;
	}
	int i, j, pre = 1;
	char c;
	infile.get(c);
	PreForm[0][1] = '\r';    //初始化
	for (i = 1; c != ';'; i++)
	{
		while (c == '\n')infile.get(c);  //除换行
		if (c == ';')
			break;
		Grammer[i][0] =' ';     //辅助标志位
		for (j = 1; c != '\n'; j++, infile.get(c))
		{
			while (c == ' ')infile.get(c);  //除空格
			Grammer[i][j] = c;
			if (Is_Upa(Grammer[i][j - 1]) && Is_Upa(c))   //有两个连续大写字母
				return false;
			if (Init_PreForm(j, pre, c))  //初始化优先关系表
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

/*输出文法*/
bool CLAN::Print_Grammer(CString &gra)
{
	gra = "\r\n";
	for (int i = 1; i <= count_line; i++)
		gra+= Grammer[i];
	gra+= "\r\n\r\n\r\n该文法是算符优先文法\r\n";
	return true;
}

/*输出LasVT*/
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

/*输出FirstVT*/
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

/*输出优先关系表*/
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

/*规约过程函数*/
bool CLAN::Include_Process(CString s1, CString &aim)
{
	int i, j,k=1,row,col;
	char a,op,q;
	bool ju = true;
	stack[k] = '#';
	aim = "符号栈\t关系\t输入串\t动作\r\n";
	for (i = 0, a = s1[i]; a != '#'&&ju; i++)
	{
		//读入一个字符串到a中
		a = s1[i];
		if (!Is_Upa(stack[k])) //栈顶为终结符
			j = k;
		else
			j = k - 1;
		if (!Find_Pos(stack[j], a, row, col)){
			ju = false;
			break;
		}  
		op = PreForm[row][col]; 
		while(op == '>')//当s[j]>a时
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
			aim += "\t规约\r\n";
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
			aim += "\t移进\r\n";
			k = k + 1;
			stack[k] = a;
		}
	}
	if (stack[k] == '#'&&ju)
		aim += "\r\n\r\n该符号串满足算符优先文法\r\n";
	else
		aim += "\r\n\r\n该符号串不满足算符优先文法\r\n";
	return true;
}

/*复制所有*/
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

/*封装后的处理流程函数*/
bool CLAN::Main_Function(CString  filepathname, CString &gra, CString &fir, CString &las, CString &pre )
{
	if (!Pre_Process(filepathname)){  //预处理
		gra = "该文法不是算符优先文法\r\n";
	}
	else{
		Get_Two_Set();      //得到firsvt和lastvt
		Get_PreForm();    //获得优先关系表
		Print_FirsVT(fir);
		Print_LastVT(las);
		Print_Grammer(gra);
		Print_PreForm(pre);
	}
	return true;
}