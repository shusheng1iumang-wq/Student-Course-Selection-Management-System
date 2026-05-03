#include "show.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include<errno.h>



extern Bool Open_Student_Course;

void show_major_code_menu(void){
	printf("--------------------\n");
	printf("Major Code Operation Menu:\n");
	printf("0->Browse Major Code\n");
	printf("1->Entry Major Code\n");
	printf("2->Delete Major Code\n");
	printf("3->Fresh the File\n");
	printf("4->Go back\n");
	printf("5->Exit\n");
	printf("--------------------\n");
}

void show_student_menu(void){
	printf("--------------------\n");
	printf("Operation menu:\n");
	printf("0->Browse Course\n");
	printf("1->View personal information\n");
	printf("2->View courese grades\n");
	printf("3->Course registration\n");
	printf("4->Cancel the course\n");
	printf("5->Change password.\n");
	printf("6->exit\n");
	printf("--------------------\n");
}

//检查完毕 1
void show_admin_student_menu(void)
{
	printf("--------------------\n");
    printf("Student operation menu:\n");
    printf("0->Student Entry\n");
    printf("1->Browse Students\n");
    printf("2->Delete Student account\n");
    printf("3->Fresh the file\n");
    printf("4->go back\n");
    printf("5->exit\n");
   	printf("--------------------\n");
}

//检查完毕 1
void show_admin_menu(void)
{	
	printf("--------------------\n");
    printf("Operation menu:\n");
    printf("0->class\n");
    printf("1->student\n");
    printf("2->major code\n");
    printf("3->exit\n");
	printf("--------------------\n");
}

//检查完毕 1
void show_admin_class_menu(void)
{
	printf("--------------------\n");
    printf("Class_operation_menu:\n");
    printf("0->Course_Entry\n");
    printf("1->Browse Courses\n");
    printf("2->Delete Course\n");
    printf("3->Fresh the file\n");
    printf("4->Open student course selection\n");
    printf("5->Course completion and student score entry.\n");
    printf("6->go back\n");
    printf("7->exit\n");
    printf("--------------------\n");
}

//检查完毕 1
void Save_SSL(S_Student_List *ssl_head)
{
    FILE *fp = NULL;
    S_Student_List *l = NULL, 
		*r = ssl_head->next;

    if ((fp = fopen(SSL_FILE, "wb")) == NULL)
    {
        printf("%s fopen error!\n", SSL_FILE);
        exit(1);
    }

    while (r != NULL)
    {
        l = r;
        r = r->next;
        if ((fwrite(l, sizeof(S_Student_List) - sizeof(ssl_head->next), 1, fp)) != 1)
        {
            printf("fwrite error!\n");
            exit(1);
        }
    }

    fclose(fp);
}

//检查完毕 1
void Read_SSL(S_Student_List *ssl_head)
{
    FILE *fp = NULL;
    S_Student_List temp_ssl={0},
		cleaner={0};
    S_Student_List *head = ssl_head;
    S_Student_List *next;
    ssl_head->next = NULL;

    while((fp = fopen(SSL_FILE, "rb")) == NULL)
    {
		if(errno==ENOENT){                 //没有文件，创造文件
			Save_SSL(ssl_head);        			
		}else{
			printf("fopen %s file error\n",SSL_FILE);
			exit(1);
		}
    }

    while (fread(&temp_ssl, sizeof(S_Student_List) - sizeof(ssl_head->next), 1, fp) == 1)
    {
        if ((next = (S_Student_List *)malloc(sizeof(S_Student_List))) == NULL)
        {
            printf("read_ssl malloc error!\n");
            exit(1);
        };
        copy_ssl_without_next(&temp_ssl, next);
        next->next = NULL;
        head->next = next;
        head = next;
        copy_ssl_without_next(&cleaner,&temp_ssl);
    }

    fclose(fp);
}

//检查完毕 1
void copy_ssl_without_next(S_Student_List *paste, S_Student_List *wall)
{
    int i = 0;
    int j = 0;

    wall->ID = paste->ID;
    cpystring(paste->name, wall->name, NAME_LINE);
    cpystring(paste->key, wall->key, KEY_LINE);
    cpystring(paste->major_code,wall->major_code,CODE_LINE);
    cpystring(paste->major_name,wall->major_name,COURSE_NAME_LINE);
    for (i = 0; i < 2; i++){
        wall->elective_credits[i][0] = paste->elective_credits[i][0];
        wall->elective_credits[i][1] = paste->elective_credits[i][1];
    }
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 10; j++)
        {
            wall->elective_record[i][j][0] = paste->elective_record[i][j][0];
            wall->elective_record[i][j][1] = paste->elective_record[i][j][1];
        }
    }
}

void clean_ssl_item(S_Student_List *wall)
{
    int i;
    clean_the_history(wall);
    wall->ID = 0;
    for (i = 0; i < NAME_LINE; i++)
        wall->name[i] = 0;
    for (i = 0; i < KEY_LINE; i++)
        wall->key[i] = 0;
    cpystring("",wall->major_code,CODE_LINE);
    cpystring("",wall->major_name,COURSE_NAME_LINE);
    for (i = 0; i < 2; i++){
        wall->elective_credits[i][0] = 0;
        wall->elective_credits[i][1] = 0;
    }
    wall->next = NULL;
}

//检查完毕 1
void show_cl_item(Class_List *p)
{
    printf("Course Number:%d\n", p->Course_Number);
    printf("Course Name:%s\n", p->Course_Name);
    printf("Credit:%.1lf\n", p->Credits);
    printf("Lecturer:%s\n", p->Lecturer);
    printf("Max_Seats:%d\n", p->Max_Enrollment);
    printf("Category:");
    if (p->Category)
    {
        printf("SS\n");
    }
    else
    {
        printf("HSS\n");
    }
}

void fresh_file(char* file){
	char out = 0;
	FILE *fp=NULL;
	
	SAFE_READ(c,"Are you sure?(y/n)",out);
    if(out=='y'||out=='Y'){
       	if(remove(file)!=0){
        	printf("remove error.\n");
        }else{
			if((fp=(fopen(file,"wb")))==NULL){
				printf("fopen error.\n");
			}else printf("finshed.\n");
		}
	}
	
	fclose(fp);   //更加安全
}

//检查完毕 1
void read_Open_Student_Course(void){
	FILE* fp=NULL;
	
	while((fp=fopen(OPEN_FILE,"rb"))==NULL){
		if(errno==ENOENT){
			save_Open_Student_Course();
		}else{
			printf("fopen %s file error\n",OPEN_FILE);
			exit(1);
		}
	}
	
	if((fread(&Open_Student_Course,sizeof(Bool),1,fp))!=1){
		printf("fread error!");
	}
	fclose(fp);
}

//检查完毕 1
void save_Open_Student_Course(void){
	FILE *fp=NULL;
	
	if((fp=fopen(OPEN_FILE,"wb"))==NULL){
		printf("%s file fopen error!\n",OPEN_FILE);
		exit(1);
	}
	
	if((fwrite(&Open_Student_Course,sizeof(Bool),1,fp))!=1){
		printf("fwrite %s file error.\n",OPEN_FILE);
		exit(1);
	}
	
	fclose(fp);
}

//检查完毕 1
Bool safe_fgets(char*string,int size){
	int length;
	
	cpystring("",string,size);
	if((fgets(string,size,stdin))==NULL)return OFF;
	if(strchr(string,'\n')==NULL){
		int c;
		while((c=getchar())!='\n'&&c!=EOF);
		return OFF;
	}
	
	length = strlen(string) - 1;
	if(string[length]=='\n')string[length]=0;
	
	return ON;
}

//		已经被我变成宏了   坠机了man!
//Bool safe_read_int(int*n){
//	char buffer[BUFFER_LINE];
//	char check_points = 0;
//	
//	while(!safe_fgets(buffer,BUFFER_LINE)){
//		printf("buffer fgets error!\n");
//		printf("again:");
//	}
//	
//	if(sscanf(buffer,"%d %c",n,&check_points)==1)return ON;
//	
//	return OFF;
//}

//检查完毕 1
void buffer_line(void){
	char line[CODE_LINE];
	do{
		printf("Press Enter to continue.");
	}while(!safe_fgets(line,CODE_LINE));
}
