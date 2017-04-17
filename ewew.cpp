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
      	 cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // 输出景点列表 
	   }
        cout<<"请按回车键继续...\n";
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
      	cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // 输出景点列表 
	   }
        cout<<"请选择起点景点（1～15）：";
        cin>>v0;
        cout<<"请选择终点景点（1～15）：";
        cin>>v1;
        ShortestPath(v0); 
        output(v0,v1);
        cout<<"请按回车键继续...\n";
        getchar();
        getchar();
        break;
	}
  }
  while(xxx!='5');
   system("cls");
}

char Menu() // 主菜单 //
{  char c;
   int flag;
  
   do
   {   system("cls");
       flag=1;
      introduce();                             
      cout<<"                      1.学校简介      "<<endl;                    
	  cout<<"                      2.显示场所的编号 "<<endl;                
      cout<<"                      3.查看场所的具体信息 "<<endl;	  
      cout<<"                      4.计算路径长度及找出最短路径"<<endl;        
      cout<<"                      5.退出 ┃"<<endl;                                                       
      cout<<"               请输入您的选择："<<endl;
      scanf("%c",&c);
      if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6')
        flag=0;
   } while(flag);
     return c;
}

char SearchMenu() // 查询子菜单 
{  char c;
   int flag;
   do
   {  flag=1;
      system("cls");
      introduce();
      cout<<"               *************************************\n";
      cout<<"               * ┃\n";                           
      cout<<"               * 1、按照景点编号查询 ┃\n";       
      cout<<"               * 2、按照景点名称查询 ┃\n";       
      cout<<"               * 0、返回 ┃\n";                   
      cout<<"               * ┃\n";                           
      cout<<"               *************************************\n";
      cout<<"               请输入您的选择：";
      scanf("%c",&c);
      if(c=='1'||c=='2'||c=='0')
        flag=0;
   }  while(flag);
      return c;
}

void search() // 查询景点信息 
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
	        cout<<"                           "<<i<<"."<<G.vex[i].sight<<" "<<endl; // 输出景点列表 
		  }
          cout<<"                           "<<"请输入您要查找的景点编号：";
          scanf("%d",&num);
          for(i=0;i<NUM;i++)
		  {
            if(num==G.vex[i].number)
			{
              cout<<"                           "<<"您要查找景点信息如下:";
              cout<<"                           "<<G.vex[i].description;
              cout<<"                    按任意键返回...";
              getchar();
              getchar();
              break;
			}
		  }
              if(i==NUM)
			  {
                cout<<"                    没有找到！";
                cout<<"                    按任回车返回...";
                getchar();
                getchar();
			  } break;
        case '2':
          system("cls");
          introduce();
          cout<<"                           "<<"请输入您要查找的景点名称：";
          scanf("%s",name);
          for(i=1;i<NUM;i++)
		  {
            if(name!=G.vex[i].sight)
			{
              cout<<"                    您要查找景点信息如下:";
              cout<<"                    "<<G.vex[i].description;
              cout<<"                    按回车键返回...";
              getchar();
              getchar();
              break;
			}
		  }
              if(i==NUM)
			  {
                cout<<"                    没有找到！";
                cout<<"                    按回车键返回...";
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
    G.vex[0].sight="学校简介";
    G.vex[1].sight="南大门";
    G.vex[2].sight="北大门";
    G.vex[3].sight="大学生活动中心";
    G.vex[4].sight="图书馆";
    G.vex[5].sight="宁庐";
    G.vex[6].sight="明德广场";
    G.vex[7].sight="静庐";
    G.vex[8].sight="和庐";
    G.vex[9].sight="宁庐";
    G.vex[10].sight="第一教学楼";
    G.vex[11].sight="第二教学楼";
    G.vex[12].sight="教工宿舍";
    G.vex[13].sight="学生一食堂";
    G.vex[14].sight="学生二食堂";
    G.vex[15].sight="学生三食堂";
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
     G.vex[0].description="  ▲ 江西财经大学麦庐园校区位于江西省南昌经济技术开发区，南临玉屏大道，西为海棠路，东临芙蓉路，北为枫林大道。校区内的教学科研区内有12公共教学楼，群庐、英庐、荟庐、萃庐四栋学院教学楼，图书文献中心，大学生活动中心；学生生活区有麦庐南区宁庐、静庐、祥庐、和庐四座学生公寓，以及麦庐北区 1栋，2栋，3栋，4栋，5栋，6栋，7栋，8栋八座学生公寓，第一、二食堂、商业街，校医院。\n\n\t\t";
     G.vex[1].description="\t▲ 暂无";
     G.vex[2].description="\t▲ 暂无";
     G.vex[3].description="\t▲ 暂无";
     G.vex[4].description="\t▲ 暂无";
     G.vex[5].description="\t▲ 暂无";
     G.vex[6].description="\t▲ 暂无";
     G.vex[7].description="\t▲ 暂无";
     G.vex[8].description="\t▲ 暂无";
     G.vex[9].description="\t▲ 暂无";
     G.vex[10].description="\t▲ 暂无";
     G.vex[11].description="\t▲ 暂无";
     G.vex[12].description="\t▲ 暂无";
     G.vex[13].description="\t▲ 暂无";
     G.vex[14].description="\t▲ 暂无";
     G.vex[15].description="\t▲ 暂无";
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
    cout<<"从"<<G.vex[sight1].sight<<"到"<<G.vex[sight2].sight<<"的最短路径是"<<endl; 
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
	 cout<<"最短距离为"<<D[a]<<"m"<<endl; 
  }
  else cout<<"该点重合!"<<"           ";
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
