#include <stdio.h>
#include <string.h>
#include <windows.h>

/***************
项目名称：		学生管理系统
功能：			增删改查
管理员密码：	717800578（拥有最高权限）
普通成员密码：	555	（只能查）
***************/

typedef struct stu
{
	char  stu_id[20];
	char  name[20];
	float score[3];

}STU;

void input_stu_data(STU *stu,int *stu_num);	//录入学生信息
int  id_exist(STU *stu,STU stu_id,int n);//判断学号是否唯一
void output_stu_data(STU *stu,int stu_num,int status); //输出学生信息
STU  *check_a_stu(STU *stu,int stu_num);	//查找一个学生信息
STU  * delete_a_stu(STU *stu,int *stu_num);	//删除一个学生信息
int  check_stu_index(STU *stu,STU *stu_id,int stu_num); //找到该学生下标
void mod_stu_score(STU *stu,int stu_num);	// 修改一个学生成绩
float stu_score_sum(STU stu,int course_num); //求一个学生的分数和
float stu_ave_score(STU stu,int course_num);  //求一个学生的平均分
float course_ave_score(STU *stu,int stu_num,int course);//求全班同一门课程的平均分
int above_60_score(STU *stu,int course,int stu_num);//找出成绩合格的学生信息
int less_60_score(STU *stu,int course,int stu_num);//找出成绩不合格的学生信息
void swap(STU *stu,int j); //交换结构体变量内容
void score_sort(STU *stu,int stu_num,int staus);//按平均分排序 staus=1 降序 staus=0 升序 如果平均分相同比较语文成绩
void stuid_sort(STU *stu,int stu_num,int staus);//学号排序
int password_window(void); //登录界面
int mod_password(int status);//修改登录密码
void open_window(void); //输出命令窗口
void freshen_window(void);//刷新窗口
void cmd_window(STU *student,int *stu_num,int status);//命令选择窗口
void creak_student_txt_out_info(STU stu,int stu_num); //创建一个学生txt文件
void write_txt_info(STU *stu,int stu_num);//输出学生信息到txt文件
void read_txt_info(STU *stu,int *stu_num); //读取文本信息
int txt_info_exist(void);//判断文本信息是否存在
void password_ordinary(void); //初始化普通成员密码
void password_administrator(void);//初始化管理员密码

int main(void)
{
	int stu_num=0,status;
	STU student[100];
	while(1)
	{
		status=password_window();
		freshen_window();
		cmd_window(student,&stu_num,status);
	}
	return 0;
}

void cmd_window(STU *student,int *stu_num,int status)
{
	int i,n;
	STU *p;
	while(1)
	{
		y:
		if(status)
			printf("普通成员权限,只能操作：2、4、5、6、7、8、9、10、12、13、14、15命令\n");
		else
			printf("管理员权限\n");

		printf("input_cmd:");
		scanf("%d",&n);
		while(getchar() != '\n');

		if((status && (n==1 || n==3 || n==11))|| (!*stu_num && (n!=1) && (n!=15)) && n!=13 && n!=14)
		{
			freshen_window();
			if(!*stu_num)
				printf("信息为空,请先录入或读取\n");
			goto y;
		}
		 
		switch(n)
		{
			case 1: freshen_window();
					input_stu_data(student,stu_num);  
					output_stu_data(student,*stu_num,1);	break;

			case 2: freshen_window();
					p=check_a_stu(student,*stu_num); 
					if(p != NULL)
						output_stu_data(p,1,3);	
															break;

			case 3: freshen_window();
					p=delete_a_stu(student,stu_num);  
					if(p != NULL)
						write_txt_info(student,*stu_num);
					output_stu_data(student,*stu_num,3);	break;

			case 4: freshen_window();
					score_sort(student,*stu_num,1);
					write_txt_info(student,*stu_num);
					output_stu_data(student,*stu_num,3);	break;

			case 5: freshen_window();
					score_sort(student,*stu_num,0);	
					write_txt_info(student,*stu_num);
					output_stu_data(student,*stu_num,3);	break;

			case 6: freshen_window();
					stuid_sort(student,*stu_num,1);
					write_txt_info(student,*stu_num);
					output_stu_data(student,*stu_num,1);	break;

			case 7: freshen_window();
					stuid_sort(student,*stu_num,0);
					write_txt_info(student,*stu_num);
					output_stu_data(student,*stu_num,1);	 break;

			case 8: freshen_window();
					n=less_60_score(student,3,*stu_num);
					if(n>=1)
					{
						printf("成绩不合格的学生信息：\n");
						output_stu_data(student,n,1);
					}										 break;

			case 9: freshen_window();
					n=above_60_score(student,3,*stu_num);
					if(n>=1)
					{
						printf("成绩合格的学生信息：\n");
						output_stu_data(student,n,1);
					}										break;

			case 10: freshen_window();
					output_stu_data(student,*stu_num,2);	break;

			case 11: freshen_window();
					 mod_stu_score(student,*stu_num);		break;

			case 12: freshen_window();
					output_stu_data(student,*stu_num,3);	break;

			case 13: system("cls");
					 return;
											
			case 14: freshen_window();
					if(mod_password(status) == -1)
					{
						system("cls");
						return;	
					}										break;

			case 15: freshen_window();
					read_txt_info(student,stu_num);			break;

			default:freshen_window(); 
					printf("该命令待开发！\n");
		}
	
	}
}

void input_stu_data(STU *stu,int *stu_num)
{
	STU temp;
	char ch ;
	if(!txt_info_exist() && !*stu_num)
	{
		read_txt_info(stu,stu_num);
		printf("文本信息已读取,是否继续输入学生信息(继续 Y 退出 N)\n");
		ch=getchar();
		if(ch == 'n'|| ch == 'N')
			return;
	}
	printf("请输入学号、名字、语文成绩、数学成绩、英语成绩(例如:20210801 张三 89 90 89)\n");
	while(1)
	{
		x:
		printf("input(输入：886 结束录入):");
		scanf("%s",temp.stu_id);
		if(id_exist(stu,temp,(*stu_num)) == 1)
		{
			while(getchar() != '\n');
			printf("学号已存在,请重新输入!\n");
			goto x;
		}
		if(strcmp(temp.stu_id,"886") == 0)
		{
			freshen_window();
			printf("录入结束！\n");
			break;
		}
		scanf("%s",temp.name);
		scanf("%f%f%f",&temp.score[0],&temp.score[1],&temp.score[2]);

		while(getchar() != '\n');
		stu[*stu_num]=temp;
		(*stu_num)++;
		creak_student_txt_out_info(temp,*stu_num);
	}
}

void open_window(void)
{
	printf("=============学生信息管理系统=================\n");
	printf("请输入要操作的命令:\n");
	printf("1---录入学生信息\n");
	printf("2---查找一个学生信息\n"); 
	printf("3---删除一个学生信息\n");
	printf("4---按平均分升序排序\n");
	printf("5---按平均分降序排序\n");
	printf("6---按学号升序排序\n");
	printf("7---按学号降序排序\n");
	printf("8---输出成绩不合格的学生\n");
	printf("9---输出成绩合格的学生\n");
	printf("10---输出课程平均分\n");
	printf("11---修改学生成绩\n");
	printf("12---输出学生信息(基础信息+各科分数+平均分+总分)\n");
	printf("13---退出命令界面\n");
	printf("14---修改登录界面密码\n");
	printf("15---读取txt文件\n");
	printf("=============================================\n");
}

void freshen_window(void)
{
	system("cls");
	open_window();
}

int  id_exist(STU *stu,STU stu_id,int n)
{
	int i;
	for(i=0;i<n;i++,stu++)
	{
		if(strcmp(stu->stu_id,stu_id.stu_id) == 0)
			return 1;	
	}
	return 0;
}

void output_stu_data(STU *stu,int stu_num,int status)
{
	int i;
	STU *p;
	switch(status)
	{
		
		case 1: //基础信息
				printf("学号    名字    语文     数学     英语\n");
				for(i=0;i<stu_num;i++,stu++)
				{
					printf("%s    ",stu->stu_id);
					printf("%s    ",stu->name);
					printf("%.2f    ",stu->score[0]);
					printf("%.2f    ",stu->score[1]);
					printf("%.2f    \n",stu->score[2]);
				}
				printf("学生信息人数为：%d\n",stu_num);
				break;

		case 2: //课程平均分
				printf("全班语文平均分为：%.2f    \n",course_ave_score(stu,stu_num,0));
				printf("全班数学平均分为：%.2f    \n",course_ave_score(stu,stu_num,1));
				printf("全班英语平均分：  %.2f    \n",course_ave_score(stu,stu_num,2));
				break;

		case 3: //基础信息 + 平均分 + 总分 
				printf("学号    名字     语文     数学      英语    平均分      总分\n");
				for(i=0;i<stu_num;i++,stu++)
				{
					printf("%s    ",stu->stu_id);
					printf("%s     ",stu->name);
					printf("%.2f    %.2f     ",stu->score[0],stu->score[1]);
					printf("%.2f    %.2f	 ",stu->score[2],(float)stu_ave_score(*stu,3));
					printf("%.2f\n",stu_score_sum(*stu,3));
				}
				break;
				
	}
}

float stu_score_sum(STU stu,int course_num)
{
	int i;
	float sum=0;
	for(i=0;i<course_num;i++)
		sum += stu.score[i];
	return sum;
}

float stu_ave_score(STU stu,int course_num)
{
	
	return stu_score_sum(stu,course_num)/course_num;
}

float course_ave_score(STU *stu,int stu_num,int course)
{
	int i;
	float sum=0;
	for(i=0;i<stu_num;i++)
	{
		sum += stu->score[course];
		stu++;
	}
	return sum/stu_num;
}

void swap(STU *stu,int j)
{
	STU temp;
	temp  = stu[j];
	stu[j] = stu[j+1];
	stu[j+1] = temp;
}

void score_sort(STU *stu,int stu_num,int staus)
{
	int i,j;
	if(staus)
	{
		for(i=0;i<stu_num-1;i++)
			for(j=0;j<stu_num-i-1;j++)
			{
				if(stu_ave_score(stu[j],3) < stu_ave_score(stu[j+1],3))
					swap(stu,j);

				if(stu_ave_score(stu[j],3) == stu_ave_score(stu[j+1],3))
					if(stu[j].score[0] < stu[j+1].score[0])
						swap(stu,j);
			}
	}

	else
	{
		for(i=0;i<stu_num-1;i++)
			for(j=0;j<stu_num-i-1;j++)
			{
				if(stu_ave_score(stu[j],3) > stu_ave_score(stu[j+1],3))
					swap(stu,j);

				if(stu_ave_score(stu[j],3) == stu_ave_score(stu[j+1],3))
					if(stu[j].score[0] > stu[j+1].score[0])
						swap(stu,j);
			}
	}
}

void stuid_sort(STU *stu,int stu_num,int staus)
{
	int i,j;
	STU temp;
	if(staus)
	{
		for(i=0;i<stu_num-1;i++)
			for(j=0;j<stu_num-i-1;j++)
				if(strcmp(stu[j].stu_id,stu[j+1].stu_id) == 1)
					swap(stu,j);
	}

	else
	{
		for(i=0;i<stu_num-1;i++)
			for(j=0;j<stu_num-i-1;j++)
				if(strcmp(stu[j].stu_id,stu[j+1].stu_id) == -1)
					swap(stu,j);
	}
}

STU  *check_a_stu(STU *stu,int stu_num)
{
	int i;
	char id_or_name[20];
	printf("请输入学号或名字：");
	gets(id_or_name);
	for(i=0;i<stu_num;i++,stu++)
	{
		if(strcmp(id_or_name,stu->stu_id) == 0 || strcmp(id_or_name,stu->name) == 0)
			return stu;
	}
	printf("不存在该学生!\n");
	return NULL;

}

STU  * delete_a_stu(STU *stu,int *stu_num)
{
	STU *t;
	char ch;
	int i,n;
	t=check_a_stu(stu,*stu_num);
	output_stu_data(t,1,1);
	printf("是否删除该学生信息(输入:Y 删除 N 退出)\n");
	ch=getchar();
	if(ch == 'y' || ch == 'Y')
	{	
		n=check_stu_index(stu,t,*stu_num);
		for(i=n;i<*stu_num;i++)
		{
			stu[i]=stu[i+1];
		}
		(*stu_num)--;
		return t;
	}
	return NULL;
}

int  check_stu_index(STU *stu,STU *stu_id,int stu_num)
{
	int i;
	for(i=0;i<stu_num;i++,stu++)
	{
		if(strcmp(stu_id->stu_id,stu->stu_id) == 0)
			return i;
	}
}

int above_60_score(STU *stu,int course,int stu_num)
{
	int i,j,n=0;
	score_sort(stu,stu_num,1);
	for(i=0;i<stu_num;i++,stu++)
	{
		for(j=0;j<course;j++)
			if(stu->score[j] >= 60)
				n++;
	}
	return n/3;
}

int less_60_score(STU *stu,int course,int stu_num)
{
	int i,j,n=0;
	score_sort(stu,stu_num,0);
	for(i=0;i<stu_num;i++,stu++)
		for(j=0;j<course;j++)
			if(stu->score[j] < 60)
			{
				n++;
				break;
			}
	return n;
}

void mod_stu_score(STU *stu,int stu_num)
{
	STU *q;
	int n;

	q=check_a_stu(stu,stu_num);
	if(q == NULL) return;
	output_stu_data(q,1,1);
	printf("请输入要修改的科目(例如: 0（语文）1（数学）) 2（英语）\n");
	y:
	scanf("%d",&n);
	if(n >= 0 && n <= 2)
	{
		printf("请输入要修改的成绩：");
		scanf("%f",&q->score[n]);
		printf("\n修改成功！\n");
	}
	else
	{	
		printf("不存在该科目,请重新输入!\n");
		goto y;
	}
}

void password_ordinary(void)
{
	FILE *fp;
	
	fp=fopen("./password_ordinary.txt","r");
	if(fp == NULL || fgetc(fp) == EOF)
	{
		fp=fopen("./password_ordinary.txt","w+");
		fputs("555",fp);
	}
	fclose(fp);
}

void password_administrator(void)
{
	FILE *fp;
	
	fp=fopen("./password_administrator.txt","r");
	if(fp == NULL || fgetc(fp) == EOF)
	{
		fp=fopen("./password_administrator.txt","w+");
		fputs("717800578",fp);
	}
	fclose(fp);
}

int password_window(void)
{
	FILE *fp1,*fp2;
	int n=0;
	char password[20];
	char password_ordinary1[20];
	char password_administrator1[20];
	

	password_ordinary();
	password_administrator();

	fp1=fopen("./password_ordinary.txt","r");
	fscanf(fp1,"%s",password_ordinary1);
	fclose(fp1);

	fp2=fopen("./password_administrator.txt","r");
	fscanf(fp2,"%s",password_administrator1);
	fclose(fp2);

	while(1)
	{
		printf("请输入密码：");
		gets(password);

		if(!strcmp(password_ordinary1,password))
			return 1;
		else if(!strcmp(password_administrator1,password))
			return 0;
		else
			printf("密码错误！\n");	
		n++;
		if(n == 3)
			system("cls");	
	}
}

int mod_password(int status)
{
	int n=3,x=0;
	FILE *fp1,*fp2;
	char password[20];
	char password_ordinary1[20];
	char password_administrator1[20];

	password_ordinary();
	password_administrator();

	fp1=fopen("./password_ordinary.txt","r");
	fscanf(fp1,"%s",password_ordinary1);
	fclose(fp1);

	fp2=fopen("./password_administrator.txt","r");
	fscanf(fp2,"%s",password_administrator1);
	fclose(fp2);

	if(!status)
	{
		printf("选择要修改成员的密码(0 普通成员 1 管理员 )\n");
		scanf("%d",&x);
		while(getchar() != '\n');
		if(x)
		{
			while(n--)
			{
				printf("请输入原密码：");
				gets(password);
				if(strcmp(password,password_administrator1) == 0)
				{
					printf("请输入要修改的密码：");
					gets(password);

					fp1=fopen("./password_administrator.txt","w+");
					fputs(password,fp1);
					fclose(fp1);
					printf("密码修改成功!\n");
					break;
				}
				printf("\n密码错误！%\n");
			}
			return n;
		}
	}
	if(status || !x)
	{
		while(n--)
			{
				printf("请输入原密码：");
				gets(password);
				if(strcmp(password,password_ordinary1) == 0)
				{
					printf("请输入要修改的密码：");
					gets(password);

					fp2=fopen("./password_ordinary.txt","w+");
					fputs(password,fp2);
					fclose(fp2);
					printf("密码修改成功!\n");
					break;
				}
				printf("\n密码错误！%\n");
			}
			return n;
	}
}


void creak_student_txt_out_info(STU stu,int stu_num)
{
		FILE *fp;
		if(stu_num == 1)
		{
			fp=fopen("./student.txt","w+");
			fclose(fp);
			fp=fopen("./student.txt","a+");
			fprintf(fp,"%s   %s   %s   %s       %s      %s\n","序号","学号","名字","语文","数学","英语");
			fclose(fp);
		}
		fp=fopen("./student.txt","a+");
		fprintf(fp,"%d     %s    %s    %.2f    %.2f    %.2f\n",stu_num,stu.stu_id,stu.name,stu.score[0],stu.score[1],stu.score[2]);
		fclose(fp);
}

void write_txt_info(STU *stu,int stu_num)
{
	int i;
	for(i=0;i<stu_num;i++)
		creak_student_txt_out_info(stu[i],i+1);
}

void read_txt_info(STU *stu,int *stu_num)
{
	FILE *fp;
	int n=6;
	float temp;
	char str[20];
	char *p=str;

	if(txt_info_exist()|| *stu_num != 0) return;

	fp=fopen("./student.txt","r");
	while(n--)fscanf(fp,"%s",p);
	n=1;
	while(fscanf(fp,"%s",p) != EOF)
	{
		switch(n)
		{
			case 2: strcpy(stu[*stu_num].stu_id,p); 				   break;
			case 3:	strcpy(stu[*stu_num].name,p);  			           break;
			case 4:	sscanf(p,"%f",&temp); stu[*stu_num].score[0]=temp; break;
			case 5:	sscanf(p,"%f",&temp); stu[*stu_num].score[1]=temp; break;
			case 6:	sscanf(p,"%f",&temp); stu[*stu_num].score[2]=temp; break;
		}
		if(n == 6)
		{
			n=0;
			(*stu_num)++;
		}
		n++;
	}
	fclose(fp);	
	printf("文本信息已读取\n");
}

int txt_info_exist(void)
{
	FILE *fp;

	fp=fopen("./student.txt","r");
	if(fgetc(fp) == EOF)
	{
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}
