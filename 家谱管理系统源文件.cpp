#include <stdio.h>
#include <iostream>
using namespace std;
typedef struct node//定义data存储结构
{
	char name[10];//家族成员姓名
	char sex;//家族成员性别
	char mate[10];//家族成员配偶姓名
	int generation;//家族成员代数
}node;

typedef struct btnode//定义二叉树数据结构
{
	struct node l;//家谱中直系家属
	struct btnode *brother;//用来指向兄弟
	struct btnode *child;//用来指向孩子
}btnode;


btnode *search (btnode *p,char ch[]);//搜索指针函数，搜索需要修改和获得的节点，输入头指针和姓名
int generation(btnode *p,char ch[]);//获得搜索道德成员的代的的返回值
void children (btnode *p,char b[],char c,int d,char e[]);//建立家谱孩子节点
void output(btnode *n);//搜索到数据的输出
void Search();
void Print(btnode *p);
void Add();
void Delete();
void Inittree();
void Change();
int getdepth(btnode *t);
void lookbrother(btnode *t);
void lookparent (btnode *t,btnode *n);

btnode *root;

void display0()
{
	system("color 6f");
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             家谱管理系统                                   *"<<endl;
	cout<<"       *                                                     by  Archie             *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	cout<<"\n"<<endl;
	cout<<"                     欢迎使用本系统"<<endl;
	cout<<"                     请根据你的需要输入相应序号。若第一次使用，请先初始化家谱\n"<<endl;
	cout<<"                     请注意：本系统不支持存储同名成员 \n\n"<<endl;
	cout<<"                     1、初始化家谱\n"<<endl;
	cout<<"                     2、查看祖先和祖孙的信息\n"<<endl;
	cout<<"                     3、添加家族成员\n"<<endl;
	cout<<"                     4、修改家族成员\n"<<endl;
	cout<<"                     5、删除家族成员\n"<<endl;
	cout<<"                     6、打印家谱\n"<<endl;
	cout<<"                     7、退出本系统\n"<<endl;
	int n,depth;
	scanf("%d",&n);
	while(!n)
	{
		cout<<"                       输入的数字无效！请重新输入"<<endl;
		scanf("%d",&n);
	}
	while(n<1||n>7)
	{
		cout<<"                       输入的数字无效！请重新输入"<<endl;
		scanf("%d",&n);
	}
	switch(n)
	{
	case 1:
		Inittree();
		system("pause");
		break;
	case 2:
		Search();
		system("pause");
		break;
	case 3:
		Add();
		system("pause");
		break;
	case 4:
		Change();
		system("pause");
		break;
	case 5:
		Delete();
		system("pause");
		break;
	case 6:
		Print(root);
		system("pause");
		printf("\n按任意键返回主菜单");
		system("pause");
		getchar();
		display0();
	case 7:
		exit(0);
		break;
	}
}

btnode *search (btnode *p,char ch[])
{
	btnode *q;
	if(p==NULL)
		return NULL;//没有家谱，头指针下为空
	if(strcmpi(p->l.name,ch)==0)
		return p;
	if(p->brother)
	{
		q=search(p->brother,ch);
		if(q)
			return q;
	}
	if(p->child)
	{
		q=search(p->child,ch);
		if(q!=NULL)
			return q;
	}
	return NULL;
}
int generation(btnode *p,char ch[])
{
	btnode *q;
	if(p==NULL)
		return 0;
	if(strcmpi(p->l.name,ch)==0)
		return p->l.generation;
	if(p->brother)
	{
		q=search(p->brother,ch);
		if(q)
			return q->l.generation;
	}
	if(p->child)
	{

	}q=search (p->child,ch);
	if(q!=NULL)
		return q->l.generation;
	return 0;
}
void children (btnode *p,char b[],char c,int d,char e[])
{
	for(int i=0;i<10;i++)
	{
		p->l.name[i]=b[i];
		p->l.mate[i]=e[i];
		p->l.sex=c;
		p->l.generation=d;
	}
}
void Inittree()
{
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             初始化家谱.....                                *"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	int a;
	char b[10],c,d[10];
	printf("请依次输入始祖的姓名和性别（女士f，男士m）以及配偶姓名");
	free(root);
	root=new btnode;
	scanf("%s %c %s",&b,&c,&d);
	while(c!='m'&&c!='f')
	{
		cout<<"输入性别有误！请重新依次输入姓名和性别（女士f，男士m）以及配偶姓名"<<endl;
		scanf("%s %c %s",&b,&c,&d);
	}
	a=1;
	root->child=NULL;
	root->brother=NULL;
	children (root,b,c,a,d);
	printf("家谱初始化成功！已返回主菜单\n");
	display0();
}
void output(btnode *n)
{
	btnode *t=NULL;
	
	printf("此人姓名：%s 性别：%c  为第%d代,其配偶是%s \n",n->l.name,n->l.sex,n->l.generation,n->l.mate);
	printf("\n");
	if(n->child==NULL)
	{
		printf("此人无子女");
	}
	else 
	{
		printf("此人的子女:");
		if(n->child->brother==NULL)
		{
			printf("姓名：%s 性别：%c\t",n->child->l.name,n->child->l.sex);
		}
		else 
		{
			printf("姓名：%s 性别：%c\t",n->child->l.name,n->child->l.sex);
			t=n->child->brother;
			while(t!=NULL)
			{
				printf("姓名：%s 性别：%c\t",t->l.name,t->l.sex);
				t=t->brother;
			}
		}
	}
	printf("\n");
	if(n->brother==NULL)
	{
		printf("此人无同辈成员\n");
	}
	else
	{
		printf("此人的同辈成员：");
		if(n->brother->brother==NULL)
		{
			printf("姓名：%s 性别：%c\t",n->brother->l.name,n->brother->l.sex);
		}
		else 
		{
			printf("姓名：%s 性别：%c\t",n->brother->l.name,n->brother->l.sex);
			t=n->brother->brother;
			while (t!=NULL)
			{
				printf("姓名：%s 性别：%c\t",t->l.name,t->l.sex);
				t=t->brother;
			}
		}
	}
	lookparent(root,n);
	printf("\n按任意键返回主菜单");
		system("pause");
		getchar();
		display0();
}
void Search()
{
	btnode *n;
	char d[10];
	printf("输入姓名，系统将查找其相关信息");
	scanf("%s",&d);
	n=search(root,d);
	while(n==NULL)
	{
		printf("被查找人不存在，请重新输入");
		scanf("%s",&d);
		n=search(root,d);
	}
	output(n);
	printf("\n");
	printf("\n按任意键返回主菜单");
	system("pause");
	getchar();
	
	display0();
}

int getdepth(btnode *t)
{
	if (!t)
	{
		return 0;
	}
	int ldepth=getdepth(t->child)+1;
	int rdepth=getdepth(t->brother)+1;
	return ldepth>rdepth?ldepth:rdepth;
}
void lookbrother(btnode *t)
{
	if(t!=NULL)
	{
		printf("%s ",t->l.name);
		lookbrother(t->brother);
	}
}

void lookparent (btnode *t,btnode *n)
{
		if(strcmp(t->child->l.name,n->l.name)==0)
		{
			printf("此人的父母是：%s，%s\n",t->l.name,t->l.mate);
			system("pause");
			return;
		}
		lookparent(t->child,n);
		lookparent(t->brother,n);
		
}
void Print(btnode *p)
{
	if(strcmp(p->l.name," ")!=0)
	{
		
		printf("第%d代的%s的孩子有：\n",p->l.generation,p->l.name);
		lookbrother(p->child);
		printf("\n");
	}
	if(p->child)
		Print(p->child);
	if(p->brother)
		Print(p->brother);
}
	


void Delete()
{
	btnode *p;
	char ch[10];
	cout<<"请输入你想要删除的成员姓名"<<endl;
	cin>>ch;
	p=search(root,ch);
	if(p==NULL)
	{
		printf("系统中未检测到此人，无法删除");
		printf("请重新输入你想要删除的成员姓名");
		cin>>ch;
	    p=search(root,ch);
	}
	p->child=NULL;
	strcpy(p->l.name," ");
	printf("已删除目标成员\n");
	printf("\n按任意键返回主菜单");
		system("pause");
		getchar();
		display0();

}

void Add()
{
	int a;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       *                             开始添加家庭成员                               *"<<endl;
	cout<<"       *                                                                            *"<<endl;
	cout<<"       ******************************************************************************"<<endl;
	cout<<"\n"<<endl;
	btnode *n,*m,*t=NULL;
	char b[10],c,d[10],e[10];
	printf("请输入要添加成员的上一辈的姓名");
	scanf("%s",&d);
	n=search (root,d);
	a=generation(root,d);
	while(n==NULL)
	{
		printf("此人不在家谱内，请重新输入姓名");
		scanf("%s",&d);
		n=search (root,d);
	}
	if(n->child==NULL)
	{
		printf("请输入所添加家庭成员的姓名与性别（注意不能重名）以及配偶名字");
		scanf("%s %c %s",&b,&c,&e);
		while(c!='m'&&c!='f')
	{
		cout<<"输入性别有误！请重新输入姓名和性别（女士f，男士m）以及配偶名字"<<endl;
		scanf("%s %c %s",&b,&c,&e);
	}
		a++;
		m=search(root,b);
		if(m!=NULL)
		{
			printf("检测到重名，添加失败！");
		}
		else 
		{
			n->child=new btnode;
			n->child->brother=NULL;
			n->child->child=NULL;
			children(n->child,b,c,a,e);
			printf("添加成功！\n");
		}
	}
	else
	{
		n=n->child;
		while (n->brother!=NULL)
			n=n->brother;
		printf("请输入所添加家庭成员的姓名与性别（注意不能重名）以及配偶姓名");
		scanf("%s %c %s",&b,&c,&e);
		while(c!='m'&&c!='f')
			{
		cout<<"输入性别有误！请重新输入姓名和性别以及配偶姓名！（女士f，男士m）："<<endl;
		scanf("%s %c %s",&b,&c,&e);
			}
		a++;
		for(int i=0;i<8;i++)
		{
			n->l.mate[i]=e[i];
		}
		m=search(root,b);
		if(m!=NULL)
		printf("检测到重名，添加失败！");
		else
		{
			t=new btnode;
			children(t,b,c,a,e);
			t->brother=NULL;
			t->child=NULL;
			n->brother=t;
			printf("添加成功！\n");
		}
	}
	printf("\n按任意键返回主菜单\n");
	system("pause");
	getchar();
	display0();
}

void Change()
{
	char a[10],r[10],c;
	btnode *n;
	int i;
	printf("请输入要修改人的姓名");
	scanf("%s",&a);
	n=search(root,a);
	while(n==NULL)
	{
		printf("此人不存在，请重新输入姓名");
		scanf("%s",&a);
		n=search(root,a);
	}
	printf("已查询到目标，请输入要修改的新信息（新名字和性别）");
	scanf("%s %c",&r,&c);
	while(c!='m'&&c!='f')
	{
		cout<<"输入性别有误！请重新输入姓名和性别！（女士f，男士m）："<<endl;
		scanf("%s %c",&r,&c);
	}
	for(i=0;i<10;i++)
		n->l.name[i]=r[i];
	n->l.sex=c;
	printf("修改成功已返回主菜单\n");
	display0();
}



int main()
{
	display0();
	return 0;
}