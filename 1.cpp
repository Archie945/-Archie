#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>
struct elevator
{
    int present;//电梯现在所在楼层
    int aim;//电梯要到的楼层
    int move;//电梯走的楼层数
}lift[4];
void show();//电梯目录显示

int elevator_choice();//乘客选择
int elevator_panduan(int now, int future);//判断电梯

int Short1(int ele[], int fu, int nw);//偶数层找出相差最小的电梯
int Short2(int ele[], int fu, int nw);//奇数层找出相差最小的电梯

int Diff(int a, int b);//求两个数的差值
int elevator_run(int i, int now, int aim1);//改变电梯运行
void shuaxin();//电梯行走

void main()
{

    int num = 1;
    while (num == 1)
    {
        show();
        num=elevator_choice();
    }
}
int elevator_choice()
{
    int floors;//当前楼层数
    int aim;//想到达的层数
    int num;
    printf("0层是地下一层，顶层为20楼\n");
    printf("请输入你所在的楼层数：");
    scanf_s("%d", &floors);
    if (floors > 20)
        floors = 20;
    printf("请输入你想到达的层数：");
    scanf_s("%d", &aim);
    if (aim > 20)
        aim = 20;
    printf("\n");
    num=elevator_panduan(floors, aim);
    return num;
}
int elevator_panduan(int now, int future)
{
    int i, a[3];
    if (now % 2 == 0)
    {
        a[0] = 0; a[1] = 2; a[2] = 3;
        i = Short1(a, future, now);//偶数返回使用的电梯。
    }
    else if (now % 2 == 1)
    {
        a[0] = 0; a[1] = 1; a[2] = 3;
        i = Short2(a, future, now);//奇数返回使用电梯号。
    }
    printf("欢迎乘坐%d号电梯\n", i + 1);
    int num=elevator_run(i, now, future);
    return num;

}

int Short1(int ele[], int fu, int nw)//找出使用哪个电梯1 偶数楼层开始判断
{

    int min = ele[0];

    int k = Diff(lift[min].present, nw);

    if (fu % 2 == 0)
    {
        for (int i = 1; i < 3; i++)
        {
            if (k > Diff(lift[ele[i]].present, nw))
            {
                k = Diff(lift[ele[i]].present, nw);
                min = ele[i];
            }
        }
        return min;
    }
    if (fu % 2 == 1)
    {
        int y = Diff(lift[3].present, nw);
        if (k > y)
        {
            return 3;

        }
        else
        {
            return 0;

        }
    }
}
int Short2(int ele[], int fu, int nw)//找出使用哪种电梯2 奇数楼层开始判断
{
    int min = ele[0];
    int k = Diff(lift[min].present, nw);
    if (fu % 2 == 1)
    {
        for (int i = 1; i < 3; i++)
        {
            if (k > Diff(lift[ele[i]].present, nw))
            {
                k = Diff(lift[ele[i]].present, nw);
                min = ele[i];
            }
        }
        return min;
    }
    if (fu % 2 == 0)
    {
        int y = Diff(lift[3].present, nw);
        if (k > y)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
}

void show()//显示楼层
{
    system("cls");
    printf("电梯\t当前楼层 \t状态\n");
    for (int i = 0; i < 4; i++)
    {
        printf("%d\t",i+1);
        printf("%d\t\t", lift[i].present);
        if (lift[i].move>0)
            printf("↑\n");
        else if (lift[i].move == 0)
            printf("--\n");
        else printf("--\n");
    }
}

int Diff(int a, int b)//求差
{
    if (a > b)
    {
        return a - b;
    }
    else
    {
        if (a < b)
        {
            return b - a;
        }
    }
}

int elevator_run(int i, int now, int aim1)//运行电梯
{
    lift[i].aim = now;
    lift[i].move = Diff(lift[i].present, lift[i].aim);
    int k = lift[i].move;
    if (k == 0)
    {
        lift[i].aim = aim1;
        lift[i].move = Diff(lift[i].present, lift[i].aim);
        int k = lift[i].move;
    }
    int m = 2;
    while (m == 2)
    {
        show();
        shuaxin();
        printf("乘坐电梯请按1，刷新请按2，退出请按任意键");
        scanf_s("%d", &m);
    
        if (lift[i].move == 0)
        {
            if (lift[i].aim == aim1)
                lift[i].move = 0;
            else
            {
                lift[i].aim = aim1;
                lift[i].move = Diff(lift[i].present, lift[i].aim);
            }
        }
    }
    if (m == 1)
        return 1;
    else
        return 0;
}
void shuaxin()
{
    for (int y = 0; y < 4; y++)
    {
        if (lift[y].aim > lift[y].present)
        {
            lift[y].present++;
            lift[y].move--;
        }
        else if (lift[y].aim < lift[y].present)
        {
            lift[y].present--;
            lift[y].move--;
        }
    }
}