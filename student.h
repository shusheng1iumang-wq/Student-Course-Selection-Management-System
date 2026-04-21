#ifndef _STUDENT_HEAD_
#define _STUDENT_HEAD_

#define STUDENT_ID_LINE 999999999 //s_id test
#define THE_TRY_LINE 10  //尝试次数限制
#define TIP_TIME 5  //提示次数线
#define NAME_LINE 30  //名字限制
#define KEY_LINE 30 // 最大密码限制
#define KEY_BOTTOM_LINE 12  //最小密码限制
#define HSS 0  //人文社科
#define SS 1  //自然科学
#define MAX_SCORE 6  //分数分配多
#define MIN_SCORE 3  //分数分配少



typedef enum {OFF,ON}Bool; //自定义开关
Bool flag;  //全局开关

//long long int
typedef long long int lli;

// student linked list structure
typedef struct STUDENT_LIST
{
	lli ID;	// student ID
	char name[NAME_LINE];  //name
	char key[KEY_LINE]; // password
	int major_code;		// major code
	/*本来想做一个专业名称对应专业号的系统的，
	但是这花费很大，先占个位*/
	// elective credits
	int elective_credits[2]; // 0 for HSS, 1 for SS
	// HSS-->Humanities and Social Sciences
	// SS-->Science and Technology
	int elective_record[2][10]; // 0 for HSS, 1 for SS
	// record course selection history
	struct STUDENT_LIST *next;
} S_Student_List;

void input_the_name(S_Student_List *p);

void clean_the_history(S_Student_List *p);  //将选课历史清空

void give_elective_credits(S_Student_List* p,int major_code);  //根据专业代号分配选课分数

void cpystring(char *paste,char *wall,int size);  //自定义复制字符串函数

void fgets_demo(char* string);  //fgets补丁，去掉'\n'

Bool key2key(char *key,char *key_input);   //字符串对比，用来比对密码

Bool password_security(char* key);   //确定密码限制

void Insert_account(S_Student_List* ssl_head,S_Student_List *p);  //根据学号插入用户

S_Student_List* Set_Up_Student_Account(S_Student_List* ssl_head,lli s_id); //建立学生用户

S_Student_List *Search_Student_ID(S_Student_List*,lli s_id); //遍历寻找Id

S_Student_List *Inquiry_User(S_Student_List *ssl_head);  //询问用户，开始界面

void free_malloc_ssl_list(S_Student_List* ssl_head);  //free_malloc


#endif