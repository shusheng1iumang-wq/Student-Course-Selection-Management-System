
#ifndef __CLASS_HEAD__
#define __CLASS_HEAD__


typedef struct CLASS_LIST
{
    int Course_Number;
    char Course_Name[COURSE_NAME_LINE];
    double Credits;
    char Lecturer[NAME_LINE];
    int Max_Enrollment;
    int Current_Students;
    Bool Category;
    struct CLASS_LIST *next;
} Class_List;

void Cancel_the_course(S_Student_List *student_temp,Class_List *cl_head);   //取消课程--学生
void Course_registration(S_Student_List *student_temp,Class_List *cl_head);   //课程报名--学生
void open_s_c_selection(Class_List *cl_head);     //选课开关！
void copy_cl(Class_List *paste, Class_List *Wall);   //复制cl链表
void read_cl_list(Class_List *cl_head);  //读取cl链表，文件读取
void save_cl_list(Class_List *cl_head);  //保存cl链表
void delete_cl_item(Class_List *cl_head, int number);  //删除特定cl元素
Class_List *check_course_number(Class_List *cl_head, int number);  //查找对应课程number
void free_malloc_cl_list(Class_List *cl_head);   //释放链表，关键！！！
void Insert_class(Class_List *p, Class_List *head);  //插入课程，按照课程号大小
void admin_class_menu(Class_List *);   //管理员课程管理页面
void Course_Entry(Class_List *);    //管理员课程加入
void Browse_Courses(Class_List *cl_head);  //浏览课程链表

#endif