#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include"readstack.c"
int manu1();
int manu21();
int manu22();
int manu1()//主界面
{
    system("cls");//清屏
    printf("|                                        |\n");
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|------------select your mode------------|\n");
    printf("|                                        |\n");
    printf("|--------1.imput from your keyboard------|\n");
    printf("|--------2.read from your file-----------|\n");
    printf("|                                        |\n");  
    printf("|                                        |\n");
    printf("|                                        |\n");  
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n");  
    printf("select your mode(1~2):");
    int select;
    scanf("%1d",&select);
    fflush(stdin);
    switch(select){
        case 1:{
            manu21();
            break;
        }
        case 2:{
            manu22();
            break;
        }
        default:{
            printf("Error,please select from 1~2!\n");
            printf("press any key to continue……");
            getch();
            break;
        }
    }
    return 0;
}
int manu21()//模式1，以键盘输入形式读，只能进行两个值的计算
{
    system("cls");
    printf("|                                        |\n");
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|----input your operation and numbers----|\n");
    printf("|                                        |\n");
    printf("|---------------1.add--------------------|\n");
    printf("|---------------2.subtract---------------|\n");
    printf("|---------------3.multiply---------------|\n");
    printf("|---------------4.divide-----------------|\n");
    printf("|---------------5.remainder--------------|\n");
    printf("|                                        |\n");  
    printf("|                              0.exit    |\n");
    printf("|                                        |\n");  
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n");  
    printf("choose your operation(0~5):");
    int op;
    scanf("%1d",&op);
    fflush(stdin);//scanf会残留\n在缓冲区
    if(op==exite){//输入0后退出
        return 0;
    }
    if(op!=adde&&op!=sube&&op!=multe&&op!=divie&&op!=reme){
        printf("Error,please select from 1~2!\n");
        printf("press any key to continue……");
        getch();
        return 0;
    }
    printf("Imput your first bumber:");
    struct number as,bs;//c语言不能传递数组，只能以结构传输   
    int i;
	for(i=0;i<size;i++){
        as.num[i]='\0';
        bs.num[i]='\0';
    }
    gets(as.num);
    printf("Imput your second number:");
    gets(bs.num);
    
	double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
    count(as,bs,op,1);
	QueryPerformanceCounter(&time_over);	//计时结束
	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
    printf("run in %f us \n", run_time );
    printf("press any key to continue……");
    getch();//实现摁任意键继续，在<conio.h>里，不回显
    return 0;
}

int manu22()//模式2，以读文件的形式读，可以进行多步计算，可以算多个式子
{
    system("cls");
    printf("|                                        |\n");
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|------Input file name/file address------|\n");
    printf("|                                        |\n");  
    printf("|                              0.exit    |\n");
    printf("|                                        |\n");  
    printf("|---------------calculator---------------|\n");
    printf("|                                        |\n"); 
    char loc1[100],loc2[100];
    FILE *read,*write;
    printf("open : ");
    gets(loc1);
    if(loc1[0]=='0'){
        return 0;
    }
    else{
        read=fopen(loc1,"r");//读取大数运算式
        if(read==NULL){
            printf("File can not open!\n");
            printf("press any key to continue……");
            getch();
            return 0;
        }
    }

    struct number result[100];//一百组大数运算以内
    double run_time;
	LARGE_INTEGER time_start;	//开始时间
	LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
    int i=0;
    while(feof(read)==0){
        result[i]=read1(read);//把结果存下来
        i++;
    }
    QueryPerformanceCounter(&time_over);	//计时结束
	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
    printf("run in %f us \n", run_time );
    
    rewind(read);//读文件的指针回到开头
    printf("save as : ");
    gets(loc2);
    write=fopen(loc2,"w");
    if(write==NULL){
        printf("File can not create!\n");
        printf("press any key to continue……");
        getch();
        return 0;
    }
    i=0;
    while(feof(read)==0){
        char function[10*size];
        fscanf(read,"%s\n",function);//读取大数运算式，忽略回车读取，自动读下一行
        fprintf(write,"%s%s\n",function,result[i].num);//将大数运算式和结果一并输出，添加\n换行
        i++;
    }
    fclose(read);
    fclose(write);
    printf("the results are stored in %s……\n",loc2);//可将存储的文件名展现出来
    printf("press any key to continue……");
    getch();//实现摁任意键继续，在<conio.h>里，不回显
    return 0;
}
int main()
{   
    while(1)
        manu1();//可循环执行的主函数，极简主义！
    system("PAUSE");
    return 0;
}