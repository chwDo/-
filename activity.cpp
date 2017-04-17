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

void Activity::contolfirst()
{
	int choise;
	
    menufirst();
    cin>>choise;

	while(choise != 0)
	{
         switch(choise)
		 {
         	case 1:contolfirst1();break;
        	case 2:
				break;
        	case 3:break; 
		 }
		 menufirst();
		 cin>>choise;
	}

}

void Activity::menufirst()
{
	system("cls");
	cout<<"\t\t        社团活动管理部分      "<<endl;
	cout<<"\t\t ============================="<<endl;
	cout<<"\t\t         1.活动计划管理       "<<endl;
	cout<<"\t\t         2.活动筹备管理       "<<endl;
	cout<<"\t\t         3.活动评价管理       "<<endl;
	cout<<"\t\t         0.退出               "<<endl;
	cout<<"\t\t ============================="<<endl;
	cout<<"\t\t    请选择：";
}
void Activity::menufirst1()
{
	system("cls");
	cout<<"\t\t        活动计划管理      "<<endl;
	cout<<"\t\t ========================="<<endl;
	cout<<"\t\t         1.活动记录       "<<endl;
	cout<<"\t\t         2.拓扑排序       "<<endl;
	cout<<"\t\t         3.关键路径       "<<endl;
	cout<<"\t\t         0.退出           "<<endl;
	cout<<"\t\t ========================="<<endl;
	cout<<"\t\t    请选择：";
}

int LocateVex(Graph G,string v1)
{
	int n=0;
	for (int i = 0; i < G.vexnum; i++ )
	{
		if (v1 == G.vertices[i].num)  
		{
			n=1;
			return i;
		}
	}
	if ( n != 0 )  cout<<"你犯错了！！！"<<endl;
}
void Activity::initGraph()    //创建一个活动计划管理的图结构
{    int i;
	cout<<"输入事件数：";cin>>activity.vexnum;
	cout<<"输入活动的数量：";cin>>activity.arcnum;

	cout<<"输入事件相关信息"<<endl;
	for (int i = 0; i < activity.vexnum; i++ )
	{
		cout<<"--------------"<<endl;
		cout<<"事件编号：";cin>>activity.vertices[i].num;
		cout<<"事件名称：";cin>>activity.vertices[i].name;
		cout<<"事件描述：";cin>>activity.vertices[i].data;
		activity.vertices[i].fistarc = NULL;
	}
	int z = 0;
	for (int j = 0;j < activity.arcnum ; ++j )
	{
		string v1,v2;
		cout<<"================"<<endl;
		cout<<"先行事件编号：";   cin>>v1;
		cout<<"后继事件编号：";   cin>>v2;
			

		int m;
		i = LocateVex(activity,v1);
		m = LocateVex(activity,v2);
        cout<<"从事件"<<activity.vertices[i].num<<"到事件"<<activity.vertices[m].num<<"所用时间（活动时间）：";

		ArcNode *p;
		p = new ArcNode;
		p->adjplace = m;
		p->nextarc = activity.vertices[i].fistarc;
		p->num = z;
		cin>>p->time;
		activity.vertices[i].fistarc = p;
		z++;
	}
	system("pause");
	system("cls");
}



status InitStack(sqStack &s)
{
	s.base=new int[MAXSIZE];
	if (!s.base)   exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=MAXSIZE;
    return OK;
}

status Push(sqStack &s,int e)
{
	if (s.top-s.base==s.stacksize)  return ERROR;
	*s.top++=e;
	return OK;
}

status Pop(sqStack &s,int &e)
{
	if(s.base==s.top)  return ERROR;
	e=*--s.top;
	return OK;
}
int StackEmpty(sqStack s)
{
	if(s.base==s.top)  return true;
	return false;
}


bool TopuiogicalSort(Graph activity,int topo[])  //进行拓扑排序，可行性分析
{
	ArcNode *p;//定义存储图中每个顶点入度的一维整型数组d
 
	int n = activity.vexnum;
    int* d=new int[n];
    for(int i=0; i<n; i++)     d[i]=0;   //利用数组d中的对应元素统计出每个顶点的入度

    for(int i=0; i<n; i++) 
    {
	   p=activity.vertices[i].fistarc;
       while(p!=NULL)
	   {
          int j=p->adjplace;
          d[j]++;
	      p=p->nextarc;
	   }
    }

    sqStack s;
	InitStack(s);

	for (int i = 0; i < activity.vexnum; i++)  	if (! d[i] )  Push(s,i);
     int i;
	int m = 0;
	while (! StackEmpty(s))
	{
		Pop(s,i);
		topo[m] = i;
		++m;

		ArcNode *p = activity.vertices[i].fistarc;

		while (p != NULL)
		{
			int k;
			k = p->adjplace;
			--d[k];
			if (d[i] == 0)  Push(s,k);
			p = p->nextarc;
		}
	}
	if (m < activity.vexnum)  return false;
	else  return true;
}

void showTopuiogicalSort(Graph activity,int topo[])  //进行拓扑排序，可行性分析
{
	ArcNode *p;//定义存储图中每个顶点入度的一维整型数组d
 
	int n = activity.vexnum;
    int* d=new int[n];
    for(int i=0; i<n; i++)     d[i]=0;   //利用数组d中的对应元素统计出每个顶点的入度

    for(int i=0; i<n; i++) 
    {
	   p=activity.vertices[i].fistarc;
       while(p!=NULL)
	   {
          int j=p->adjplace;
          d[j]++;
	      p=p->nextarc;
	   }
    }
    sqStack s;
	InitStack(s);

	for (int i = 0; i < activity.vexnum; i++)  	if (! d[i] )  Push(s,i);
    int i;
	int m = 0;
	while(!StackEmpty(s))
	{
		Pop(s,i);
		topo[m] = i;
		++m;

		ArcNode *p = activity.vertices[i].fistarc;

		while (p != NULL)
		{
			int k;
			k = p->adjplace;
			--d[k];
			cout<<"输出:"<<activity.vertices[p->adjplace].num<<endl;
			if (d[i] == 0)  Push(s,k);
			p = p->nextarc;
		}
	}
	if (m < activity.vexnum)  cout<<"拓扑排序失败！"<<endl;
	else  cout<<"拓扑排序成功！"<<endl;;
}

void CriticalPath(Graph activity)    //求解关键路径
{
	int topo[MAXSIZE],ve[MAXSIZE],vl[MAXSIZE];

	if (!TopuiogicalSort(activity,topo))  
	{
		cout<<"拓扑排序失败，关键路径无法求解！"<<endl;
		system("pause");
	    system("cls");
		return ;
	}
	
	int n = activity.vexnum,k;
	for (int i = 0 ; i < n ;i++)   ve[i] = 0;  //给每一个事件的最早时间置零
	/*------按拓扑排序顺序求每一个事件发生的最早时间-----*/
	for (int i =0 ; i < n ; i ++)
	{
	    k = topo[i];
        ArcNode * p =activity.vertices[k].fistarc;
		while (p != NULL)
		{
			int j = p->adjplace;
			if (ve[j] < ve[k] + p->time )  ve[j] = ve[k]+p->time;
			p= p->nextarc;
		}
	}

	for (int i = 0 ; i < n ;i++)   vl[i] = ve[n-1];  //给每一个事件的最早时间置零
    /*------按逆拓扑排序顺序求每一个事件发生的最迟时间-----*/
	for (int i = n - 1; i >= 0 ; i --)
	{

		k = topo[i];
        ArcNode * q =activity.vertices[k].fistarc;

		while (q != NULL)
		{
			int j = q->adjplace;
			if (vl[k] > vl[j] - q->time )  vl[k] = vl[j] - q->time;
			q= q->nextarc;
		}
	}

	cout<<"计算各顶点事件最早开始时间和最晚开始时间:"<<endl<<endl;
	for (int i = 0 ; i < n ; i ++)
	{
		cout<<"顶点事件"<<activity.vertices[i].num<<"最早开始时间:"<<ve[i]<<"  "<<"最晚开始时间:"<<vl[i]<<endl;
	}

	for( int i = 0 ; i < n; i++)
	{
		ArcNode *r = activity.vertices[i].fistarc;
	
		while (r != NULL)
		{
			
			int j = r->adjplace;
		
			int e,l;
			e = ve[i];
			l = vl[j] - r->time;
			
			static int m_temp = 0;
			if (m_temp == 0)  
			{
				cout<<"关键路径："<<endl;
				cout<<setw(20)<<"事件编号"<<setw(20)<<"事件名称"<<setw(20)<<"事件描述"<<endl;
				m_temp++;
			}
			char tag;
			if (e == l) 
	        cout<<setw(20)<<activity.vertices[i].num<<setw(20)<<activity.vertices[i].name<<setw(20)<<activity.vertices[i].data<<endl;
			r= r->nextarc;
		}
	}
	system("pause");
	system("cls");
}
void Activity::contolfirst1()
{
	int topo[MAXSIZE];
	int choise;
    menufirst1();
    cin>>choise;

	while(choise != 0)
	{
         switch(choise)
		 {
         	case 1:initGraph();break;
        	case 2:showTopuiogicalSort(activity,topo);	system("pause");   system("cls");	break;
        	case 3:CriticalPath(activity);break; 
		 }
		 menufirst1();
		 cin>>choise;
	}
	
}

int main()
{
	Activity a;

	a.contolfirst();
	return 0;
}
