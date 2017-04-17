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
	cout<<"\t\t        ���Ż������      "<<endl;
	cout<<"\t\t ============================="<<endl;
	cout<<"\t\t         1.��ƻ�����       "<<endl;
	cout<<"\t\t         2.��ﱸ����       "<<endl;
	cout<<"\t\t         3.����۹���       "<<endl;
	cout<<"\t\t         0.�˳�               "<<endl;
	cout<<"\t\t ============================="<<endl;
	cout<<"\t\t    ��ѡ��";
}
void Activity::menufirst1()
{
	system("cls");
	cout<<"\t\t        ��ƻ�����      "<<endl;
	cout<<"\t\t ========================="<<endl;
	cout<<"\t\t         1.���¼       "<<endl;
	cout<<"\t\t         2.��������       "<<endl;
	cout<<"\t\t         3.�ؼ�·��       "<<endl;
	cout<<"\t\t         0.�˳�           "<<endl;
	cout<<"\t\t ========================="<<endl;
	cout<<"\t\t    ��ѡ��";
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
	if ( n != 0 )  cout<<"�㷸���ˣ�����"<<endl;
}
void Activity::initGraph()    //����һ����ƻ������ͼ�ṹ
{    int i;
	cout<<"�����¼�����";cin>>activity.vexnum;
	cout<<"������������";cin>>activity.arcnum;

	cout<<"�����¼������Ϣ"<<endl;
	for (int i = 0; i < activity.vexnum; i++ )
	{
		cout<<"--------------"<<endl;
		cout<<"�¼���ţ�";cin>>activity.vertices[i].num;
		cout<<"�¼����ƣ�";cin>>activity.vertices[i].name;
		cout<<"�¼�������";cin>>activity.vertices[i].data;
		activity.vertices[i].fistarc = NULL;
	}
	int z = 0;
	for (int j = 0;j < activity.arcnum ; ++j )
	{
		string v1,v2;
		cout<<"================"<<endl;
		cout<<"�����¼���ţ�";   cin>>v1;
		cout<<"����¼���ţ�";   cin>>v2;
			

		int m;
		i = LocateVex(activity,v1);
		m = LocateVex(activity,v2);
        cout<<"���¼�"<<activity.vertices[i].num<<"���¼�"<<activity.vertices[m].num<<"����ʱ�䣨�ʱ�䣩��";

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


bool TopuiogicalSort(Graph activity,int topo[])  //�����������򣬿����Է���
{
	ArcNode *p;//����洢ͼ��ÿ��������ȵ�һά��������d
 
	int n = activity.vexnum;
    int* d=new int[n];
    for(int i=0; i<n; i++)     d[i]=0;   //��������d�еĶ�ӦԪ��ͳ�Ƴ�ÿ����������

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

void showTopuiogicalSort(Graph activity,int topo[])  //�����������򣬿����Է���
{
	ArcNode *p;//����洢ͼ��ÿ��������ȵ�һά��������d
 
	int n = activity.vexnum;
    int* d=new int[n];
    for(int i=0; i<n; i++)     d[i]=0;   //��������d�еĶ�ӦԪ��ͳ�Ƴ�ÿ����������

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
			cout<<"���:"<<activity.vertices[p->adjplace].num<<endl;
			if (d[i] == 0)  Push(s,k);
			p = p->nextarc;
		}
	}
	if (m < activity.vexnum)  cout<<"��������ʧ�ܣ�"<<endl;
	else  cout<<"��������ɹ���"<<endl;;
}

void CriticalPath(Graph activity)    //���ؼ�·��
{
	int topo[MAXSIZE],ve[MAXSIZE],vl[MAXSIZE];

	if (!TopuiogicalSort(activity,topo))  
	{
		cout<<"��������ʧ�ܣ��ؼ�·���޷���⣡"<<endl;
		system("pause");
	    system("cls");
		return ;
	}
	
	int n = activity.vexnum,k;
	for (int i = 0 ; i < n ;i++)   ve[i] = 0;  //��ÿһ���¼�������ʱ������
	/*------����������˳����ÿһ���¼�����������ʱ��-----*/
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

	for (int i = 0 ; i < n ;i++)   vl[i] = ve[n-1];  //��ÿһ���¼�������ʱ������
    /*------������������˳����ÿһ���¼����������ʱ��-----*/
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

	cout<<"����������¼����翪ʼʱ�������ʼʱ��:"<<endl<<endl;
	for (int i = 0 ; i < n ; i ++)
	{
		cout<<"�����¼�"<<activity.vertices[i].num<<"���翪ʼʱ��:"<<ve[i]<<"  "<<"����ʼʱ��:"<<vl[i]<<endl;
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
				cout<<"�ؼ�·����"<<endl;
				cout<<setw(20)<<"�¼����"<<setw(20)<<"�¼�����"<<setw(20)<<"�¼�����"<<endl;
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
