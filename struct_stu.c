#include <stdio.h>
#include <string.h>
#include <windows.h>

/***************
��Ŀ���ƣ�		ѧ������ϵͳ
���ܣ�			��ɾ�Ĳ�
����Ա���룺	717800578��ӵ�����Ȩ�ޣ�
��ͨ��Ա���룺	555	��ֻ�ܲ飩
***************/

typedef struct stu
{
	char  stu_id[20];
	char  name[20];
	float score[3];

}STU;

void input_stu_data(STU *stu,int *stu_num);	//¼��ѧ����Ϣ
int  id_exist(STU *stu,STU stu_id,int n);//�ж�ѧ���Ƿ�Ψһ
void output_stu_data(STU *stu,int stu_num,int status); //���ѧ����Ϣ
STU  *check_a_stu(STU *stu,int stu_num);	//����һ��ѧ����Ϣ
STU  * delete_a_stu(STU *stu,int *stu_num);	//ɾ��һ��ѧ����Ϣ
int  check_stu_index(STU *stu,STU *stu_id,int stu_num); //�ҵ���ѧ���±�
void mod_stu_score(STU *stu,int stu_num);	// �޸�һ��ѧ���ɼ�
float stu_score_sum(STU stu,int course_num); //��һ��ѧ���ķ�����
float stu_ave_score(STU stu,int course_num);  //��һ��ѧ����ƽ����
float course_ave_score(STU *stu,int stu_num,int course);//��ȫ��ͬһ�ſγ̵�ƽ����
int above_60_score(STU *stu,int course,int stu_num);//�ҳ��ɼ��ϸ��ѧ����Ϣ
int less_60_score(STU *stu,int course,int stu_num);//�ҳ��ɼ����ϸ��ѧ����Ϣ
void swap(STU *stu,int j); //�����ṹ���������
void score_sort(STU *stu,int stu_num,int staus);//��ƽ�������� staus=1 ���� staus=0 ���� ���ƽ������ͬ�Ƚ����ĳɼ�
void stuid_sort(STU *stu,int stu_num,int staus);//ѧ������
int password_window(void); //��¼����
int mod_password(int status);//�޸ĵ�¼����
void open_window(void); //��������
void freshen_window(void);//ˢ�´���
void cmd_window(STU *student,int *stu_num,int status);//����ѡ�񴰿�
void creak_student_txt_out_info(STU stu,int stu_num); //����һ��ѧ��txt�ļ�
void write_txt_info(STU *stu,int stu_num);//���ѧ����Ϣ��txt�ļ�
void read_txt_info(STU *stu,int *stu_num); //��ȡ�ı���Ϣ
int txt_info_exist(void);//�ж��ı���Ϣ�Ƿ����
void password_ordinary(void); //��ʼ����ͨ��Ա����
void password_administrator(void);//��ʼ������Ա����

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
			printf("��ͨ��ԱȨ��,ֻ�ܲ�����2��4��5��6��7��8��9��10��12��13��14��15����\n");
		else
			printf("����ԱȨ��\n");

		printf("input_cmd:");
		scanf("%d",&n);
		while(getchar() != '\n');

		if((status && (n==1 || n==3 || n==11))|| (!*stu_num && (n!=1) && (n!=15)) && n!=13 && n!=14)
		{
			freshen_window();
			if(!*stu_num)
				printf("��ϢΪ��,����¼����ȡ\n");
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
						printf("�ɼ����ϸ��ѧ����Ϣ��\n");
						output_stu_data(student,n,1);
					}										 break;

			case 9: freshen_window();
					n=above_60_score(student,3,*stu_num);
					if(n>=1)
					{
						printf("�ɼ��ϸ��ѧ����Ϣ��\n");
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
					printf("�������������\n");
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
		printf("�ı���Ϣ�Ѷ�ȡ,�Ƿ��������ѧ����Ϣ(���� Y �˳� N)\n");
		ch=getchar();
		if(ch == 'n'|| ch == 'N')
			return;
	}
	printf("������ѧ�š����֡����ĳɼ�����ѧ�ɼ���Ӣ��ɼ�(����:20210801 ���� 89 90 89)\n");
	while(1)
	{
		x:
		printf("input(���룺886 ����¼��):");
		scanf("%s",temp.stu_id);
		if(id_exist(stu,temp,(*stu_num)) == 1)
		{
			while(getchar() != '\n');
			printf("ѧ���Ѵ���,����������!\n");
			goto x;
		}
		if(strcmp(temp.stu_id,"886") == 0)
		{
			freshen_window();
			printf("¼�������\n");
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
	printf("=============ѧ����Ϣ����ϵͳ=================\n");
	printf("������Ҫ����������:\n");
	printf("1---¼��ѧ����Ϣ\n");
	printf("2---����һ��ѧ����Ϣ\n"); 
	printf("3---ɾ��һ��ѧ����Ϣ\n");
	printf("4---��ƽ������������\n");
	printf("5---��ƽ���ֽ�������\n");
	printf("6---��ѧ����������\n");
	printf("7---��ѧ�Ž�������\n");
	printf("8---����ɼ����ϸ��ѧ��\n");
	printf("9---����ɼ��ϸ��ѧ��\n");
	printf("10---����γ�ƽ����\n");
	printf("11---�޸�ѧ���ɼ�\n");
	printf("12---���ѧ����Ϣ(������Ϣ+���Ʒ���+ƽ����+�ܷ�)\n");
	printf("13---�˳��������\n");
	printf("14---�޸ĵ�¼��������\n");
	printf("15---��ȡtxt�ļ�\n");
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
		
		case 1: //������Ϣ
				printf("ѧ��    ����    ����     ��ѧ     Ӣ��\n");
				for(i=0;i<stu_num;i++,stu++)
				{
					printf("%s    ",stu->stu_id);
					printf("%s    ",stu->name);
					printf("%.2f    ",stu->score[0]);
					printf("%.2f    ",stu->score[1]);
					printf("%.2f    \n",stu->score[2]);
				}
				printf("ѧ����Ϣ����Ϊ��%d\n",stu_num);
				break;

		case 2: //�γ�ƽ����
				printf("ȫ������ƽ����Ϊ��%.2f    \n",course_ave_score(stu,stu_num,0));
				printf("ȫ����ѧƽ����Ϊ��%.2f    \n",course_ave_score(stu,stu_num,1));
				printf("ȫ��Ӣ��ƽ���֣�  %.2f    \n",course_ave_score(stu,stu_num,2));
				break;

		case 3: //������Ϣ + ƽ���� + �ܷ� 
				printf("ѧ��    ����     ����     ��ѧ      Ӣ��    ƽ����      �ܷ�\n");
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
	printf("������ѧ�Ż����֣�");
	gets(id_or_name);
	for(i=0;i<stu_num;i++,stu++)
	{
		if(strcmp(id_or_name,stu->stu_id) == 0 || strcmp(id_or_name,stu->name) == 0)
			return stu;
	}
	printf("�����ڸ�ѧ��!\n");
	return NULL;

}

STU  * delete_a_stu(STU *stu,int *stu_num)
{
	STU *t;
	char ch;
	int i,n;
	t=check_a_stu(stu,*stu_num);
	output_stu_data(t,1,1);
	printf("�Ƿ�ɾ����ѧ����Ϣ(����:Y ɾ�� N �˳�)\n");
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
	printf("������Ҫ�޸ĵĿ�Ŀ(����: 0�����ģ�1����ѧ��) 2��Ӣ�\n");
	y:
	scanf("%d",&n);
	if(n >= 0 && n <= 2)
	{
		printf("������Ҫ�޸ĵĳɼ���");
		scanf("%f",&q->score[n]);
		printf("\n�޸ĳɹ���\n");
	}
	else
	{	
		printf("�����ڸÿ�Ŀ,����������!\n");
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
		printf("���������룺");
		gets(password);

		if(!strcmp(password_ordinary1,password))
			return 1;
		else if(!strcmp(password_administrator1,password))
			return 0;
		else
			printf("�������\n");	
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
		printf("ѡ��Ҫ�޸ĳ�Ա������(0 ��ͨ��Ա 1 ����Ա )\n");
		scanf("%d",&x);
		while(getchar() != '\n');
		if(x)
		{
			while(n--)
			{
				printf("������ԭ���룺");
				gets(password);
				if(strcmp(password,password_administrator1) == 0)
				{
					printf("������Ҫ�޸ĵ����룺");
					gets(password);

					fp1=fopen("./password_administrator.txt","w+");
					fputs(password,fp1);
					fclose(fp1);
					printf("�����޸ĳɹ�!\n");
					break;
				}
				printf("\n�������%\n");
			}
			return n;
		}
	}
	if(status || !x)
	{
		while(n--)
			{
				printf("������ԭ���룺");
				gets(password);
				if(strcmp(password,password_ordinary1) == 0)
				{
					printf("������Ҫ�޸ĵ����룺");
					gets(password);

					fp2=fopen("./password_ordinary.txt","w+");
					fputs(password,fp2);
					fclose(fp2);
					printf("�����޸ĳɹ�!\n");
					break;
				}
				printf("\n�������%\n");
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
			fprintf(fp,"%s   %s   %s   %s       %s      %s\n","���","ѧ��","����","����","��ѧ","Ӣ��");
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
	printf("�ı���Ϣ�Ѷ�ȡ\n");
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
