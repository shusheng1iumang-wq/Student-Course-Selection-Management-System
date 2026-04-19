#ifndef __CLASS_HEAD__
#define __CLASS_HEAD__
#define COURSE_NAME_LINE 100



typedef struct CLASS_ARRAY{
	int Course_Number;   //课程编号
	char Course_Name[COURSE_NAME_LINE];  //课程名
	double Credits;   //课程学分
	char Lecturer[NAME_LINE];   //课程讲师
	int Max_Enrollment;   //人数限制
	int Current_Students;  //已选人数
	Bool Category;   //课程类别
}Class_Array; 

void admin_class_menu(void);

#endif