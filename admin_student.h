#ifndef __ADMIN_STUDENT_HEAD__
#define __ADMIN_STUDENT_HEAD__
#include "student.h"

void Delete_Student_item(S_Student_List* ssl_head);  //删除学生元素，似乎重复定义了，回头优化一下
void Browse_Student(S_Student_List* ssl_head);  //浏览学生链表
void Student_Entry(S_Student_List* ssl_head);  //管理员添加学生
void admin_student_menu(S_Student_List *ssl_head);  //管理员学生管理

#endif