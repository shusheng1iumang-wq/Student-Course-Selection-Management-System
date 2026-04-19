#ifndef __CLASS_HEAD__
#define __CLASS_HEAD__
#define COURSE_NAME_LINE 100
#include "student.h"


typedef struct CLASS_LIST{
	int Course_Number;   //课程编号
	char Course_Name[COURSE_NAME_LINE];  //课程名
	double Credits;   //学分
	char Lecturer[NAME_LINE];   //教师
	int Max_Enrollment;   //最大人数
	int Current_Students;  //已报名学生
	Bool Category;   //课程类别HHS，SS
	struct CLASS_LITS *next;
}Class_List; 

void admin_class_menu(void);

void Course_Entry(void);
#endif