#include "show.h"
#include<stdio.h>
#include<stdlib.h>
#include"student.h"

void show_admin_menu(void){
	printf("Operation menu:\n");
	printf("0->class\n");
	printf("1->student\n");
	printf("2->exit\n");
	printf("Your choose:");
}
void show_admin_class_menu(void){
	printf("Class_operation_menu:\n");
	printf("0->Course_Entry\n");
	printf("1->Browse Courses\n");
	printf("2->Delete Course\n");
	printf("3->go back\n");
	printf("4->exit\n");
	printf("Your choose:");
}

void Save_SSL(S_Student_List *ssl_head){
	FILE *fp=NULL;
	char* file_ssl="Student_list.txt";
	S_Student_List *l=ssl_head,*r=ssl_head->next;
	
	if((fp=fopen(file_ssl,"wb"))==NULL){
		printf("%s fopen error!\n",file_ssl);
		exit(1);
	}
	
	while(r!=NULL){
		l=r;
		r=r->next;
		if((fwrite(l,sizeof(S_Student_List)-sizeof(ssl_head->next),1,fp))!=1){
			printf("fwrite error!\n");
			exit(1);	
		}
	}
	
	fclose(fp);
}

void Read_SSl(S_Student_List *ssl_head){
	FILE *fp=NULL;
	char* file_ssl="Student_list.txt";
	S_Student_List temp_ssl;
	S_Student_List *head = ssl_head;
	S_Student_List* next;
	
	if((fp=fopen(file_ssl,"rb"))==NULL){
		printf("%s fread error!\n",file_ssl);
		exit(1);
	}
	
	while(fread(&temp_ssl,sizeof(S_Student_List)-sizeof(ssl_head->next),1,fp)==1){
		if((next = (S_Student_List*)malloc(sizeof(S_Student_List)))==NULL){
			printf("read_ssl malloc error!\n");
			exit(1);
		};
		copy_ssl(&temp_ssl,next);
		head->next = next;
		head = next;
	}
	
	fclose(fp);
	
}

void copy_ssl(S_Student_List *paste,S_Student_List *wall){
	int i=0;
	int j=0;
	clean_ssl(wall);
	
	wall->ID = paste->ID;
	cpystring(paste->name,wall->name,NAME_LINE);
	cpystring(paste->key,wall->key,KEY_LINE);
	wall->major_code = paste->major_code;
	for(i=0;i<2;i++) wall->elective_credits[i] = paste->elective_credits[i];
	for(i=0;i<2;i++){
		for(j=0;j<10;j++){
			wall->elective_record[i][j] = paste->elective_record[i][j];
		}
	}
	
}

void clean_ssl(S_Student_List *wall){
	int i;
	clean_the_history(wall);
	wall->ID=0;
	for(i=0;i<NAME_LINE;i++) wall->name[i]=0;
	for(i=0;i<KEY_LINE;i++) wall->key[i]=0;
	wall->major_code=0;
	for(i=0;i<2;i++) wall->elective_credits[i]=0;
	wall->next=NULL;
}

void show_cl_item(Class_List *p){
	printf("Course Number:%d\n",p->Course_Number);
	printf("Course Name:%s\n",p->Course_Name);
	printf("Credit:%.1lf\n",p->Credits);
	printf("Lecturer:%s\n",p->Lecturer);
	printf("Max_Seats:%d\n",p->Max_Enrollment);
	printf("Category:");
	if(p->Category){
		printf("SS\n");
	}else{
		printf("HSS\n");
	}
}