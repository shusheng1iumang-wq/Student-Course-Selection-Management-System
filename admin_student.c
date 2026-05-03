#include <stdio.h>
#include <stdlib.h>
#include "admin_student.h"
#include "show.h"
#include "student.h"
#include"major_code.h"

extern Major_Code_List mcl_head;

//检查完毕 1
void admin_student_menu(S_Student_List *ssl_head)
{
    int i = 0;
    
    do
    {
        show_admin_student_menu();
    	SAFE_READ(d,"Your choose:",i);
        Read_SSL(ssl_head);
        switch (i)
        {
        	case 0:
        		Student_Entry(ssl_head);
        		Save_SSL(ssl_head);
           		break;
	        case 1:
	        	Browse_Student(ssl_head);
	            break;
	        case 2:
	        	Delete_Student_item(ssl_head);
	        	Save_SSL(ssl_head);
	            break;
	        case 3:
	        	fresh_file(SSL_FILE);
	        	break;
	        case 4:
	        	free_malloc_ssl_list(ssl_head);
	        	return;
	            break;
	        case 5:
	        	free_malloc_ssl_list(ssl_head);
	        	exit(0);
	            break;
	        default:
	        	printf("Input the illegal number.\n");
	        	break;
        }
        free_malloc_ssl_list(ssl_head);
    } while (1);
}

//检查完毕 1
void Student_Entry(S_Student_List* ssl_head){
	lli id=0;
	char out=0;
	S_Student_List *p=NULL;
	Major_Code_List *mcl_p=NULL;
	Bool flag = OFF;
	
	Read_major_code_list(&mcl_head);
	
	do{
		flag =OFF;
		do{
			again:
			SAFE_READ(lld,"The Student ID:",id);
		}while(id<=STUDENT_ID_LINE);
		
		p = Search_Student_ID(ssl_head,id);
		if(p!=NULL){
			printf("There had a same one:\n");
			show_ssl_item(p);
			
			SAFE_READ(c,"Do you want to delete this?(y/n)",out);
			
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed!let's continue.\n");
			}else{
				
				SAFE_READ(c,"continue?(y/n)",out);
				
				if(out=='y'||out=='Y'){
					goto again;
				}else{
					return;
				}
			}		
		}
		p = (S_Student_List*)malloc(sizeof(S_Student_List));
		clean_ssl_item(p);
		p->ID = id;
		cpystring("123456789&&Gdut",p->key,15);
		
		again3:
		printf("Major Code:");
		while(!safe_fgets(p->major_code,CODE_LINE)){
			printf("fgets error!\n");
			printf("input again:");
		}
		
		mcl_p = Search_mcl_item_code(&mcl_head,p->major_code);
		
		if(mcl_p==NULL){
			printf("Could find this major_code.\n");
			
			SAFE_READ(c,"Do you want to inout again?(y/n)",out);
			
			if(out=='y'||out=='Y')goto again3;
			free(p);
			free_malloc_mcl(&mcl_head);
			printf("go back.\n");
			return;
		}
		cpystring(mcl_p->name,p->major_name,COURSE_NAME_LINE);
		give_elective_credits(mcl_p->Category,p); 
		
		printf("Name:");
		while(!safe_fgets(p->name,NAME_LINE)){
			printf("fgets error!\n");
			printf("input again:");
		}
		
		Insert_account(ssl_head,p);
		
		SAFE_READ(c,"continue?(y/n)",out);
		if(out=='Y'||out=='y')flag=ON;
		
		
	}while(flag);
	
	free_malloc_mcl(&mcl_head); 
}

void Browse_Student(S_Student_List* ssl_head){
	S_Student_List* p=ssl_head->next;
	int i;
	int j=0;
	
	for(j=0;p!=NULL;j++,p=p->next){
		if(j%10==0&&j!=0){
			buffer_line();
			printf("| Student ID | Student NAME | m_code |  HSS  |  SS   | major_name\n");
		}
		printf("|%12lld|",p->ID);
		printf("%14s|",p->name);
		printf("%8s|",p->major_code);
		printf("%3.1lf/%3.1lf|",p->elective_credits[HSS][1],p->elective_credits[HSS][0]);
		printf("%3.1lf/%3.1lf|",p->elective_credits[SS][1],p->elective_credits[SS][0]);
		printf("%s\n",p->major_name);
		printf("HSS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[HSS][i][0]!=0){
				printf("(%d):%d",i,(int)(p->elective_record[HSS][i][0]));
				printf(" ");
			}else printf("\n");break;
		}
		printf("SS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[SS][i][0]!=0){
				printf("(%d):%d",i,(int)(p->elective_record[SS][i][0]));
				printf(" ");
			}else printf("\n");break;
		}
	}
}

void Delete_Student_item(S_Student_List* ssl_head){
	lli id = 0;
	char out = 0;
	int c=0;
	S_Student_List *p = NULL;
	Bool flag = OFF;
	
	do{
		flag =OFF;

		SAFE_READ(lld,"Input id to delete:",id);

		p = Search_Student_ID(ssl_head,id);
		
		if(p==NULL){
			printf("Cannot find the ID:%lld\n",id);
		}else{
			printf("We find:\n");
			show_ssl_item(p);
			SAFE_READ(c,"Do you want to delete?(y/n)",out);
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed.\n"); 
			}
		}
		
		SAFE_READ(c,"continue?(y/n)",out);
		if(out=='Y'||out=='y')flag=ON;	
		
	}while(flag);
}