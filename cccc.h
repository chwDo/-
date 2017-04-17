#include <iostream>
#include <string>
#include <iomanip>

#define Maxnum 100
#define Mnum 100
#define MAXEVA 100
#define Maxint 10000

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2

//-----------------------------------------------------

using namespace std;

/*-----------------
用邻接表表示活动有关信息
--------------------*/
typedef struct ArcNode   //边节点(完成活动时间)
{
	int adjplace;               //该边指向的顶点位置
	struct ArcNode *nextarc;    //下一条边的指针
	int time;                   //边的相关信息（完成活动时间）
	int num;                    //活动编号
}ArcNode;

typedef struct VNode           //顶点（事件）
{
	string data;         //顶点信息（活动描述）
	string name;         //活动名称
	string num;          //活动编号
	ArcNode *fistarc;    //顶点指向的第一条边

}VNode,ADjlist[Mnum];

typedef struct     
{
	ADjlist vertices;    //邻接表
	int vexnum,arcnum;    //图的当前顶点数和边数
}Graph;

//栈的操作
typedef int status;

typedef struct
{
	int *base;
	int *top;
	int stacksize;
}sqStack;


class Activity
{
public:
	/*有关活动计划管理*/
	void initGraph();
	void fileSave();
	friend bool TopuiogicalSort(Graph activity,int topo[]);
	friend void showTopuiogicalSort(Graph activity,int topo[]);
	friend void CriticalPath(Graph activity);
	friend int LocateVex(Graph G,string v1);

	/*校园导航系统*/
	
	/*活动评价管理*/


	//控制器
	void contolfirst();
	void menufirst();

	void contolfirst1();
	void menufirst1();

private:
	Graph activity;

};
#include<conio.h>
#define N 10
	int n=1;
#define Max 32767
#define NUM 16
using namespace std;
typedef struct ArcCell
{ 
 int adj;
  char *info;
}ArcCell; 

typedef struct VertexType
{
  int number;  
  string sight; 
  string description; 
}VertexType; 
typedef struct
{
  VertexType vex[NUM]; 
  ArcCell arcs[NUM][NUM];  
  int vexnum,arcnum;
}MGraph;

MGraph G;
int P[NUM][NUM];
long int D[NUM];  
void CreateUDN(int v,int a); 
void introduce();
void ShortestPath(int num);
void output(int sight1,int sight2);
char Menu();
void search(); // 查询景点信息 
char SearchMenu();
class student 
{ 
  string name[20]; 
  string secret[20]; 
};
class student stu[N];


