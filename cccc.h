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
���ڽӱ��ʾ��й���Ϣ
--------------------*/
typedef struct ArcNode   //�߽ڵ�(��ɻʱ��)
{
	int adjplace;               //�ñ�ָ��Ķ���λ��
	struct ArcNode *nextarc;    //��һ���ߵ�ָ��
	int time;                   //�ߵ������Ϣ����ɻʱ�䣩
	int num;                    //����
}ArcNode;

typedef struct VNode           //���㣨�¼���
{
	string data;         //������Ϣ���������
	string name;         //�����
	string num;          //����
	ArcNode *fistarc;    //����ָ��ĵ�һ����

}VNode,ADjlist[Mnum];

typedef struct     
{
	ADjlist vertices;    //�ڽӱ�
	int vexnum,arcnum;    //ͼ�ĵ�ǰ�������ͱ���
}Graph;

//ջ�Ĳ���
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
	/*�йػ�ƻ�����*/
	void initGraph();
	void fileSave();
	friend bool TopuiogicalSort(Graph activity,int topo[]);
	friend void showTopuiogicalSort(Graph activity,int topo[]);
	friend void CriticalPath(Graph activity);
	friend int LocateVex(Graph G,string v1);

	/*У԰����ϵͳ*/
	
	/*����۹���*/


	//������
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
void search(); // ��ѯ������Ϣ 
char SearchMenu();
class student 
{ 
  string name[20]; 
  string secret[20]; 
};
class student stu[N];


