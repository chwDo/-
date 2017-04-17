#include <iostream> 
#include<conio.h>
#include<string.h>
#define N 10
	int n=1;
#define Max 32767
#define NUM 16
using namespace std;
typedef struct ArcCell
{ int adj;
  char *info;
}ArcCell; 

typedef struct VertexType
{ int number;  
  string sight; 
  string description; 
}VertexType; 
typedef struct
{ VertexType vex[NUM]; 
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

      
int main() 
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
   system("cls");
   do
   {  flag=1;
      introduce();                             
      cout<<"                     * 1.ѧУ��� ��     "<<endl;                    
	  cout<<"                     * 2.��ʾ�����ı�� ��"<<endl;                
      cout<<"                     * 3.�鿴�����ľ�����Ϣ ��"<<endl;	  
      cout<<"                     * 4.����·�����ȼ��ҳ����·����"<<endl;        
      cout<<"                     * 5.�˳� ��"<<endl;                                                       
      cout<<"               ****************************************************\n"<<endl;
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
      G.arcs[1][4].adj=G.arcs[4][1].adj=1000;
      G.arcs[1][6].adj=G.arcs[6][1].adj=600;            
      G.arcs[2][3].adj=G.arcs[3][2].adj=400;
      G.arcs[2][8].adj=G.arcs[8][2].adj=1200;
      G.arcs[3][5].adj=G.arcs[5][3].adj=400;
      G.arcs[3][6].adj=G.arcs[6][3].adj=900;
      G.arcs[4][6].adj=G.arcs[6][4].adj=700;
      G.arcs[4][7].adj=G.arcs[7][4].adj=700;
	  G.arcs[5][6].adj=G.arcs[6][5].adj=800;
      G.arcs[5][9].adj=G.arcs[9][5].adj=800;    
      G.arcs[5][10].adj=G.arcs[10][5].adj=800;
      G.arcs[6][7].adj=G.arcs[7][6].adj=100;
      G.arcs[7][11].adj=G.arcs[11][7].adj=200;
      G.arcs[8][9].adj=G.arcs[9][8].adj=200;
      G.arcs[8][12].adj=G.arcs[12][8].adj=400;
      G.arcs[9][10].adj=G.arcs[10][9].adj=700;
      G.arcs[9][12].adj=G.arcs[12][9].adj=500;      
      G.arcs[11][14].adj=G.arcs[14][11].adj=100;
      G.arcs[12][13].adj=G.arcs[13][12].adj=600;
      G.arcs[13][15].adj=G.arcs[15][13].adj=100;
      G.arcs[14][15].adj=G.arcs[15][14].adj=100;
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
    cout<<G.vex[sight1].sight<<"-->"; 
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
