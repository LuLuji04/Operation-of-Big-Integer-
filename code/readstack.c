#include <stdio.h>
#include <stdlib.h> 
#include"all.c"
#define MAX 20
//存放运算数的栈 
struct SNode_Num
{
	struct number datas[MAX];
	int top;
};
typedef struct SNode_Num OperateNum;
 
//存放运算符号的栈 
struct SNode_Symbol
{
	char symbol[MAX];
	int top;
};
typedef struct SNode_Symbol OperateSymbol;

//初始化运算数的栈的函数
void InitOperateNum(OperateNum *StackNum)
{
	StackNum->top = -1; 
}

//初始化运算符的栈的函数
void InitOperateSymbol(OperateSymbol *StackSymbol)
{
	StackSymbol->top = -1;
} 

//运算数的进栈
void PushOperateNum(OperateNum *StackNum, struct number x)
{
	StackNum->top++;
	StackNum->datas[StackNum->top] = x; 
} 

//运算符的进栈
void PushOperateSymbol(OperateSymbol *StackSymbol, char ch)
{
	StackSymbol->top++;
	StackSymbol->symbol[StackSymbol->top] = ch; 
}

//运算数的出栈
struct number PopOperateNum(OperateNum *StackNum)
{
	struct number num;
	num = StackNum->datas[StackNum->top];
	StackNum->top--;
	return num;
}

//运算符的出栈
char PopOperateSymbol(OperateSymbol *StackSymbol)
{
	char ch;
	ch = StackSymbol->symbol[StackSymbol->top];
	StackSymbol->top--;
	return ch;
}
 
//取出相应的数 
struct number GetOperateNum(OperateNum *StackNum)
{
	return StackNum->datas[StackNum->top];
}
 
//取出相应运算符 
char GetOperateSymbol(OperateSymbol *StackSymbol)
{
	return StackSymbol->symbol[StackSymbol->top]; 
} 

//判断所有需要用的操作符 包括 + - * / ( ) = 
short IsOperateSymbolOrNum(char ch)
{
	if(ch == '+' || ch == '-' || ch == '*' 
	|| ch == '/' || ch == '%' || ch == '(' || ch == ')' || ch == '=') return 1;
	
	else return 0;	
}

//判断优先级
char Priority(char inputnum, char ch)
{
	switch(inputnum)
	{
		//加减在同一个优先级上 
		case '+':
		case '-':
		{
			if(ch == '+' || ch == '-') return '>';
			else if(ch == '*' || ch == '/'||ch=='%') return '<';
			else if(ch == '(') return '<';
			else if(ch == ')') return '>';
			else return '>';
		}
			break;
		
		//乘除在同一优先级 
		case '*':
		case '/':
		case '%':
		{
			if(ch == '+' || ch == '-') return '>';
			else if(ch == '*' || ch == '/'||ch=='%') return '>';
			else if(ch == '(') return '<';
			else if(ch == ')') return '>';
			else return '>';
		}
			break;
		
		//括号在所有优先级以上 
		case '(':
		{
			if(ch == ')') return '=';
			else return '<';
		}
			break;
		case ')':
		{
			return '>';
		}
			break;
		case '=':
		{
			if(ch == '=') return '=';
			else return '<';
		}
			break;	
	}
}

//进行计算的主函数 
struct number read1(FILE *read)
{
	OperateNum *datas;
	OperateSymbol *symbol;
	datas=(OperateNum*)malloc(sizeof(OperateNum));
	symbol=(OperateSymbol*)malloc(sizeof(OperateSymbol));
	struct number *num1, *num2, *result, *num;
	num1=(struct number*)malloc(sizeof(struct number));
	num2=(struct number*)malloc(sizeof(struct number));
	result=(struct number*)malloc(sizeof(struct number));
	num=(struct number*)malloc(sizeof(struct number));
	char ch, sign;
	
	InitOperateNum(datas);
	InitOperateSymbol(symbol);
	
	int i;
	PushOperateSymbol(symbol, '=');//把等号计算的操作符放在栈中 
	ch = fgetc(read);

	while((ch != '=') || (GetOperateSymbol(symbol) != '='))
	{
		if(!IsOperateSymbolOrNum(ch))//是数字
		{
			for(i=0;i<size;i++)//读取新数字的时候先初始化
				num->num[i]='\0';
			i=0;
			num->num[i] = ch;//以结构中的数组存储
			i++; 
			ch = fgetc(read);  
			while(!IsOperateSymbolOrNum(ch))
			{
				num->num[i]= ch;
				i++;
				ch = fgetc(read);   //当没有读入=时，继续读取
			} 
			PushOperateNum(datas, *num);			
		}
		else
		{
			switch(Priority(GetOperateSymbol(symbol), ch))//判断优先级后进行计算 
			{
				case '<':
					PushOperateSymbol(symbol, ch);
					ch = fgetc(read);
					break;
				case '=':
					sign = PopOperateSymbol(symbol);
					ch = fgetc(read);  //获取输入
					break;
				case '>':
					sign = PopOperateSymbol(symbol);
					*(num2) = PopOperateNum(datas);
					*(num1) = PopOperateNum(datas);
					int op;
					switch(sign){
						case '+':
						op=adde;break;
						case '-':
						op=sube;break;
						case '*':
						op=multe;break;
						case '/':
						op=divie;break;
						case '%':
						op=reme;break;
						default:
						break;	
					}
					*result = count(*num1, *num2, op , 2);
					PushOperateNum(datas, *result);
					break;
					
			}
		} 
		
	}	
	*result = GetOperateNum(datas);
	//puts(result.num);  //输出结果，模式2不需要
	free(datas);
	free(symbol);
	free(num1);
	free(num2);
	free(num);
	char temp[5];
	fgets(temp,5,read);//读入回车，从下一行继续读
	return *result;
}