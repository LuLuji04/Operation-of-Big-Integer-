#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>//有getch()
#define size 1000
enum{exite,adde,sube,multe,divie,reme,eque};//退出，加，减，乘，除，取余，等于
struct number//大数以结构的形式存储（符号，数据，长度）
{
    signed int sign;//正数1，负数-1
    char num[size];//char存储，便于按位输入输出
    int len;//很重要，用于判断数据结尾在什么地方
};
void reverse(char* left,char* right)
{
    while(left < right)//只有当左边的地址小于右边的地址时，才交换，中间的不需要交换
    {
        char tmp = 0;
        tmp = *left;
        *left = *right;
        *right = tmp;
        left++;
        right--;
    }
}
void dete(struct number *a)//检测符号，使数据数组存的是绝对值，确定符号位
{
    int i;
    if(a->num[0]=='-'){
        a->sign=-1;
        for(i=0;i<a->len-1;i++){
            a->num[i]=a->num[i+1];
        }
        a->num[a->len-1]='\0';
        a->len--;
    }
    else
        a->sign=1;
}
int compare(struct number *a,struct number *b)//比大小，除法要用
{
    if(a->len>b->len)
        return 1;        
    else if (a->len<b->len)
        return -1;
    else{
        int i;
        for(i=a->len-1;i>=0;i--){
            if(a->num[i]>b->num[i]){
                return 1;
            }
            if (a->num[i]<b->num[i]){
                return -1; 
            }              
        }
        return 0;
    }
}
void output(struct number *a)//检测符号，以判断是否需加上负号输出
{
    if(a->sign==-1){
        int i;
        for(i=a->len;i>=0;i--)//从a->len开始，\0也后移
            a->num[i+1]=a->num[i];
        a->num[0]='-';
        a->sign=1;
    }
    //return a->num;
}
void add(struct number *a,struct number *b,struct number *d)//加法
{
    
    int c=0;
    int i;
    d->len=((a->len>b->len)?a->len:b->len)+1;//假设a+b不进位后d的长度
    for(i=0;i<d->len+1;i++){
        if(i>=b->len)
        b->num[i]='0';//对于a或b不齐的那几位补0
        if(i>=a->len)
        a->num[i]='0';
        d->num[i]=(a->num[i]-'0'+b->num[i]-'0'+c)+'0';//减'0'变成int型计算，最后加'0'变成char型存储，加上进位
        if((d->num[i]-'0')>=10){//判断进位
            d->num[i]=(d->num[i]-'0')%10+'0';
            c=1;
        }
        else
            c=0;
    }
    if(c==1){//最后的进位
        d->num[d->len]='1';
        d->len++;
    }
    int k=d->len;//确定d长度
    while((d->num[k]=='0'||d->num[k]=='\0')&&k!=0){ 
        d->num[k]='\0';
        k--;
    }
    d->len=k+1;
    
}
void sub(struct number *a,struct number *b,struct number *d)//减法
{
    int c=0;
    int i;
    d->len=(a->len>b->len)?a->len:b->len;//假设d是最长长度

    for(i=0;i<d->len+1;i++){
        if(i>=b->len)
        b->num[i]='0';
        if(i>=a->len)
        a->num[i]='0';
        d->num[i]=(a->num[i]-b->num[i]-c)+'0';//减去被前一位借走的位
        if((d->num[i]-'0')<0){//判断是否需要借位
            d->num[i]=(d->num[i]-'0')+10+'0';
            c=1;
        }
        else
            c=0;
    }
    int k=d->len;//确定d长度
    while((d->num[k]=='0'||d->num[k]=='\0')&&k!=0){ 
        d->num[k]='\0';
        k--;
    }
    d->len=k+1;
}
void mult(struct number *a,struct number *b,struct number *d)//乘法
{
    int temp;
    int c;
    int i,j,digit;
    for(i=0;i<a->len+b->len+1;i++)//最多不超过a位+b位+1
        d->num[i]='0';
    for(i=0;i<b->len;i++){
        int c1=0,c2=0;
        for(j=0;j<a->len+1;j++){
            if(i>=b->len)
            b->num[i]='0';
            if(j>=a->len)
            a->num[j]='0';
            temp=(a->num[j]-'0')*(b->num[i]-'0')+c1;//第一步乘法计算
            c1=temp/10;//第一步进位的计算
            temp=temp%10;
            d->num[i+j]=(d->num[i+j]-'0'+temp+c2)+'0';//第二步加法计算，d->num[i+j]相当于在按位累加之前的计算结果
            c2=(d->num[i+j]-'0')/10;//第二步进位的计算
            d->num[i+j]=(d->num[i+j]-'0')%10+'0';
        }
    }
    int k=a->len+b->len;
    while((d->num[k]=='0'||d->num[k]=='\0')&&k!=0){    
        d->num[k]='\0';
        k--;
    }
    d->len=k+1;
    d->sign=a->sign*b->sign;//1和-1之间的乘法代表了a*b的符号运算

}
void divi(struct number *a,struct number *b,struct number *d,struct number *e)//返回商和余数两个值，用指针
{
    d->sign=a->sign*b->sign;//正负性与乘法相同
    e->sign=1;//余数只能为正
    d->len=a->len;//商的位数不大于被除数
    e->len=b->len;//余数的位数不大于除数
    int i,j,m=0;
    for(i=0;i<a->len+1;i++)
        d->num[i]='0';
    for(i=0;i<b->len+1;i++)
        e->num[i]='0';

    int sublen=a->len-b->len;    
    for(i=a->len;i>=0;i--){//b后面补0，补到和a同位
        if(i>=sublen+1)
        b->num[i]=b->num[i-sublen-1];
        else
        b->num[i]='0';
    }        
    b->len=a->len+1;
    for(j=0;j<=sublen;j++){
        for(i=0;i<b->len;i++){
            b->num[i]=b->num[i+1];//算完商把b往回移
        }
        b->num[i]='\0';
        b->len--;
        while(compare(a,b)!=-1){//得到那一位的商
            sub(a,b,a);
            d->num[sublen-j]++;
        }            
    }
    for(i=0;i<a->len;i++)
        e->num[i]=a->num[i];//a就是余数，赋值给e
    int k=d->len;
    while((d->num[k]=='0'||d->num[k]=='\0')&&k!=0){ 
        d->num[k]='\0';
        k--;
    }
    d->len=k+1;
    k=b->len;
    while((e->num[k]=='0'||e->num[k]=='\0')&&k!=0){    
        e->num[k]='\0';
        k--;
    }
    e->len=k+1;
}   
struct number count(struct number as,struct number bs,int op,int mode)
{//衔接输入-计算-输出的函数
    struct number *a,*b,*d,*e;
    a=(struct number*)malloc(sizeof(struct number));
    b=(struct number*)malloc(sizeof(struct number));
    d=(struct number*)malloc(sizeof(struct number));
    e=(struct number*)malloc(sizeof(struct number));

    strcpy(a->num,as.num);
    strcpy(b->num,bs.num);
    a->len=strlen(a->num);
    b->len=strlen(b->num);

    dete(a);//检测负数
    dete(b);
    reverse(a->num,a->num+a->len-1);//反转存储
    reverse(b->num,b->num+b->len-1);
    switch(op){
        case adde:{//可支持负数
            if(a->sign*b->sign==1){
                add(a,b,d);
                d->sign=a->sign;   
            }
            else{
                if(compare(a,b)==1){
                    sub(a,b,d);
                    d->sign=a->sign;
                }
                else if (compare(a,b)==-1){
                    sub(b,a,d);
                    d->sign=b->sign;
                }
                else{
                    d->num[0]='0';
                    d->num[1]='\0';
                    d->len=1;
                    d->sign=1;
                }     
            }
            break;
        }
        case sube:{//可支持负数
            if(a->sign*b->sign==-1){
                add(a,b,d);
                d->sign=a->sign;
            }
            else{
                if(compare(a,b)==1){
                    sub(a,b,d);
                    d->sign=a->sign;
                }
                else if(compare(a,b)==-1){
                    sub(b,a,d);
                    d->sign=-a->sign;
                }
                if(compare(a,b)==0){
                    d->num[0]='0';
                    d->num[1]='\0';//\0要一直做结尾
                    d->len=1;
                    d->sign=1;
                }
            }            
            break;
        }
        case multe:{
            mult(a,b,d);
            break;
        }
        case divie:{
            int i,flag=0;
            for(i=0;i<b->len;i++){
                if(b->num[i]!='0'&&b->num[i]!='\0'){
                    flag=1;
                    divi(a,b,d,e);
                    break;
                }      
            }
            if(flag==0){
                printf("Error,the divisor can't be 0\n");
                return *d;//强行退出
            }
            else
                break;  
        }
        case reme:{
            int i,flag=0;
            for(i=0;i<b->len;i++){
                if(b->num[i]!='0'&&b->num[i]!='\0'){
                    flag=1;
                    divi(a,b,e,d);
                    break;
                }      
            }
            if(flag==0){
                printf("Error,the second number can't be 0");
                getch();
                return *d;//强行退出
            }
            else
                break;  
        }
        default:{
            printf("Error,please choose from 0~4!");
            break;
        }
    }
    reverse(d->num,d->num+d->len-1);//反转输出
    output(d);
    free(a);
    free(b);
    free(e);
    if(mode==1){//模式一直接打印
        printf("=");
        puts(d->num);
        
    }
    else
        return *d;//模式二返回数据，不打印
}
