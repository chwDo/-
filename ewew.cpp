#include "cccc.h"

int show_tu() 
{ int v0,v1,i;
  char xxx;
  CreateUDN(NUM,16);
  do
  { xxx=Menu();
    switch(xxx)
	{
      case'1':
        system("cls");
	    introduce();
        cout<<G.vex[0].description;
        getchar();
        getchar();
        break;
      case '2':
       for(i=1;i<NUM;i++)
	   { 
      	 cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // ��������б� 
	   }
        cout<<"�밴�س�������...\n";
        getchar();
        getchar();
        break;		
      case '3':
		search();
        break;
      case '4':
        system("cls");
       for(i=1;i<NUM;i++)
	   { 
      	cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // ��������б� 
	   }
        cout<<"��ѡ����㾰�㣨1��15����";
        cin>>v0;
        cout<<"��ѡ���յ㾰�㣨1��15����";
        cin>>v1;
        ShortestPath(v0); 
        output(v0,v1);
        cout<<"�밴�س�������...\n";
        getchar();
        getchar();
        break;
	}
  }
  while(xxx!='5');
   system("cls");
}

char Menu() // ���˵� //
{  char c;
   int flag;
  
   do
   {   system("cls");
       flag=1;
      introduce();                             
      cout<<"                      1.ѧУ���      "<<endl;                    
	  cout<<"                      2.��ʾ�����ı�� "<<endl;                
      cout<<"                      3.�鿴�����ľ�����Ϣ "<<endl;	  
      cout<<"                      4.����·�����ȼ��ҳ����·��"<<endl;        
      cout<<"                      5.�˳� ��"<<endl;                                                       
      cout<<"               ����������ѡ��"<<endl;
      scanf("%c",&c);
      if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6')
        flag=0;
   } while(flag);
     return c;
}

char SearchMenu() // ��ѯ�Ӳ˵� 
{  char c;
   int flag;
   do
   {  flag=1;
      system("cls");
      introduce();
      cout<<"               *************************************\n";
      cout<<"               * ��\n";                           
      cout<<"               * 1�����վ����Ų�ѯ ��\n";       
      cout<<"               * 2�����վ������Ʋ�ѯ ��\n";       
      cout<<"               * 0������ ��\n";                   
      cout<<"               * ��\n";                           
      cout<<"               *************************************\n";
      cout<<"               ����������ѡ��";
      scanf("%c",&c);
      if(c=='1'||c=='2'||c=='0')
        flag=0;
   }  while(flag);
      return c;
}

void search() // ��ѯ������Ϣ 
{  int num;
   int i;
   char c;
   char name[20];
   do
   {  system("cls");
      c=SearchMenu();
      switch (c)
	  {
        case '1': 
          system("cls");
          introduce();
          for(i=1;i<NUM;i++)
		  { 
	        cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // ��������б� 
		  }
          cout<<"                           "<<"��������Ҫ���ҵľ����ţ�";
          scanf("%d",&num);
          for(i=0;i<NUM;i++)
		  {
            if(num==G.vex[i].number)
			{
              cout<<"                           "<<"��Ҫ���Ҿ�����Ϣ����:";
              cout<<"                           "<<G.vex[i].description;
              cout<<"                    �����������...";
              getchar();
              getchar();
              break;
			}
		  }
              if(i==NUM)
			  {
                cout<<"                    û���ҵ���";
                cout<<"                    ���λس�����...";
                getchar();
                getchar();
			  } break;
        case '2':
          system("cls");
          introduce();
          cout<<"                           "<<"��������Ҫ���ҵľ������ƣ�";
          scanf("%s",name);
          for(i=1;i<NUM;i++)
		  {
            if(name!=G.vex[i].sight)
			{
              cout<<"                    ��Ҫ���Ҿ�����Ϣ����:";
              cout<<"                    "<<G.vex[i].description;
              cout<<"                    ���س�������...";
              getchar();
              getchar();
              break;
			}
		  }
              if(i==NUM)
			  {
                cout<<"                    û���ҵ���";
                cout<<"                    ���س�������...";
                getchar();
                getchar();
			  } break;
	  }
   }while(c!='0');
    getchar();
}

void CreateUDN(int v,int a) 
{ int i,j;
  G.vexnum=v; 
  G.arcnum=a;
  for(i=1;i<G.vexnum;++i) 
    G.vex[i].number=i; 
    G.vex[0].sight="ѧУ���";
    G.vex[1].sight="�ϴ���";
    G.vex[2].sight="������";
    G.vex[3].sight="��ѧ�������";
    G.vex[4].sight="ͼ���";
    G.vex[5].sight="��®";
    G.vex[6].sight="���¹㳡";
    G.vex[7].sight="��®";
    G.vex[8].sight="��®";
    G.vex[9].sight="��®";
    G.vex[10].sight="��һ��ѧ¥";
    G.vex[11].sight="�ڶ���ѧ¥";
    G.vex[12].sight="�̹�����";
    G.vex[13].sight="ѧ��һʳ��";
    G.vex[14].sight="ѧ����ʳ��";
    G.vex[15].sight="ѧ����ʳ��";
    for(i=1;i<G.vexnum;++i)
    {
      for(j=1;j<G.vexnum;++j) 
	  {
        G.arcs[i][j].adj=Max;
        G.arcs[i][j].info=NULL;
	  }
	}
      G.arcs[1][4].adj=G.arcs[4][1].adj=1300;
      G.arcs[1][6].adj=G.arcs[6][1].adj=200;            
      G.arcs[2][3].adj=G.arcs[3][2].adj=500;
      G.arcs[2][8].adj=G.arcs[8][2].adj=100;
      G.arcs[3][5].adj=G.arcs[5][3].adj=600;
      G.arcs[3][6].adj=G.arcs[6][3].adj=700;
      G.arcs[4][6].adj=G.arcs[6][4].adj=350;
      G.arcs[4][7].adj=G.arcs[7][4].adj=650;
	  G.arcs[5][6].adj=G.arcs[6][5].adj=740;
      G.arcs[5][9].adj=G.arcs[9][5].adj=250;    
      G.arcs[5][10].adj=G.arcs[10][5].adj=150;
      G.arcs[6][7].adj=G.arcs[7][6].adj=550;
      G.arcs[7][11].adj=G.arcs[11][7].adj=330;
      G.arcs[8][9].adj=G.arcs[9][8].adj=440;
      G.arcs[8][12].adj=G.arcs[12][8].adj=220;
      G.arcs[9][10].adj=G.arcs[10][9].adj=880;
      G.arcs[9][12].adj=G.arcs[12][9].adj=770;      
      G.arcs[11][14].adj=G.arcs[14][11].adj=660;
      G.arcs[12][13].adj=G.arcs[13][12].adj=990;
      G.arcs[13][15].adj=G.arcs[15][13].adj=880;
      G.arcs[14][15].adj=G.arcs[15][14].adj=520;
}

void introduce()
{  int i;
   for(i=1;i<=NUM;i++)
   { 
     G.vex[0].description="  �� �����ƾ���ѧ��®԰У��λ�ڽ���ʡ�ϲ����ü��������������������������Ϊ����·������ܽ��·����Ϊ���ִ����У���ڵĽ�ѧ����������12������ѧ¥��Ⱥ®��Ӣ®����®����®�Ķ�ѧԺ��ѧ¥��ͼ���������ģ���ѧ������ģ�ѧ������������®������®����®����®����®����ѧ����Ԣ���Լ���®���� 1����2����3����4����5����6����7����8������ѧ����Ԣ����һ����ʳ�á���ҵ�֣�УҽԺ��\n\n\t\t";
     G.vex[1].description="\t�� ����";
     G.vex[2].description="\t�� ����";
     G.vex[3].description="\t�� ����";
     G.vex[4].description="\t�� ����";
     G.vex[5].description="\t�� ����";
     G.vex[6].description="\t�� ����";
     G.vex[7].description="\t�� ����";
     G.vex[8].description="\t�� ����";
     G.vex[9].description="\t�� ����";
     G.vex[10].description="\t�� ����";
     G.vex[11].description="\t�� ����";
     G.vex[12].description="\t�� ����";
     G.vex[13].description="\t�� ����";
     G.vex[14].description="\t�� ����";
     G.vex[15].description="\t�� ����";
   }
}


void ShortestPath(int num)  
{  int v,w,i,t; 
   int final[NUM]; 
   int min;
   for(v=1;v<NUM;v++)
   {
     final[v]=0; 
     D[v]=G.arcs[num][v].adj;
     for(w=1;w<NUM;w++) 
     P[v][w]=0;
     if(D[v]<32767) 
	 { 
       P[v][num]=1; 
       P[v][v]=1; 
	 }
   }
       D[num]=0;
       final[num]=1;  
    for(i=1;i<NUM;++i) 
	{
       min=Max; 
       for(w=1;w<NUM;++w)
        if(!final[w]) 
         if(D[w]<min) 
		 {
           v=w;
           min=D[w];  
		 } 
           final[v]=1; 
    for(w=1;w<NUM;++w) 
     if(!final[w]&&((min+G.arcs[v][w].adj)<D[w]))
	 {
        D[w]=min+G.arcs[v][w].adj;
        for(t=0;t<NUM;t++)
         P[w][t]=P[v][t];
         P[w][w]=1;
	 }
	}
}

void output(int sight1,int sight2)
{
  int a,b,c,d,q=0;
  a=sight2; 
  if(a!=sight1) 
  {
    cout<<"��"<<G.vex[sight1].sight<<"��"<<G.vex[sight2].sight<<"�����·����"<<endl; 
    cout<<G.vex[sight1].sight<<"------>"; 
    d=sight1; 
    for(c=0;c<NUM;++c)
	{
      gate:; 
      P[a][sight1]=0;
      for(b=0;b<NUM;b++)
	  {
        if(G.arcs[d][b].adj<32767&&P[a][b]) 
		{  cout<<G.vex[b].sight<<"-->"; 
           q=q+1; 
           P[a][b]=0;
           d=b; 
           if(q%8==0) cout<<endl;
           goto gate;
		}
	  }
	}
	 cout<<endl;
	 cout<<"��̾���Ϊ"<<D[a]<<"m"<<endl; 
  }
  else cout<<"�õ��غ�!"<<"           ";
}

//***************************************************
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
        	case 2:show_tu(); 	break;
        	case 3: break; 
        	case 4: return;
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
