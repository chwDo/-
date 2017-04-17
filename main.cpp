#include "heard.h"
#include "cccc.h"
void savedata(CTree &T)
{
	PTNode p_node;
	FILE *fp = fopen("�����ļ�.txt", "wb");
	rewind(fp);
	//fprintf(fp, "%s", &T.nodeNum);
	
	fwrite(&T.nodeNum, sizeof(int), 1, fp);
	for (int i = 0; i < T.nodeNum;i++)
	{ 
		p_node.data = T.nodes[i].data;
		p_node.parent = T.nodes[i].parent;
		//fprintf(fp, "%s", &p_node);//���ļ���д�����˫�׵����Ž����Ϣ
		fwrite(&p_node,sizeof(PTNode),1,fp);
	}
	fclose(fp);
	printf("����ɹ�");

}
void readdata(CTree &T)
{
	PTNode p_node = { { "����Ŀ¼"," 0"," 0","0 "," 0"," 0" }, -1 };//��ʼΪ��㣬��ֵ���ڵ㳣��ֵ
	childPtr p;
	int i, num;
	FILE *fp;
	if (!(fp = fopen("�����ļ�.txt", "rb")))//�����ļ������ڣ��Զ��������ڵ㲢���̺󷵻�
	{
		T.nodes[0].data = p_node.data;
		T.nodes[0].firstChild = NULL;
		T.nodes[0].parent = -1;
		T.nodeNum = 1; T.root = 0;
		savedata(T);
		return;
	}
	//fscanf(fp, "%s", &num);
	fread(&num, sizeof(int), 1, fp);//��ȡ���Ž������
	for (i = 0; i < num; i++)T.nodes[i].firstChild = NULL;//ͷ����ʼ��
	for (i = 0; i < num; i++)
	{
		//fscanf(fp, "%s", &p_node);
		fread(&p_node, sizeof(PTNode), 1, fp);
		T.nodes[i].data = p_node.data;       
		T.nodes[i].parent = p_node.parent;
	   // printf("%s(%s)\n", T.nodes[i].data.name, T.nodes[i].data.id);
		if (p_node.parent != -1)
		{
			p = (childPtr)malloc(sizeof(CNode));
			p->child = i;
			p->nextChild = T.nodes[p_node.parent].firstChild;
			T.nodes[p_node.parent].firstChild = p;
		}
	}
	T.root = 0;
	T.nodeNum = num;
	fclose(fp);
}
void preDisp(CTree &T, int s, int layer)
//�����������T�и��������Խ��SΪ�ԡ����ͽṹ����ʾ��layerΪS������ڲ���
{
	childPtr p;
	int i;
	for (i =1; i < layer-1; i++)   printf("%-7s", "| ");
	if (i < layer) printf("��----");
	printf("%s\n", T.nodes[s].data.name);//(%s), T.nodes[s].data.id
	for (p = T.nodes[s].firstChild; p; p = p->nextChild)
		preDisp(T, p->child, layer + 1);//�ݹ���ʾ��s������Ϊ��������
}
void displayBCTree(CTree &T)//�ԡ����ͽṹ��������ŷ���Ŀ¼��
{
	if (T.root != -1)//�����ǿ�
		preDisp(T, T.root, 1);
}
void addNewBC(CTree &T)//��Ŀ¼������·���
{
	childPtr p;
	char fName[20];
	int i;
	printf("����·���\n");
	printf("�����������֣�\n"); scanf("%s", fName);
	for (i = 0; i < T.nodeNum&&strcmp(T.nodes[i].data.name, fName) != 0; i++);
	if (i >= T.nodeNum)          {printf("�޴����ţ�\n"); return; }
	printf("���������֣�"); scanf("%s", T.nodes[T.nodeNum].data.name);
	printf("�����ŷ�����: "); scanf("%s", T.nodes[T.nodeNum].data.name_p);
	printf("����������: "); scanf("%s", T.nodes[T.nodeNum].data.xingzhi);
	printf("�����ſں�: "); scanf("%s", T.nodes[T.nodeNum].data.kouhao);
	printf("��������ּ: "); scanf("%s", T.nodes[T.nodeNum].data.zongzhi);
	printf("�������³�: "); scanf("%s", T.nodes[T.nodeNum].data.zhangcheng);
	T.nodes[T.nodeNum].parent = i; T.nodes[T.nodeNum].firstChild = NULL;
	p = (childPtr)malloc(sizeof(CNode)); p->child = T.nodeNum;
	p->nextChild = T.nodes[i].firstChild; T.nodes[i].firstChild = p;
	T.nodeNum++;
}
void deleteBC(CTree &T)
{   childPtr p,r;
	char fName[20];
	int i;
	printf("�������ż��丽�����ŵ�ɾ��\n");
	printf("�������֣�\n"); scanf("%s", fName);
	for (i = 0; i < T.nodeNum&&strcmp(T.nodes[i].data.name, fName) != 0; i++);
	if (i >= T.nodeNum)     {printf("�޴����ţ�\n"); return; }
	p=T.nodes[T.nodes[i].parent].firstChild;  int c=1;
	if(strcmp(T.nodes[p->child].data.name,fName)==0)
	{ T.nodes[T.nodes[i].parent].firstChild=p->nextChild; c=0;}//ȷ����һ����ΪҪ�ҵ��� 
	 r=p; 
	 p=p->nextChild;
 	while(p&&c==1)
	{   
       if((strcmp(T.nodes[p->child].data.name,fName))==0)
		{ 
		  r->nextChild=p->nextChild; 
	    }
		if(p==NULL)  break;
		r=p;
		p=p->nextChild;
	}
	 T.nodes[i].parent=-1;     //��������ɾ������ɾ�� 
    /*	while(i<=T.nodeNum)
	{ T.nodes[i]=T.nodes[i+1]; i++;
	cout<<"i="<<i<<endl;
	}

	 for(p=T.nodes[T.nodes[i].parent].firstChild; p ; p=p->nextChild)
	    {    //cout<<"**"<<T.nodes[p->child].data.name<<endl;
	        //cout<<T.nodes[p->nextChild->child].data.name<<endl;
		  
		}*/
	cout<<"ɾ���ɹ�"<<endl;
}
void selectMenu()
{    system("cls");
	printf("\n------------���Ź���--------------------\n");
	printf("\t1:��ʾĿ¼\n");
	printf("\t2:��ӷ���\n");
	printf("\t3:ɾ������\n");
	printf("\t4:���Ź���\n");
	printf("\t5:�����̹���\n");
	printf("\t0:�˳�\n");
	printf("\n\n\n��ѡ��");
}
void  change_Tree(CTNode &T)
{
	int j;
	system("cls");
	cout<<"1-��������:"<<T.data.name<<endl;//.nodes[i].
	cout<<"2-���ŷ�����:"<<T.data.name_p<<endl;
	cout<<"3-��������:"<<T.data.xingzhi<<endl;
	cout<<"4-���ſں�:"<<T.data.kouhao<<endl;
	cout<<"5-������ּ:"<<T.data.zongzhi<<endl; 
	cout<<"6-�����³�: "<<T.data.zhangcheng<<endl;
	cout<<"����Ҫ�޸ĵ���"<<endl;
      cin>>j;
	cout<<"����Ҫ�޸ĵ�ֵ"<<endl;
	switch(j)
	{  
	  case 1:  cin>>T.data.name;  cout<<"�޸ĳɹ�"<<endl; break;
	  case 2:  cin>>T.data.name_p; cout<<"�޸ĳɹ�"<<endl; break;
	  case 3:  cin>>T.data.xingzhi; cout<<"�޸ĳɹ�"<<endl; break;
	  case 4:  cin>>T.data.kouhao; cout<<"�޸ĳɹ�"<<endl; break;
	  case 5:  cin>>T.data.zongzhi; cout<<"�޸ĳɹ�"<<endl; break;
	  case 6:  cin>>T.data.zhangcheng; cout<<"�޸ĳɹ�"<<endl; break;
	default :  cout<<"�������"<<endl; cin.clear(); cin.sync();
	}  
    
}
void add_Tree(char str1[],ppList &L)
{   ppList p=L->next;
     string str=str1;
	  cout<<"��ѡ��Ա: "<<endl;
	  while(p)
	  {  if(p->data.shetuan=="��")
	        cout<<"ѧ�ţ�"<<p->data.ID<<"������"<<p->data.name<<endl;
	      p=p->next;  
	  }
	  system("pause");
        int n,n1;	  
	while(1)
	{ p=L->next;   //ָ�븴λ 
	   n=0; 
	   system("cls");
	   cout<<"����������ѧ��"<<endl;
	   cin>>str;
	  while(p) 
	  {
	   if(str==p->data.ID)
	    {     p->data.shetuan=str1; 
		      p->data.integral=0;
	          p->data.rank=999;     //���Ż������ 
		 n=1; cout<<"�������"<<endl; break;
		}
	    p=p->next;
	  }
	    if(n==0)  cout<<"���޴���"<<endl;
	     cout<<"1:���� 2:���"<<endl;
         cin>>n1; if(n1==2) break;
        
	}
}
void tuihe_Tree(char str[],ppList L)
{   ppList p=L->next;
     string str1=str,str2;  int n=0;
     while(1)
	{  system("cls");
	  cout<<"����������Աѧ��"<<endl;
	   p=L->next;
	   cin>>str2;
	   cout<<"������Ա: "<<endl;
	  while(p)
	  {  if(str2==p->data.ID&&str1==p->data.shetuan)
	      {   cout<<"ѧ�ţ�"<<p->data.ID<<"������"<<p->data.name<<endl;
	          p->data.shetuan="��";
	          p->data.shenfen="��Ա";
	          p->data.integral=0;
	        n=1;  p->data.rank=999;  //���Ż������ 
	      }
		  p=p->next;  
	  }
	  if(n==0) cout<<"���޴���"<<endl;
	cout<<"1:���� 0���˳�"<<endl; int n;cin>>n; if(n==0) break;
    }
}
void  display_Tree(char str[],ppList &L)
{
	ppList p=L->next;
	string str1=str;
	cout<<"������Ա"<<endl;
	while(p)
	{ 
	   if(p->data.shetuan==str1)
	   { 
	    cout<<p->data.shenfen<<":"<<endl;
	    cout<<"ѧ�ţ�"<<p->data.ID<<"������"<<p->data.name<<endl;
        cout<<"����:"<<p->data.integral<<endl;
	   } 
	   p=p->next;
	}
	system("pause");
}
void ganbu_Tree(char str1[],ppList &L)
{ ppList p=L->next;
  string str=str1,str2; int q=0,n;
    cout<<"����Ҫѡ�ٵ�ְλ"<<endl;
    cin>>str2;
    if(str2=="����")  q=800;
     else if(str2=="������")q=600;
	  else {cout<<"�������"<<endl; return;}
     cout<<"������������Ա:"<<endl;
	while(p)
	{
		if(p->data.shetuan==str&&p->data.integral>=q)
		 { 
		  cout<<"ѧ�ţ�"<<p->data.ID<<"������"<<p->data.name<<endl;
          cout<<"����:"<<p->data.integral<<endl;   
          n=1;
		 }
        p=p->next;
	}
	if(n==0) { cout<<"��������Ա"<<endl; system("pause"); system("cls"); return;}
   p=L->next; //ָ�븴λ
     cout<<"�����뱻ѡ���˵�ѧ��"<<endl;
	  string str3;cin>>str3; 
	 while(p)
    {
    	if(p->data.shetuan==str&&p->data.integral>=q&&p->data.ID==str3)
    	 { 
		  cout<<"��Ա:"<<p->data.name<<endl;
          cout<<"�����:"<<p->data.shenfen<<"->"<<str2<<endl;
          p->data.shenfen=str2; break;
		 }
		 p=p->next;
	}
}
void zanzhu_chushihua(zanzhu (&z)[5])
{   
    z[0].name="���ι�˾";z[0].fuzeren="��1";z[0].wangzhi="www.lalal.com";z[0].jianjie="����";z[0].shetuan="ѧϰ��";z[0].shetuan2="����"; 
	z[1].name="��ţ��Ϸ";z[1].fuzeren="��2";z[1].wangzhi="www.lala2.com";z[1].jianjie="����";z[1].shetuan="����";z[1].shetuan2="����"; 
    z[2].name="ʢ������";z[2].fuzeren="��3";z[2].wangzhi="www.lala3.com";z[2].jianjie="����";z[2].shetuan="����";z[2].shetuan2="����"; 
    z[3].name="��ͨ���";z[3].fuzeren="��4";z[3].wangzhi="www.lala4.com";z[3].jianjie="����";z[3].shetuan="����";z[3].shetuan2="����"; 
    z[4].name="��Ѷ��˾";z[4].fuzeren="��5";z[4].wangzhi="www.lala5.com";z[4].jianjie="����";z[4].shetuan="����";z[4].shetuan2="����"; 
    
}
zanzhu z[5];
void  zanzhu_Tree()
{    
    if(z[0].name!="���ι�˾") zanzhu_chushihua(z);
	system("cls");cout<<"��������Ϣ"<<endl; 
   for(int i=0;i<5;i++)
   { cout<<i+1<<": ��˾��: "<<z[i].name<<" ������: "<<z[i].fuzeren<<" ���: "<<z[i].jianjie<<endl;
     cout<<"��վ: "<<z[i].wangzhi<<" ��������1: "<<z[i].shetuan<<" ��������2: "<<z[i].shetuan2;
      cout<<endl;
   }
   cout<<"1:������Ϣ�޸� 0:�˳�"<<endl; 	
   int i;cin>>i;  if(i==0) return;
   cout<<"Ҫ�޸ĵĹ�˾"<<endl;
   cin>>i; cout<<"�����޸ĵĹ�˾: "<<z[--i].name<<endl;
   system("pause"); system("cls");
   cout<<"������Ҫ�޸ĵ���Ŀ"<<endl;
   cout<<"1: ��˾��"<<endl;
   cout<<"2��������"<<endl;
   cout<<"3�����"<<endl;
   cout<<"4����վ"<<endl;
   cout<<"5����������1"<<endl;
   cout<<"6����������2"<<endl;
    int n;cin>>n;
   switch(n)
   {
   	case 1:  cout<<"����������:"<<endl; cin>>z[i].name;  break;
   	case 2:  cout<<"����������:"<<endl; cin>>z[i].fuzeren;  break;
   	case 3:  cout<<"����������:"<<endl; cin>>z[i].jianjie; break;
   	case 4:  cout<<"����������:"<<endl; cin>>z[i].wangzhi;  break;
   	case 5:  cout<<"����������:"<<endl; cin>>z[i].shetuan; break;
   	case 6:  cout<<"����������:"<<endl; cin>>z[i].shetuan2;  break;
   	 default: cout<<"�������"<<endl; break;
   }
}
void chaxun_Tree(string str,ppList &L)
{
 ppList p=L->next;
  double average=0;int i=0;
  while(p)
  {   if(p->data.shetuan==str)
     {average+=p->data.integral; i++;}
  }
  if(i!=0) cout<<"����Ϊ"<<average/i<<endl;
    else cout<<"����Ϊ"<<average<<endl;
}
void renshiguanli(CTree &T,ppList &L)
{   
   cout<<"�������Ž������Ź���"<<endl;
     char str[20]; cin>>str; int n=0; int i,j;
    for(i=0;i<T.nodeNum;i++)
       if(strcmp(T.nodes[i].data.name,str)==0) { n=1; break;}
     if(n==0) { cout<<"�޴�����"<<endl; return;}
	while(1)
	{
	system("cls");
	cout<<"1-������Ϣ�޸�"<<endl;
    cout<<"2-��������"<<endl;
    cout<<"3-��Ա����"<<endl;
    cout<<"4-������Ա�鿴"<<endl;
    cout<<"5-�ɲ�ѡ���ʸ��ѯ"<<endl;
    cout<<"6-��Ա����ƽ��ֵ��ѯ"<<endl;
    cout<<"0-�˳�"<<endl;
	cin>>j; 
	  switch(j)
	 { 
	   case 1: change_Tree(T.nodes[i]);break;
	   case 2: add_Tree(T.nodes[i].data.name,L);break;
	   case 3: tuihe_Tree(T.nodes[i].data.name,L);break;
	   case 4: display_Tree(T.nodes[i].data.name,L);break;
	   case 5: ganbu_Tree(T.nodes[i].data.name,L);break;
	   case 6: chaxun_Tree(T.nodes[i].data.name,L);break;
	   case 0: return;
	    default :  cout<<"�������"<<endl; i=0; cin.clear(); cin.sync();
		
	 }
    }
	
}
int show_Tree(ppList &L)
{
	CTree T;
	int select;
	readdata(T);
	while (1)
	{
		selectMenu();
		scanf("%d", &select);
		switch (select)
		{
		case 1:displayBCTree(T); break;
		case 2:addNewBC(T); break;
		case 3:deleteBC(T); break;
		case 4:renshiguanli(T,L);break;
		case 5:zanzhu_Tree();break;
		case 0: return 0;
		default:printf("�������\n");
		}
		system("pause");
		system("cls");
	}
	savedata(T);
}
void Member::fileout(ppList &L)
{  
     L=new ppNode;
    L->next=NULL;
    L->prior=NULL;
    ppList r,p;
       r=L;
    string line;
    
    ifstream open("ͨѶ¼.txt");//��ȡ�ļ�
	if (!open)
	{
		cout << "open error!" << endl;
	}
	while (getline(open, line))
	{
		istringstream is(line);   
		p = new ppNode;
		is >>p->data.shenfen>>p->data.shetuan>>p->data.address>> p->data.class_n>>p->data.ID >> p->data.integral >> p->data.name >> p->data.rank >> p->data.sex >> p->data.telephonenumber>>p->data.time_p.day>>p->data.time_p.hour>>p->data.time_p.minute>>p->data.time_p.mouth>>p->data.time_p.second>>p->data.time_p.year;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	open.close();
	cout<<"��ȡ���"<<endl;
}
void Member::filein(ppList &L)
{    
     ppList p;
     p=L->next;
     fstream fMember("ͨѶ¼.txt", ios::out);
	if (!fMember)
	{
		cout << "open error!" << endl;
		abort();
	}
	while (p != NULL)
	{
	  fMember <<p->data.shenfen<<" "<<p->data.shetuan<<" "<<p->data.address<<" "<< p->data.class_n<<" "<<p->data.ID <<" "<< p->data.integral <<" "<< p->data.name <<" "<< p->data.rank <<" "<<p->data.sex <<" "<< p->data.telephonenumber<<" "<<p->data.time_p.day<<" "<<p->data.time_p.hour<<" "<<p->data.time_p.minute<<" "<<p->data.time_p.mouth<<" "<<p->data.time_p.second<<" "<<p->data.time_p.year<<endl;
	   p=p->next;

	 }
	 fMember.close();
	 cout<<"д�����"<<endl;
	 system("pause");
}
int Member::GrateList(ppList &L)
{   L=new ppNode;
    L->next=NULL;
    L->prior=NULL;
	ppList p=L->next,r=L;
    SYSTEMTIME sys; 
	while(1)
    { GetLocalTime(&sys);//ʱ��ˢ�� 
	  p=new ppNode;
	  p->data.time_p.second=sys.wSecond;
	  p->data.time_p.minute=sys.wMinute;
      p->data.time_p.day=sys.wDay;
      p->data.time_p.mouth=sys.wMonth;
      p->data.time_p.year=sys.wYear;
      p->data.time_p.hour=sys.wHour;
      p->data.rank=0;
      p->data.integral=0;
      p->data.shetuan="��";
	  p->data.shenfen="��Ա"; 
      system("cls");
      cout<<"�뿪ʼ����ѧ����Ϣ"<<endl;
      cout<<"ѧ��:  "<<endl;   cin>>p->data.ID;
      cout<<"������ "<<endl;   cin>>p->data.name;
      cout<<"�Ա� "<<endl;   cin>>p->data.sex;
      cout<<"רҵ�༶�� "<<endl; cin>>p->data.class_n;
      cout<<"��ϵ�绰�� "<<endl; cin>>p->data.telephonenumber;
      cout<<"��ͥסַ�� "<<endl; cin>>p->data.address;
	   p->next=NULL; r->next=p; p->prior=r; r=p;
	  int n; cout<<"1:�������� 0������"<<endl; cin>>n; if(n==0) break;
      system("cls");
      cin.sync();
      cin.clear();
      	
	   
     //cin.ignore(888,'\n');//�����ǰ��
     //std::numeric_limits<std::streamsize>::max()
	 //cin.sync();
	 
	 }
	 system("pause");
	 system("cls");
	 return OK;
}
int Member::Llength(ppList &L)
{    
    ppList p=L->next;
    int i=0;
	while(p)
	{
	p=p->next;
     i++;
	}
	return i;
}
int Member::InsertList(ppList &L)
{   SYSTEMTIME sys; 
    ppList p,q=L->next;  int n=0;
    while(1)
    { GetLocalTime(&sys);//ʱ��ˢ�� 
	  p=new ppNode;
	  system("cls");
      cout<<"�뿪ʼ����ѧ����Ϣ"<<endl;
      cout<<"ѧ��:  "<<endl;   cin>>p->data.ID;
          while(q)
        { if(q->data.ID==p->data.ID)
            { cout<<"�Ѿ��д�����Ϣ"<<endl; n=1; system("pause");break;}
          q=q->next; 
		}
		if(n==1) {delete p; break;}
      cout<<"������ "<<endl;   cin>>p->data.name;
      cout<<"�Ա� "<<endl;   cin>>p->data.sex;
      cout<<"רҵ�༶�� "<<endl; cin>>p->data.class_n;
      cout<<"��ϵ�绰�� "<<endl; cin>>p->data.telephonenumber;
      cout<<"��ͥסַ�� "<<endl; cin>>p->data.address;
	  p->data.time_p.second=sys.wSecond;
	  p->data.time_p.minute=sys.wMinute;
      p->data.time_p.day=sys.wDay;
      p->data.time_p.mouth=sys.wMonth;
      p->data.time_p.year=sys.wYear;
      p->data.rank=999;
      p->data.integral=0;
	  p->next=L->next;  L->next=p; //p->prior=L; L->next->prior=p;
      int n; cout<<"0������"<<endl; cin>>n;
	  
	  if(!cin){
	  cin.clear();
      cin.sync();
	  } else{
	   if(n==0) break;
        }
      

	  system("cls");
    }
    system("cls");
    return OK;
}
int Member::display_member(ppList &L)
{  
  ppList p;
  p=L->next;
  system("cls");
  while(p)
  {   cout<<"ѧ��:  "<<p->data.ID<<endl;  
      cout<<"������ "<<p->data.name<<endl;  
      cout<<"�Ա� "<<p->data.sex<<endl;  
      cout<<"רҵ�༶�� "<<p->data.class_n<<endl;
      cout<<"��ϵ�绰�� "<<p->data.telephonenumber<<endl;
      cout<<"��ͥסַ�� "<<p->data.address<<endl; 
      cout<<"��������   "<<p->data.shetuan<<endl;
      cout<<"����ʱ�䣺 "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      p=p->next;
  }
  system("pause");
  system("cls");
  return OK;
}
int  Member::rankquery(ppList &L)
{  ppList p=L->next;
   cout<<"������ѧ��"<<endl;
   string str; cin>>str;
   while(p)
   { if(p->data.ID==str)
     { 
      cout<<"��Ա�ȼ�:  "<<endl;
	  cout<<"ѧ��:  "<<p->data.ID<<endl;  
      cout<<"������ "<<p->data.name<<endl;  
      cout<<"�Ա� "<<p->data.sex<<endl;  
      cout<<"רҵ�༶�� "<<p->data.class_n<<endl;
      cout<<"��ϵ�绰�� "<<p->data.telephonenumber<<endl;
      cout<<"��ͥסַ�� "<<p->data.address<<endl; 
      cout<<"����ʱ�䣺 "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
	 }
	 p=p->next;
   }
   return OK;
}
double Member::rankaverage(ppList &L)
{ ppList p=L->next;
  double average=0;int i=0;
  while(p)
  { average+=p->data.integral;
     i++;
  }
  return average/i;
}
int Member::ranksort(ppList &L)
{   
   ppList p,q;
  /*
  while(i<=Llength(L))
  {  p=L->next;   //���� 
     while((p->data.rank!=0)&&p->next)
       p=p->next;
        q=p;p=p->next;
    while(p)
    {	 
	if((p->data.integral>q->data.integral)&&(p->data.rank==0))
		{ q=p;  cout<<q->data.name<<"<->"<<p->data.name<<endl; }
      p=p->next; 
	}
	q->data.rank=i;
	i++;
  }*/system("cls");
  for(int i=1;i<=Llength(L);i++)
  {  p=L->next; 
		 while(p)
	 {
	   if(p->data.rank==i)
	   {
	  cout<<"��"<<i<<":"<<endl;
      cout<<"���֣�"<<p->data.integral<<"�ȼ�:  "<<p->data.integral/100<<endl;
	  cout<<"ѧ��:  "<<p->data.ID<<endl;  
      cout<<"������ "<<p->data.name<<endl;  
      cout<<"�Ա� "<<p->data.sex<<endl;  
      cout<<"רҵ�༶�� "<<p->data.class_n<<endl;
      cout<<"��ϵ�绰�� "<<p->data.telephonenumber<<endl;
      cout<<"��ͥסַ�� "<<p->data.address<<endl; 
      cout<<"����ʱ�䣺 "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      cout<<"��������:  "<<p->data.shetuan<<endl;
	   }
	   p=p->next;
     }
	}
     system("pause");
     system("cls");
    return OK;
  
}
int Member::delete_ppList(ppList &L)
{   ppList p=L->next,r=L;  int n=0;
    cout<<"������Ҫɾ���˵�ѧ��"<<endl;
	string people;
	cin>>people;
	while(p)
    { 
     if(people==p->data.ID)
      {
	    r->next=p->next;
        cout<<"ɾ������Ϣ:"<<endl;
        cout<<"����:"<<p->data.name<<endl;
        cout<<"�Ա�:"<<p->data.sex<<endl;
        cout<<"ѧ��:"<<p->data.ID<<endl;
		delete p;   //�ͷſռ�    
		n=1;
	  }
	  p=p->next;
	}
	if(n==0) cout<<"δ�ҵ�����"<<endl;
	 else cout<<"ɾ���ɹ�"<<endl;
	system("pause");
   return OK;
}
int Member::sort_1(ppList &L,ppList p)
{   cout<<"*****"<<endl;
   //cout<<p->data.name<<"***"<<endl;
   int m_1=p->data.integral,m_2=1,n=0; // cout<<"��ʱ����Ϊ"<<m_1<<endl;
   ppList q=L->next; 
   while(q!=NULL)
   {     
   if(q->data.integral>m_1&&q->data.rank>=m_2)
      { m_2=q->data.rank;  n=1;}
	   //cout<<q->data.integral<<"-----   m2:"<<m_2<<endl;
     q=q->next;
   }        //�ҵ�Ҫ���������λ��  
              if(n==1) m_2++;
          //  cout<<"����λ��Ϊ"<<m_2<<endl;          
     q=L->next;
   while(q)
    {     
      if(q->data.rank>=m_2&&q->data.rank<p->data.rank)
        { 
		  q->data.rank++;// cout<<q->data.name<<":"<<q->data.rank;
		}  
	    q=q->next;      
    } //��λ�ú��λ�ú��� 
      p->data.rank=m_2;   //cout<<p->data.name<<":"<<p->data.rank;
      return OK;
}
int   Member::sort_2(ppList &L,ppList p)
{   int m_1=p->data.integral,m_2=999,n=0;
     ppList q=L->next; 
  while(q!=NULL)
   {     
   if(q->data.integral<m_1&&q->data.rank<=m_2)
      { m_2=q->data.rank;  n=1;}
	   //cout<<q->data.integral<<"-----   m2:"<<m_2<<endl;
     q=q->next;
    }        //�ҵ�Ҫ���������λ��  
              if(n==1) m_2--;
           // cout<<"����λ��Ϊ"<<m_2<<endl;          
     q=L->next;
   while(q)
    {     
      if(q->data.rank<=m_2&&q->data.rank>p->data.rank)
        { 
		  q->data.rank--;// cout<<q->data.name<<":"<<q->data.rank;
		}  
	    q=q->next;      
    }  //��λ��ǰ��λ��ǰ�� 
     p->data.rank=m_2;
	return 0;
}
int  Member::add_integral(ppList &L) 
{   ppList  p=L->next;;
	string people; int n_1=-1,n_2=0,n_3=0;
	while(1)
   {	system("cls");
      cout<<"������ѧ��"<<endl;
	    cin>>people; 
          p=L->next;   n_1=-1,n_2=0,n_3=0;
   	while(p)
    {  
     if(people==p->data.ID)
      { cout<<"������Ϣ:"<<endl;
        cout<<"����:"<<p->data.name<<endl;
        cout<<"�Ա�:"<<p->data.sex<<endl;
        cout<<"ѧ��:"<<p->data.ID<<endl;
		cout<<"1:ȷ��������Ϣ 2:��������"<<endl;
		 cin>>n_3;
		 if(n_3==1)
		{   n_2=1;  //��־�ҵ� 
		 cout<<"������Ҫ���ӵĻ���"<<endl;   
	     cin>>n_1;
	     p->data.integral+=n_1;
		}
		else if(n_3==2)
		{  
		  n_2=-1;
		}
        else  cout<<"�������"<<endl; 
		break; 
	  }
	  p=p->next;
	}
	if(n_2==-1)    continue;  //���ñ�ʶ 
	if(n_2==0)    {cout<<"δ�ҵ�����"<<endl; continue;}
	 if(n_1>0) sort_1(L,p);
	  else if(n_1<0) sort_2(L,p);
	 cout<<"0:ֹͣ 1:����"<<endl;
	 cin>>n_1; if(n_1==0) break;
   }
   //�����ӻ��ֵ��������� 
   cout<<"�Ʒ����"<<endl;
	system("pause");
    return OK;   
}

int   Member::change(ppList &L)
{    ppList p=L->next;
    cout<<"������ѧ��"<<endl;
	string people;  cin>>people; int i,n=0;
		while(p)
    { 
     if(people==p->data.ID)
      {  cout<<"������Ҫ�޸ĵ��"<<endl;
      cout<<"1-���֣� " <<p->data.integral<<endl;
	  cout<<"2-ѧ��:  "<<p->data.ID<<endl;  
      cout<<"3-������ "<<p->data.name<<endl;  
      cout<<"4-�Ա� "<<p->data.sex<<endl;  
      cout<<"5-רҵ�༶�� "<<p->data.class_n<<endl;
      cout<<"6-��ϵ�绰�� "<<p->data.telephonenumber<<endl;
      cout<<"7-��ͥסַ�� "<<p->data.address<<endl; 
      cout<<"����ʱ�䣺 "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      cin>>i;
	    switch(i)
		{
		  case 1:  cout<<"������"<<endl;  i=8; n=p->data.integral; cin>>p->data.integral;break;
		  case 2:  cout<<"������"<<endl;   cin>>p->data.ID; break;
		  case 3:  cout<<"������"<<endl;   cin>>p->data.name; break;
		  case 4:  cout<<"������"<<endl;   cin>>p->data.sex;break;
		  case 5:  cout<<"������"<<endl;   cin>>p->data.class_n; break;
		  case 6:  cout<<"������"<<endl;   cin>>p->data.telephonenumber; break;
		  case 7:  cout<<"������"<<endl;   cin>>p->data.address; break;
		   default :  cout<<"�������"<<endl; i=0; cin.clear(); cin.sync();
		} 
		break;
	   }
		p=p->next;
	  
    } 
    if(i==0) cout<<"�޸�ʧ��"<<endl;
       else  cout<<"�޸ĳɹ�"<<endl;
	if(i==8)
	 {   
	 if(n<p->data.integral)
	 sort_1(L,p);  
	 else if(n>p->data.integral)
	 sort_2(L,p);  
	 }
  return OK;
}
void show_ppList(Member &cc,ppList &L)
{
    int n=1;
    while(n!=-1)
	{
	system("cls");
	cout<<"1��ͨѶ¼����"<<endl;
    cout<<"2�����ֽ���鿴"<<endl;
    cout<<"3�����ӳ�Ա"<<endl;
    cout<<"4��ɾ����Ա"<<endl;
    cout<<"5: ��Ա�������"<<endl;
	cout<<"6����Ա��Ϣ�޸�"<<endl;
    cout<<"0: �˳�"<<endl;
	cin>>n;
	switch(n)
     {
    	case 1:    cc.display_member(L); break;
    	case 2:    cc.ranksort(L);  break;
    	case 3:    cc.InsertList(L); break;
    	case 4:    cc.delete_ppList(L); break;
    	case 5:    cc.add_integral(L); break;
    	case 6:    cc.change(L);  break;
    	case 0:    return ; 
        default : cout<<"������� !!"<<endl; cin.clear();cin.sync();break;
	 }
   }
    
}
//-----------------------------------------------------------
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
     G.vex[0].description="  �� ����";
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

int daa()
{
	Activity a;

	a.contolfirst();
	return 0;
}
//-----------------------------
int main()
{    Member cc;  ppList L;
    cc.fileout(L);
     //  cc.GrateList(L);
	   int i;      
    while(1)
   {  system("cls");
    cout<<"1����Ա��Ϣ����"<<endl;
    cout<<"2��������Ϣ����"<<endl;
    cout<<"3: �������"<<endl;
    cout<<"0: �˳�"<<endl;
	cin>>i;
    switch(i)
     { 
	  case 1:show_ppList(cc,L); break;
	  case 2:show_Tree(L); break;
	  case 3: daa();break;
	  case 0: return 1 ;
	   default : cout<<"������� !!"<<endl; cin.clear();cin.sync();break;
     } 
    }
   cc.filein(L);
	return 0;
}
