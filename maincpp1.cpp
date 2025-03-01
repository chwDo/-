#include "heard.h"
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
		is >>p->data.address>> p->data.class_n>>p->data.ID >> p->data.integral >> p->data.name >> p->data.rank >> p->data.sex >> p->data.telephonenumber>>p->data.time_p.day>>p->data.time_p.hour>>p->data.time_p.minute>>p->data.time_p.mouth>>p->data.time_p.second>>p->data.time_p.year;
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
	  fMember <<p->data.address<<" "<< p->data.class_n<<" "<<p->data.ID <<" "<< p->data.integral <<" "<< p->data.name <<" "<< p->data.rank <<" "<<p->data.sex <<" "<< p->data.telephonenumber<<" "<<p->data.time_p.day<<" "<<p->data.time_p.hour<<" "<<p->data.time_p.minute<<" "<<p->data.time_p.mouth<<" "<<p->data.time_p.second<<" "<<p->data.time_p.year<<endl;
	   p=p->next;

	 }
	 	
	 fMember.close();
	 cout<<"写入完成"<<endl;
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
	 //cin.clear();
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
	  p->next=L->next;   L->next=p;
      int n; cout<<"1:继续输入 0：结束"<<endl; cin>>n; if(n==0) break;
      
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
  }*/
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
            cout<<"插入位置为"<<m_2<<endl;          
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
     system("pause");
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
		 cout<<"请输入要增加的学分"<<endl;   
	     cin>>n_1;
	     p->data.integral+=n_1;
		}
		else if(n_3==2)
		{  n_2=-1;
		}
        else  cout<<"输入错误"<<endl; 
        cout<<"n_2"<<n_2<<endl;
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
    cout<<"7: 退出"<<endl;
    cout<<""<<endl;
	cin>>n;
	switch(n)
     {
    	case 1:    cc.display_member(L); break;
    	case 2:    cc.ranksort(L);  break;
    	case 3:    cc.InsertList(L); break;
    	case 4:    cc.delete_ppList(L); break;
    	case 5:    cc.add_integral(L); break;
    	case 6:    cc.change(L);  break;
    	case 7:    n=-1; break;
	 }
   }
    
}
int main()
{   Member cc;  ppList L;
   //cc.GrateList(L);
    cc.fileout(L);
    show_ppList(cc,L);
	cc.filein(L);
	return 0;
}
