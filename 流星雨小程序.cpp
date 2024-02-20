#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<conio.h>

#include<easyx.h>//图形库
//注：凡是用easyx图形库的字符串都要用_T()函数来转换。


//导入播放音乐所需文件
#include<MMSystem.h>
#pragma comment(lib,"winmm.lib")


//定义结构体，弄星星
#define Start 500
#define liu 60

struct Star
{
	int x,y,r,speed;
	COLORREF color;
}star[Start];

struct liuXin
{
	int x,y,speed;
}liuX[liu];

//初始化星星
void xin(int i)
{
	star[i].x=rand()%getwidth();
	star[i].y=rand()%getheight();
	star[i].r=rand()%3+1;
	star[i].speed=rand()%5;
	star[i].color=RGB(rand()%256,rand()%256,rand()%256);
}
//绘制小星星
void drawXin()
{
	for(int i=0;i<Start;i++)
	{
		
		//putpixel(star[i].x,star[i].y,star[i].color);//绘制像素点
		setfillcolor(star[i].color);//设置星星颜色
		solidcircle(star[i].x,star[i].y,star[i].r);//绘制圆,第三个参数为半径
	}
}
// 移动星星
void moveXin()
{
	for(int i=0;i<Start;i++)
	{
		star[i].x+=star[i].speed;
		if(star[i].x>getwidth())
			star[i].x=0;
	}
}

//流星
IMAGE img[2],a[2];

#define SIZE 55
void loadImg()
{
	//加载图片//SRCPAINT参数可以让图片背景不把其他背景遮盖点
	loadimage(img+0,_T("img/259.jpg"),SIZE,SIZE);//图片数组地址 图片地址 图片宽度 图片高度
	loadimage(img+1,_T("img/258.png"),SIZE,SIZE);
}
using namespace std;

//初始化流量
void Liu(int i)
{
	//0~1200
	liuX[i].x=rand()%(getwidth()*2)-getwidth();
	liuX[i].y=-100;
	liuX[i].speed=rand()%16+1;
}
//画流量
void drawLiu()
{
	for(int i=0;i<liu;i++)
	{
		putimage(liuX[i].x,liuX[i].y,img+rand()%2,SRCPAINT);//输出图片，  离左边办距离 与上边界距离
	}
		
}

//移动流星
void moveLiu()
{
	for(int i=0;i<liu;i++)
	{
		liuX[i].x+=liuX[i].speed;
		liuX[i].y+=liuX[i].speed;
		if(liuX[i].x>getwidth()||liuX[i].y>getheight())
		{
			liuX[i].x=rand()%(getwidth()*2)-getwidth();
			liuX[i].y=-100;
		}
	}
}

#define Text1 "天道酬勤!"
#define Text2 "不抛弃不放弃!"
#define Text3 "Never never give up!"
#define Text4 "笑对未来，勇往直前!"
#define Text5 "如果事与原违，那一定另有安排!"

void welcome()
{

	//导入音乐  mci(media device interface)多媒体设备接口
	mciSendString(_T("open ./music/LYQ.mp3"),NULL,0,NULL);//第一个参数为字符串，指给多媒体设备的指令,后面的三个参数不用管，赋NULL 0 NULL即可
	mciSendString(_T("play ./music/LYQ.mp3"),NULL,0,NULL);

	//文本输出中能用outtextxy
	//_T(string *s) 此函数可以将其字符串进行转换
	srand(time(NULL));
	//字体高度 字体宽度（若设置为0表自适应） 字体名

	//设置背景模式为透明
	setbkmode(TRANSPARENT);//transparent，此模式保持文字背景色不变

	//窗口宽度 getwidth(); 文本宽度：textwidth(a);

	int T1=(getwidth()-textwidth(_T(Text1)))/2-textwidth(_T(Text1))*2;
	int T2=(getwidth()-textwidth(_T(Text2)))/2-textwidth(_T(Text2))*2;
	int T3=(getwidth()-textwidth(_T(Text3)))/2-textwidth(_T(Text3))*2;
	int T4=(getwidth()-textwidth(_T(Text4)))/2-textwidth(_T(Text4))*2;
	int T5=(getwidth()-textwidth(_T(Text5)))/2-textwidth(_T(Text5))*2;


	//返回随机数rand()但要种种子，方法和C一样
	//设置文字颜色settextcolor

	//是否按键，是为1，不是为0
	while(!_kbhit())
	{
		//清屏
		cleardevice();
		//system("cls");
		putimage(0,0,a+0);
		cout<<"Good";
		settextcolor(RED);//可以是颜色的英文，也可以用RGB（int,int,int）来定义指定的颜色
		//outtextxy(Tx,0,_T("Hello Everone！"));//离左边界的距离  离上边界的距离  输出的文本

		settextcolor(RGB(rand()%256,rand()%256,rand()%256));
		settextstyle(80,0,_T("华文行楷"));
		outtextxy(T1,0,_T(Text1));
		outtextxy(T2,150,_T(Text2));
		settextstyle(80,0,_T("华文彩云"));
		outtextxy(T3,300,_T(Text3));
		settextstyle(80,0,_T("华文行楷"));
		outtextxy(T4,450,_T(Text4));
		outtextxy(T5,600,_T(Text5));

		for(int i=0;i<20;i++)
		{
			settextcolor(RGB(rand()%255,rand()%255,rand()%255));
			outtextxy(rand()%getwidth(),rand()%getheight(),_T("❤"));
		}

		Sleep(1000);//延迟函数，形参为毫秒
	}
}

int main()
{
	
	//1.创建图形窗口
	initgraph(1500,800);//宽 高
	//设置背景颜色
	setbkcolor(BLACK);
	
	//加载背景图片
	loadimage(a+0,_T("img/g1.jpg"),getwidth(),getheight());
	loadimage(a+1,_T("img/bk.jpg"),getwidth(),getheight());

	for(int i=0;i<Start;i++)
	{
		xin(i);
	}

	for(int i=0;i<liu;i++)
	{
		Liu(i);
	}

	welcome();
	loadImg();

	
	//双缓冲绘图，解决闪屏问题
	BeginBatchDraw();

	while(1)
	{
		cleardevice();
		putimage(0,0,a+1);

		drawXin();
		moveXin();

		drawLiu();
		moveLiu();

		Sleep(20);
		FlushBatchDraw();
	}

	EndBatchDraw();


	return 0;
}