#include "heard.h"
#include "cccc.h"
void savedata(CTree &T)
{
	PTNode p_node;
	FILE *fp = fopen("社团文件.txt", "wb");
	rewind(fp);
	//fprintf(fp, "%s", &T.nodeNum);
	
	fwrite(&T.nodeNum, sizeof(int), 1, fp);
	for (int i = 0; i < T.nodeNum;i++)
	{ 
		p_node.data = T.nodes[i].data;
		p_node.parent = T.nodes[i].parent;
		//fprintf(fp, "%s", &p_node);//向文件中写入带有双亲的社团结点信息
		fwrite(&p_node,sizeof(PTNode),1,fp);
	}
	fclose(fp);
	printf("保存成功");

}
void readdata(CTree &T)
{
	PTNode p_node = { { "社团目录"," 0"," 0","0 "," 0"," 0" }, -1 };//初始为结点，赋值根节点常量值
	childPtr p;
	int i, num;
	FILE *fp;
	if (!(fp = fopen("社团文件.txt", "rb")))//社团文件不存在，自动建立根节点并存盘后返回
	{
		T.nodes[0].data = p_node.data;
		T.nodes[0].firstChild = NULL;
		T.nodes[0].parent = -1;
		T.nodeNum = 1; T.root = 0;
		savedata(T);
		return;
	}
	//fscanf(fp, "%s", &num);
	fread(&num, sizeof(int), 1, fp);//读取社团结点总数
	for (i = 0; i < num; i++)T.nodes[i].firstChild = NULL;//头结点初始化
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
//用先序遍历将T中根的子树以结点S为以“树型结构”显示，layer为S结点所在层数
{
	childPtr p;
	int i;
	for (i =1; i < layer-1; i++)   printf("%-7s", "| ");
	if (i < layer) printf("◎----");
	printf("%s\n", T.nodes[s].data.name);//(%s), T.nodes[s].data.id
	for (p = T.nodes[s].firstChild; p; p = p->nextChild)
		preDisp(T, p->child, layer + 1);//递归显示以s各孩子为根的子树
}
void displayBCTree(CTree &T)//以“树型结构”输出社团分类目录树
{
	if (T.root != -1)//若树非空
		preDisp(T, T.root, 1);
}
void addNewBC(CTree &T)//向目录中添加新分组
{
	childPtr p;
	char fName[20];
	int i;
	printf("添加新分组\n");
	printf("父级社团名字：\n"); scanf("%s", fName);
	for (i = 0; i < T.nodeNum&&strcmp(T.nodes[i].data.name, fName) != 0; i++);
	if (i >= T.nodeNum)          {printf("无此社团！\n"); return; }
	printf("新社团名字："); scanf("%s", T.nodes[T.nodeNum].data.name);
	printf("新社团发起人: "); scanf("%s", T.nodes[T.nodeNum].data.name_p);
	printf("新社团性质: "); scanf("%s", T.nodes[T.nodeNum].data.xingzhi);
	printf("新社团口号: "); scanf("%s", T.nodes[T.nodeNum].data.kouhao);
	printf("新社团宗旨: "); scanf("%s", T.nodes[T.nodeNum].data.zongzhi);
	printf("新社团章程: "); scanf("%s", T.nodes[T.nodeNum].data.zhangcheng);
	T.nodes[T.nodeNum].parent = i; T.nodes[T.nodeNum].firstChild = NULL;
	p = (childPtr)malloc(sizeof(CNode)); p->child = T.nodeNum;
	p->nextChild = T.nodes[i].firstChild; T.nodes[i].firstChild = p;
	T.nodeNum++;
}
void deleteBC(CTree &T)
{   childPtr p,r;
	char fName[20];
	int i;
	printf("进行社团及其附属社团的删除\n");
	printf("社团名字：\n"); scanf("%s", fName);
	for (i = 0; i < T.nodeNum&&strcmp(T.nodes[i].data.name, fName) != 0; i++);
	if (i >= T.nodeNum)     {printf("无此社团！\n"); return; }
	p=T.nodes[T.nodes[i].parent].firstChild;  int c=1;
	if(strcmp(T.nodes[p->child].data.name,fName)==0)
	{ T.nodes[T.nodes[i].parent].firstChild=p->nextChild; c=0;}//确定第一个不为要找的数 
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
	 T.nodes[i].parent=-1;     //将其数据删除隐形删除 
    /*	while(i<=T.nodeNum)
	{ T.nodes[i]=T.nodes[i+1]; i++;
	cout<<"i="<<i<<endl;
	}

	 for(p=T.nodes[T.nodes[i].parent].firstChild; p ; p=p->nextChild)
	    {    //cout<<"**"<<T.nodes[p->child].data.name<<endl;
	        //cout<<T.nodes[p->nextChild->child].data.name<<endl;
		  
		}*/
	cout<<"删除成功"<<endl;
}
void selectMenu()
{    system("cls");
	printf("\n------------社团管理--------------------\n");
	printf("\t1:显示目录\n");
	printf("\t2:添加分组\n");
	printf("\t3:删除分组\n");
	printf("\t4:社团管理\n");
	printf("\t5:赞助商管理\n");
	printf("\t0:退出\n");
	printf("\n\n\n请选择：");
}
void  change_Tree(CTNode &T)
{
	int j;
	system("cls");
	cout<<"1-社团名字:"<<T.data.name<<endl;//.nodes[i].
	cout<<"2-社团发起人:"<<T.data.name_p<<endl;
	cout<<"3-社团性质:"<<T.data.xingzhi<<endl;
	cout<<"4-社团口号:"<<T.data.kouhao<<endl;
	cout<<"5-社团宗旨:"<<T.data.zongzhi<<endl; 
	cout<<"6-社团章程: "<<T.data.zhangcheng<<endl;
	cout<<"输入要修改的项"<<endl;
      cin>>j;
	cout<<"输入要修改的值"<<endl;
	switch(j)
	{  
	  case 1:  cin>>T.data.name;  cout<<"修改成功"<<endl; break;
	  case 2:  cin>>T.data.name_p; cout<<"修改成功"<<endl; break;
	  case 3:  cin>>T.data.xingzhi; cout<<"修改成功"<<endl; break;
	  case 4:  cin>>T.data.kouhao; cout<<"修改成功"<<endl; break;
	  case 5:  cin>>T.data.zongzhi; cout<<"修改成功"<<endl; break;
	  case 6:  cin>>T.data.zhangcheng; cout<<"修改成功"<<endl; break;
	default :  cout<<"输入错误"<<endl; cin.clear(); cin.sync();
	}  
    
}
void add_Tree(char str1[],ppList &L)
{   ppList p=L->next;
     string str=str1;
	  cout<<"可选人员: "<<endl;
	  while(p)
	  {  if(p->data.shetuan=="无")
	        cout<<"学号："<<p->data.ID<<"姓名："<<p->data.name<<endl;
	      p=p->next;  
	  }
	  system("pause");
        int n,n1;	  
	while(1)
	{ p=L->next;   //指针复位 
	   n=0; 
	   system("cls");
	   cout<<"请输入社人学号"<<endl;
	   cin>>str;
	  while(p) 
	  {
	   if(str==p->data.ID)
	    {     p->data.shetuan=str1; 
		      p->data.integral=0;
	          p->data.rank=999;     //社团积分清空 
		 n=1; cout<<"入社完成"<<endl; break;
		}
	    p=p->next;
	  }
	    if(n==0)  cout<<"查无此人"<<endl;
	     cout<<"1:继续 2:完成"<<endl;
         cin>>n1; if(n1==2) break;
        
	}
}
void tuihe_Tree(char str[],ppList L)
{   ppList p=L->next;
     string str1=str,str2;  int n=0;
     while(1)
	{  system("cls");
	  cout<<"输入退社人员学号"<<endl;
	   p=L->next;
	   cin>>str2;
	   cout<<"退社人员: "<<endl;
	  while(p)
	  {  if(str2==p->data.ID&&str1==p->data.shetuan)
	      {   cout<<"学号："<<p->data.ID<<"姓名："<<p->data.name<<endl;
	          p->data.shetuan="无";
	          p->data.shenfen="社员";
	          p->data.integral=0;
	        n=1;  p->data.rank=999;  //社团积分清空 
	      }
		  p=p->next;  
	  }
	  if(n==0) cout<<"查无此人"<<endl;
	cout<<"1:继续 0：退出"<<endl; int n;cin>>n; if(n==0) break;
    }
}
void  display_Tree(char str[],ppList &L)
{
	ppList p=L->next;
	string str1=str;
	cout<<"社团人员"<<endl;
	while(p)
	{ 
	   if(p->data.shetuan==str1)
	   { 
	    cout<<p->data.shenfen<<":"<<endl;
	    cout<<"学号："<<p->data.ID<<"姓名："<<p->data.name<<endl;
        cout<<"积分:"<<p->data.integral<<endl;
	   } 
	   p=p->next;
	}
	system("pause");
}
void ganbu_Tree(char str1[],ppList &L)
{ ppList p=L->next;
  string str=str1,str2; int q=0,n;
    cout<<"输入要选举的职位"<<endl;
    cin>>str2;
    if(str2=="部长")  q=800;
     else if(str2=="副部长")q=600;
	  else {cout<<"输入错误"<<endl; return;}
     cout<<"满足条件的人员:"<<endl;
	while(p)
	{
		if(p->data.shetuan==str&&p->data.integral>=q)
		 { 
		  cout<<"学号："<<p->data.ID<<"姓名："<<p->data.name<<endl;
          cout<<"积分:"<<p->data.integral<<endl;   
          n=1;
		 }
        p=p->next;
	}
	if(n==0) { cout<<"无满足人员"<<endl; system("pause"); system("cls"); return;}
   p=L->next; //指针复位
     cout<<"请输入被选举人的学号"<<endl;
	  string str3;cin>>str3; 
	 while(p)
    {
    	if(p->data.shetuan==str&&p->data.integral>=q&&p->data.ID==str3)
    	 { 
		  cout<<"成员:"<<p->data.name<<endl;
          cout<<"身份由:"<<p->data.shenfen<<"->"<<str2<<endl;
          p->data.shenfen=str2; break;
		 }
		 p=p->next;
	}
}
void zanzhu_chushihua(zanzhu (&z)[5])
{   
    z[0].name="畅游公司";z[0].fuzeren="张1";z[0].wangzhi="www.lalal.com";z[0].jianjie="暂无";z[0].shetuan="学习部";z[0].shetuan2="暂无"; 
	z[1].name="蜗牛游戏";z[1].fuzeren="张2";z[1].wangzhi="www.lala2.com";z[1].jianjie="暂无";z[1].shetuan="暂无";z[1].shetuan2="暂无"; 
    z[2].name="盛大在线";z[2].fuzeren="张3";z[2].wangzhi="www.lala3.com";z[2].jianjie="暂无";z[2].shetuan="暂无";z[2].shetuan2="暂无"; 
    z[3].name="申通快递";z[3].fuzeren="张4";z[3].wangzhi="www.lala4.com";z[3].jianjie="暂无";z[3].shetuan="暂无";z[3].shetuan2="暂无"; 
    z[4].name="腾讯公司";z[4].fuzeren="张5";z[4].wangzhi="www.lala5.com";z[4].jianjie="暂无";z[4].shetuan="暂无";z[4].shetuan2="暂无"; 
    
}
zanzhu z[5];
void  zanzhu_Tree()
{    
    if(z[0].name!="畅游公司") zanzhu_chushihua(z);
	system("cls");cout<<"赞助商信息"<<endl; 
   for(int i=0;i<5;i++)
   { cout<<i+1<<": 公司名: "<<z[i].name<<" 负责人: "<<z[i].fuzeren<<" 简介: "<<z[i].jianjie<<endl;
     cout<<"网站: "<<z[i].wangzhi<<" 赞助社团1: "<<z[i].shetuan<<" 赞助社团2: "<<z[i].shetuan2;
      cout<<endl;
   }
   cout<<"1:赞助信息修改 0:退出"<<endl; 	
   int i;cin>>i;  if(i==0) return;
   cout<<"要修改的公司"<<endl;
   cin>>i; cout<<"进行修改的公司: "<<z[--i].name<<endl;
   system("pause"); system("cls");
   cout<<"请输入要修改的项目"<<endl;
   cout<<"1: 公司名"<<endl;
   cout<<"2：负责人"<<endl;
   cout<<"3：简介"<<endl;
   cout<<"4：网站"<<endl;
   cout<<"5：赞助社团1"<<endl;
   cout<<"6：赞助社团2"<<endl;
    int n;cin>>n;
   switch(n)
   {
   	case 1:  cout<<"请输入数据:"<<endl; cin>>z[i].name;  break;
   	case 2:  cout<<"请输入数据:"<<endl; cin>>z[i].fuzeren;  break;
   	case 3:  cout<<"请输入数据:"<<endl; cin>>z[i].jianjie; break;
   	case 4:  cout<<"请输入数据:"<<endl; cin>>z[i].wangzhi;  break;
   	case 5:  cout<<"请输入数据:"<<endl; cin>>z[i].shetuan; break;
   	case 6:  cout<<"请输入数据:"<<endl; cin>>z[i].shetuan2;  break;
   	 default: cout<<"输入错误"<<endl; break;
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
  if(i!=0) cout<<"积分为"<<average/i<<endl;
    else cout<<"积分为"<<average<<endl;
}
void renshiguanli(CTree &T,ppList &L)
{   
   cout<<"输入社团进入社团管理"<<endl;
     char str[20]; cin>>str; int n=0; int i,j;
    for(i=0;i<T.nodeNum;i++)
       if(strcmp(T.nodes[i].data.name,str)==0) { n=1; break;}
     if(n==0) { cout<<"无此社团"<<endl; return;}
	while(1)
	{
	system("cls");
	cout<<"1-社团信息修改"<<endl;
    cout<<"2-社团招新"<<endl;
    cout<<"3-人员退社"<<endl;
    cout<<"4-社团人员查看"<<endl;
    cout<<"5-干部选举资格查询"<<endl;
    cout<<"6-成员积分平均值查询"<<endl;
    cout<<"0-退出"<<endl;
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
	    default :  cout<<"输入错误"<<endl; i=0; cin.clear(); cin.sync();
		
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
		default:printf("输入错误\n");
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
    
    ifstream open("通讯录.txt");//读取文件
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
	cout<<"读取完成"<<endl;
}
void Member::filein(ppList &L)
{    
     ppList p;
     p=L->next;
     fstream fMember("通讯录.txt", ios::out);
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
	 cout<<"写入完成"<<endl;
	 system("pause");
}
int Member::GrateList(ppList &L)
{   L=new ppNode;
    L->next=NULL;
    L->prior=NULL;
	ppList p=L->next,r=L;
    SYSTEMTIME sys; 
	while(1)
    { GetLocalTime(&sys);//时间刷新 
	  p=new ppNode;
	  p->data.time_p.second=sys.wSecond;
	  p->data.time_p.minute=sys.wMinute;
      p->data.time_p.day=sys.wDay;
      p->data.time_p.mouth=sys.wMonth;
      p->data.time_p.year=sys.wYear;
      p->data.time_p.hour=sys.wHour;
      p->data.rank=0;
      p->data.integral=0;
      p->data.shetuan="无";
	  p->data.shenfen="社员"; 
      system("cls");
      cout<<"请开始输入学生信息"<<endl;
      cout<<"学号:  "<<endl;   cin>>p->data.ID;
      cout<<"姓名： "<<endl;   cin>>p->data.name;
      cout<<"性别： "<<endl;   cin>>p->data.sex;
      cout<<"专业班级： "<<endl; cin>>p->data.class_n;
      cout<<"联系电话； "<<endl; cin>>p->data.telephonenumber;
      cout<<"家庭住址： "<<endl; cin>>p->data.address;
	   p->next=NULL; r->next=p; p->prior=r; r=p;
	  int n; cout<<"1:继续输入 0：结束"<<endl; cin>>n; if(n==0) break;
      system("cls");
      cin.sync();
      cin.clear();
      	
	   
     //cin.ignore(888,'\n');//清除当前行
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
    { GetLocalTime(&sys);//时间刷新 
	  p=new ppNode;
	  system("cls");
      cout<<"请开始输入学生信息"<<endl;
      cout<<"学号:  "<<endl;   cin>>p->data.ID;
          while(q)
        { if(q->data.ID==p->data.ID)
            { cout<<"已经有此人信息"<<endl; n=1; system("pause");break;}
          q=q->next; 
		}
		if(n==1) {delete p; break;}
      cout<<"姓名： "<<endl;   cin>>p->data.name;
      cout<<"性别： "<<endl;   cin>>p->data.sex;
      cout<<"专业班级： "<<endl; cin>>p->data.class_n;
      cout<<"联系电话； "<<endl; cin>>p->data.telephonenumber;
      cout<<"家庭住址： "<<endl; cin>>p->data.address;
	  p->data.time_p.second=sys.wSecond;
	  p->data.time_p.minute=sys.wMinute;
      p->data.time_p.day=sys.wDay;
      p->data.time_p.mouth=sys.wMonth;
      p->data.time_p.year=sys.wYear;
      p->data.rank=999;
      p->data.integral=0;
	  p->next=L->next;  L->next=p; //p->prior=L; L->next->prior=p;
      int n; cout<<"0：结束"<<endl; cin>>n;
	  
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
  {   cout<<"学号:  "<<p->data.ID<<endl;  
      cout<<"姓名： "<<p->data.name<<endl;  
      cout<<"性别： "<<p->data.sex<<endl;  
      cout<<"专业班级： "<<p->data.class_n<<endl;
      cout<<"联系电话； "<<p->data.telephonenumber<<endl;
      cout<<"家庭住址： "<<p->data.address<<endl; 
      cout<<"所属社团   "<<p->data.shetuan<<endl;
      cout<<"入社时间： "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      p=p->next;
  }
  system("pause");
  system("cls");
  return OK;
}
int  Member::rankquery(ppList &L)
{  ppList p=L->next;
   cout<<"请输入学号"<<endl;
   string str; cin>>str;
   while(p)
   { if(p->data.ID==str)
     { 
      cout<<"成员等级:  "<<endl;
	  cout<<"学号:  "<<p->data.ID<<endl;  
      cout<<"姓名： "<<p->data.name<<endl;  
      cout<<"性别： "<<p->data.sex<<endl;  
      cout<<"专业班级： "<<p->data.class_n<<endl;
      cout<<"联系电话； "<<p->data.telephonenumber<<endl;
      cout<<"家庭住址： "<<p->data.address<<endl; 
      cout<<"入社时间： "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
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
  {  p=L->next;   //重置 
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
	  cout<<"第"<<i<<":"<<endl;
      cout<<"积分："<<p->data.integral<<"等级:  "<<p->data.integral/100<<endl;
	  cout<<"学号:  "<<p->data.ID<<endl;  
      cout<<"姓名： "<<p->data.name<<endl;  
      cout<<"性别： "<<p->data.sex<<endl;  
      cout<<"专业班级： "<<p->data.class_n<<endl;
      cout<<"联系电话； "<<p->data.telephonenumber<<endl;
      cout<<"家庭住址： "<<p->data.address<<endl; 
      cout<<"入社时间： "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      cout<<"所属社团:  "<<p->data.shetuan<<endl;
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
    cout<<"请输入要删除人的学号"<<endl;
	string people;
	cin>>people;
	while(p)
    { 
     if(people==p->data.ID)
      {
	    r->next=p->next;
        cout<<"删除人信息:"<<endl;
        cout<<"姓名:"<<p->data.name<<endl;
        cout<<"性别:"<<p->data.sex<<endl;
        cout<<"学号:"<<p->data.ID<<endl;
		delete p;   //释放空间    
		n=1;
	  }
	  p=p->next;
	}
	if(n==0) cout<<"未找到此人"<<endl;
	 else cout<<"删除成功"<<endl;
	system("pause");
   return OK;
}
int Member::sort_1(ppList &L,ppList p)
{   cout<<"*****"<<endl;
   //cout<<p->data.name<<"***"<<endl;
   int m_1=p->data.integral,m_2=1,n=0; // cout<<"此时积分为"<<m_1<<endl;
   ppList q=L->next; 
   while(q!=NULL)
   {     
   if(q->data.integral>m_1&&q->data.rank>=m_2)
      { m_2=q->data.rank;  n=1;}
	   //cout<<q->data.integral<<"-----   m2:"<<m_2<<endl;
     q=q->next;
   }        //找到要查入的排序位置  
              if(n==1) m_2++;
          //  cout<<"插入位置为"<<m_2<<endl;          
     q=L->next;
   while(q)
    {     
      if(q->data.rank>=m_2&&q->data.rank<p->data.rank)
        { 
		  q->data.rank++;// cout<<q->data.name<<":"<<q->data.rank;
		}  
	    q=q->next;      
    } //将位置后的位置后移 
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
    }        //找到要查入的排序位置  
              if(n==1) m_2--;
           // cout<<"插入位置为"<<m_2<<endl;          
     q=L->next;
   while(q)
    {     
      if(q->data.rank<=m_2&&q->data.rank>p->data.rank)
        { 
		  q->data.rank--;// cout<<q->data.name<<":"<<q->data.rank;
		}  
	    q=q->next;      
    }  //将位置前的位置前移 
     p->data.rank=m_2;
	return 0;
}
int  Member::add_integral(ppList &L) 
{   ppList  p=L->next;;
	string people; int n_1=-1,n_2=0,n_3=0;
	while(1)
   {	system("cls");
      cout<<"请输入学号"<<endl;
	    cin>>people; 
          p=L->next;   n_1=-1,n_2=0,n_3=0;
   	while(p)
    {  
     if(people==p->data.ID)
      { cout<<"个人信息:"<<endl;
        cout<<"姓名:"<<p->data.name<<endl;
        cout<<"性别:"<<p->data.sex<<endl;
        cout<<"学号:"<<p->data.ID<<endl;
		cout<<"1:确定个人信息 2:重新输入"<<endl;
		 cin>>n_3;
		 if(n_3==1)
		{   n_2=1;  //标志找到 
		 cout<<"请输入要增加的积分"<<endl;   
	     cin>>n_1;
	     p->data.integral+=n_1;
		}
		else if(n_3==2)
		{  
		  n_2=-1;
		}
        else  cout<<"输入错误"<<endl; 
		break; 
	  }
	  p=p->next;
	}
	if(n_2==-1)    continue;  //重置标识 
	if(n_2==0)    {cout<<"未找到此人"<<endl; continue;}
	 if(n_1>0) sort_1(L,p);
	  else if(n_1<0) sort_2(L,p);
	 cout<<"0:停止 1:继续"<<endl;
	 cin>>n_1; if(n_1==0) break;
   }
   //对增加积分的人重排序 
   cout<<"计分完成"<<endl;
	system("pause");
    return OK;   
}

int   Member::change(ppList &L)
{    ppList p=L->next;
    cout<<"请输入学号"<<endl;
	string people;  cin>>people; int i,n=0;
		while(p)
    { 
     if(people==p->data.ID)
      {  cout<<"输入您要修改的项："<<endl;
      cout<<"1-积分： " <<p->data.integral<<endl;
	  cout<<"2-学号:  "<<p->data.ID<<endl;  
      cout<<"3-姓名： "<<p->data.name<<endl;  
      cout<<"4-性别： "<<p->data.sex<<endl;  
      cout<<"5-专业班级： "<<p->data.class_n<<endl;
      cout<<"6-联系电话； "<<p->data.telephonenumber<<endl;
      cout<<"7-家庭住址： "<<p->data.address<<endl; 
      cout<<"入社时间： "<<p->data.time_p.year<<":"<<p->data.time_p.mouth<<":"<<p->data.time_p.day<<":"
	                     <<p->data.time_p.hour<<":"<<p->data.time_p.minute<<":"<<p->data.time_p.second<<endl;
      cin>>i;
	    switch(i)
		{
		  case 1:  cout<<"请输入"<<endl;  i=8; n=p->data.integral; cin>>p->data.integral;break;
		  case 2:  cout<<"请输入"<<endl;   cin>>p->data.ID; break;
		  case 3:  cout<<"请输入"<<endl;   cin>>p->data.name; break;
		  case 4:  cout<<"请输入"<<endl;   cin>>p->data.sex;break;
		  case 5:  cout<<"请输入"<<endl;   cin>>p->data.class_n; break;
		  case 6:  cout<<"请输入"<<endl;   cin>>p->data.telephonenumber; break;
		  case 7:  cout<<"请输入"<<endl;   cin>>p->data.address; break;
		   default :  cout<<"输入错误"<<endl; i=0; cin.clear(); cin.sync();
		} 
		break;
	   }
		p=p->next;
	  
    } 
    if(i==0) cout<<"修改失败"<<endl;
       else  cout<<"修改成功"<<endl;
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
	cout<<"1；通讯录总览"<<endl;
    cout<<"2：积分降序查看"<<endl;
    cout<<"3：增加成员"<<endl;
    cout<<"4：删除成员"<<endl;
    cout<<"5: 成员积分添加"<<endl;
	cout<<"6：成员信息修改"<<endl;
    cout<<"0: 退出"<<endl;
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
        default : cout<<"输入错误 !!"<<endl; cin.clear();cin.sync();break;
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
     G.vex[0].description="  ▲ 暂无";
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
    cout<<"1：成员信息管理"<<endl;
    cout<<"2：社团信息管理"<<endl;
    cout<<"3: 活动管理导航"<<endl;
    cout<<"0: 退出"<<endl;
	cin>>i;
    switch(i)
     { 
	  case 1:show_ppList(cc,L); break;
	  case 2:show_Tree(L); break;
	  case 3: daa();break;
	  case 0: return 1 ;
	   default : cout<<"输入错误 !!"<<endl; cin.clear();cin.sync();break;
     } 
    }
   cc.filein(L);
	return 0;
}
