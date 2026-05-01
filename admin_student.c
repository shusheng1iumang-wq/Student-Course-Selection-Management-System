#include <stdio.h>
#include <stdlib.h>
#include "admin_student.h"
#include "show.h"
#include "student.h"
#include"major_code.h"

extern Major_Code_List mcl_head;

void admin_student_menu(S_Student_List *ssl_head)
{
    int i = 0;
    char *ssl_file="Student_list.txt";
    int c=0;

    do
    {
        show_admin_student_menu();
        scanf("%d", &i);
        while((c=getchar())!='\n'&&c!=EOF);
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
	        	fresh_file(ssl_file);
	        	break;
	        case 4:
	        	free_malloc_ssl_list(ssl_head);
	        	return;
	            break;
	        case 5:
	        	free_malloc_ssl_list(ssl_head);
	        	exit(0);
	            break;
        }
        free_malloc_ssl_list(ssl_head);
    } while (1);
}

void Student_Entry(S_Student_List* ssl_head){
	lli id=0;
	char out=0;
	S_Student_List *p=NULL;
	Major_Code_List *mcl_p=NULL;
	int c=0;
	
	Read_major_code_list(&mcl_head,MCL_FILE);
	
	do{
		flag =OFF;
		do{
			again:
			printf("The Student ID:");
			scanf("%lld",&id);
			while((c=getchar())!='\n'&&c!=EOF);
		}while(id<=STUDENT_ID_LINE);
		
		p = Search_Student_ID(ssl_head,id);
		if(p!=NULL){
			printf("There had a same one:\n");
			show_ssl_item(p);
			printf("Do you want to delete this?(y/n)");
			scanf("%c",&out);
			while((c=getchar())!='\n'&&c!=EOF);
			
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed!let's continue.\n");
			}else{
				printf("continue?(y/n)");
				scanf("%c",&out);
				while((c=getchar())!='\n'&&c!=EOF);
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
		while(!save_fgets(p->major_code,CODE_LINE)){
			printf("fgets error!\n");
			printf("input again:");
		}
		
		mcl_p = Search_mcl_item_code(&mcl_head,p->major_code);
		
		if(mcl_p==NULL){
			printf("Could find this major_code.\n");
			printf("Do you want to inout again?(y/n)");
			scanf("%c",&out);
			while((c=getchar())!='\n'&&c!=EOF);
			if(out=='y'||out=='Y')goto again3;
			free(p);
			free_malloc_mcl(&mcl_head);
			printf("go back.\n");
			return;
		}
		cpystring(mcl_p->name,p->major_name,COURSE_NAME_LINE);
		give_elective_credits(mcl_p->Category,p); 
		free_malloc_mcl(&mcl_head);
		
		printf("Name:");
		while(!save_fgets(p->name,NAME_LINE)){
			printf("fgets error!\n");
			printf("input again:");
		}
		
		
		Insert_account(ssl_head,p);
		
		
		printf("continue?(y/n)");
		out = getchar();
		if(out=='Y'||out=='y')flag=ON;
		
		
	}while(flag);
	
	free_malloc_mcl(&mcl_head); 
}

void Browse_Student(S_Student_List* ssl_head){
	S_Student_List* p=ssl_head->next;
	int i;
	
	printf("| Student ID | Student NAME | m_code |  HSS  |  SS   | major_name\n");
	
	while(p!=NULL){
		printf("|%12lld|",p->ID);
		printf("%14s|",p->name);
		printf("%8s|",p->major_code);
		printf("%3.1lf/%3.1lf|",p->elective_credits[HSS][1],p->elective_credits[HSS][0]);
		printf("%3.1lf/%3.1lf|",p->elective_credits[SS][1],p->elective_credits[SS][0]);
		printf("%s\n",p->major_name);
		printf("HSS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[HSS][i][0]!=0){
				printf("(%d):%d",i,p->elective_record);
				printf(" ");
			}else printf("\n");break;
		}
		printf("SS record:");
		for(i=0;i<10;i++){
			if(p->elective_record[SS][i][0]!=0){
				printf("(%d):%d",i,p->elective_record);
				printf(" ");
			}else printf("\n");break;
		}
		p = p->next;
	}
}

void Delete_Student_item(S_Student_List* ssl_head){
	lli id = 0;
	char out = 0;
	int c=0;
	S_Student_List *p = NULL;
	
	do{
		flag =OFF;
		printf("Input student id to delete:");
		scanf("%lld",&id);
		while((c=getchar())!='\n'&&c!=EOF);
		p = Search_Student_ID(ssl_head,id);
		
		if(p==NULL){
			printf("Cannot find the ID:%lld\n",id);
		}else{
			printf("We find:\n");
			show_ssl_item(p);
			printf("Do you want to delete?(y/n)");
			out = getchar();
			if(out=='y'||out=='Y'){
				del_ssl_item(ssl_head,id);
				printf("finshed.\n"); 
			}
		}
		
		printf("continue?(y/n)");
		getchar();
		out=getchar();
		if(out=='Y'||out=='y')flag=ON;	
		
	}while(flag);
}