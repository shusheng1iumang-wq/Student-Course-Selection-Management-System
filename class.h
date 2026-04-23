#ifndef __CLASS_HEAD__
#define __CLASS_HEAD__
#define COURSE_NAME_LINE 100
#include "student.h"


typedef struct CLASS_LIST{
	int Course_Number;   
	char Course_Name[COURSE_NAME_LINE];  
	double Credits;   
	char Lecturer[NAME_LINE];   
	int Max_Enrollment;   
	int Current_Students;  
	Bool Category;   
	struct CLASS_LITS *next;
}Class_List;

void copy_cl(Class_List* paste,Class_List *Wall);
void read_cl_list(Class_List *cl_head);
void save_cl_list(Class_List *cl_head);
void delete_cl_item(Class_List* cl_head,int number);
Class_List * check_course_number(Class_List* cl_head,int number);
void free_malloc_cl_list(Class_List* cl_head);
void Insert_class(Class_List* p,Class_List *head);
void admin_class_menu(Class_List*);
void Course_Entry(Class_List*);
void Browse_Courses(Class_List *cl_head);



#endif