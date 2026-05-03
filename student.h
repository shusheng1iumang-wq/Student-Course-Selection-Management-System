#ifndef _STUDENT_HEAD_
#define _STUDENT_HEAD_

#define COURSE_NAME_LINE 100        //课程名
#define CODE_LINE 24            //code_line
#define STUDENT_ID_LINE 999999999 // s_id test
#define THE_TRY_LINE 10           // 尝试次数限制
#define TIP_TIME 5                // 提示次数线
#define NAME_LINE 100              // 名字限制
#define KEY_LINE 30               // 最大密码限制
#define KEY_BOTTOM_LINE 12        // 最小密码限制
#define HSS 0                     // 人文社科
#define SS 1                      // 自然科学
#define MAX_SCORE 9.0               // 分数分配多
#define MIN_SCORE 3.0               // 分数分配少
#define OPEN_FILE "open.txt"         //开关文件
#define SSL_FILE  "Student_list.txt"      //ssl文件

typedef enum{ OFF,ON}Bool;    
/*自定义开关*/
extern Bool extern_flag; // 全局开关
//取消全局开关的设置，实际函数嵌套完全局调度会很复杂，不如局部定义。
//其实给宏就可以了  标明他的全局性质，防止用错

// long long int
typedef long long int lli;

// student linked list structure
typedef struct STUDENT_LIST
{
    lli ID;               // student ID
    char name[NAME_LINE]; // name
    char key[KEY_LINE];   // password
    char major_code[CODE_LINE];       // major code
    char major_name[COURSE_NAME_LINE];
    // elective credits
    double elective_credits[2][2]; // 0 for HSS, 1 for SS
    // HSS-->Humanities and Social Sciences
    // SS-->Science and Technology
    // 0 for max , 1 for now
    double elective_record[2][10][2]; // 0 for HSS, 1 for SS   
	// 10个空间够用，后面想想怎么优化
	//后面加入的功能，成绩功能。   0表示课程号  1表示成绩，成绩大于0就是结课     
    // record course selection history
    struct STUDENT_LIST *next;
} S_Student_List;

void change_password(S_Student_List *p);         //修改密码
void view_course_grades(S_Student_List *p);       //展示学生个人成绩
void del_ssl_item(S_Student_List *ssl_head,lli id);   //删除学生元素
void show_ssl_item(S_Student_List *p);    //展示学生元素
void clean_the_history(S_Student_List *p); // 将选课历史清空
void give_elective_credits(Bool,S_Student_List*p); // 根据专业代号分配选课分数
void cpystring(char *paste, char *wall, int size); // 自定义复制字符串函数  
//也有清空string的作用，好好利用。
Bool password_security(char *key); // 确定密码限制
void Insert_account(S_Student_List *ssl_head, S_Student_List *p); // 根据学号插入用户
S_Student_List *Set_Up_Student_Account(S_Student_List *ssl_head, lli s_id); // 建立学生用户
S_Student_List *Search_Student_ID(S_Student_List *, lli s_id); // 遍历寻找Id
S_Student_List *Inquiry_User(S_Student_List *ssl_head); // 询问用户，开始界面
void free_malloc_ssl_list(S_Student_List *ssl_head); // free_malloc

#endif