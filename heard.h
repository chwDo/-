#include <iostream>
#include <ctime>
#include <windows.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <windows.h>

#include <fstream>
#include <sstream>
#include <stdio.h>
#define OK 1
#define ERROR 0
#define VOERFLOW -2

using namespace std;

struct time_1{
	int second;
	int minute;
	int hour;
	int day;
	int mouth;
	int year;
};   //ʱ������ 
struct Data
{	string ID;
	string name;
	string sex;
	string class_n;
    string telephonenumber;
	string address;	
	string shetuan;
	string shenfen;
	time_1  time_p;
	
	int  integral;	
    int  rank;
    
};
typedef struct ppNode{
     Data  data;
	struct ppNode *next;
	struct ppNode *prior;
	  //changdu
}ppNode,*ppList;
// �ṹ��������  ʹ��˫������ 
class Member{
public:
	//int InitList(ppList &L);
	int GrateList(ppList &L); //ǰ�巨���� 
	int  Llength(ppList &L);  //������� 
	int InsertList (ppList &L);
	int display_member(ppList &L);
	//�ļ� 
	void filein(ppList &L);
	void fileout(ppList &L);
	//��Ա�ȼ�
	int    sort_2(ppList &L,ppList p);
	 int    sort_1(ppList &L,ppList p);
	 int    change(ppList &L);
	 int   add_integral(ppList &L);
	 int   delete_ppList(ppList &L);
	 int   rankquery(ppList &L); 
	 double rankaverage(ppList &L);
	 int  ranksort(ppList &L);
	 int  rankchange(ppList &L);
private:
   ppList L;
};
//-------------------------------------------------------------------
typedef struct
{
	char name[20];
	char name_p[20];
	char xingzhi[20];
	char kouhao[50];
	char zongzhi[200];
	char zhangcheng[200];
	
}BCType;

typedef BCType TElemType;

typedef struct
{
	TElemType data;
	int parent;
}PTNode;//����˫�ױ�ʾ�������Ľ������

#define MAX_TREE_SIZE 100
typedef struct CNode
{
	int child;
	struct CNode *nextChild;
}CNode,*childPtr;//����������㼰��ָ������

typedef struct
{
	TElemType data;
	int parent;
	childPtr firstChild;
}CTNode;//��˫�׵ĺ�������ͷ�������

typedef struct
{
	CTNode nodes[MAX_TREE_SIZE];
	int nodeNum, root;
}CTree;//��˫�׵ĺ��������ʾ�������ŷ���Ŀ¼����

struct  zanzhu
{  string name;
   string fuzeren;
   string wangzhi;
   string jianjie;
   string shetuan;
   string shetuan2;
};
