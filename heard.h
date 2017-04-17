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
};   //时间整合 
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
// 结构体存放数据  使用双向链表 
class Member{
public:
	//int InitList(ppList &L);
	int GrateList(ppList &L); //前插法创建 
	int  Llength(ppList &L);  //计算个数 
	int InsertList (ppList &L);
	int display_member(ppList &L);
	//文件 
	void filein(ppList &L);
	void fileout(ppList &L);
	//成员等级
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
}PTNode;//采用双亲表示法中树的结点类型

#define MAX_TREE_SIZE 100
typedef struct CNode
{
	int child;
	struct CNode *nextChild;
}CNode,*childPtr;//孩子链表表结点及其指针类型

typedef struct
{
	TElemType data;
	int parent;
	childPtr firstChild;
}CTNode;//带双亲的孩子链表头结点类型

typedef struct
{
	CTNode nodes[MAX_TREE_SIZE];
	int nodeNum, root;
}CTree;//带双亲的孩子链表表示法的社团分类目录类型

struct  zanzhu
{  string name;
   string fuzeren;
   string wangzhi;
   string jianjie;
   string shetuan;
   string shetuan2;
};
