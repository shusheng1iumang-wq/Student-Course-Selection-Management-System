#include "class.h"
#include <stdio.h>
#include <stdlib.h>
#include "show.h"

void admin_class_menu(Class_List *cl_head)
{
    int i = 0;
    char out = 0;
    Class_List *temp = NULL;
    FILE* fp=NULL;
    char* cl_file="class_list.txt";

    do
    {
        show_admin_class_menu();
        scanf("%d", &i);
        getchar();
        read_cl_list(cl_head);
        switch (i)
        {
        case 0:
            Course_Entry(cl_head);
            break;
        case 1:
            Browse_Courses(cl_head);
            break;
        case 2:
			do
            {
                printf("Input the Course Number to delete:");
                scanf("%d", &i);
                getchar();
                temp = check_course_number(cl_head, i);

                if (temp != NULL)
                {

                    printf("We found this one:\n");
                    show_cl_item(temp);
                    printf("Ready to delete?(y/n)");
                    scanf("%c", &out);

                    if (out == 'y' || out == 'Y')
                    {
                        delete_cl_item(cl_head, i);
                        printf("finshed.\n");
                    }
                    else
                    {
                        printf("go back.\n");
                    }
                }
                else
                {
                    printf("We cannot find the Course Number:%d\n", i);
                }

                save_cl_list(cl_head);

                flag = OFF;
                getchar();
                printf("continue?(y/n)");
                scanf("%c", &out);
                if (out == 'y' || out == 'Y')
                    flag = ON;
            } while (flag);
            //有空优化一下，程序可读性差了
            break;
        case 3:
			 fresh_file(cl_file);
        	break;
        case 4:
            free_malloc_cl_list(cl_head);
            return;
            break;
        case 5:
            free_malloc_cl_list(cl_head);
            exit(1);
            break;
        default:
            break;
        }
    } while (1);
}

void Course_Entry(Class_List *cl_head)
{
    Class_List *p = NULL;
    Class_List *temp = NULL;
    int i;
    char out = 0;
    FILE *fp = NULL;
    char *cl_file = "class_list.txt";

    flag = ON;

    do
    {
        if ((p = (Class_List *)malloc(sizeof(Class_List))) == NULL)
        {
            printf("malloc error!");
            exit(1);
        }

    re_entry:
        printf("Course Number:");
        scanf("%d", &p->Course_Number);
        getchar();
        temp = check_course_number(cl_head, p->Course_Number);
        if (temp != NULL)
        {
            printf("There have the same Course Number.\n");
            show_cl_item(temp);
            do
            {
                printf("What do you want?\n");
                printf("0->delete\n");
                printf("1->re-entry\n");
                printf("2->exit\n");
                printf("Your choose:");
                scanf("%d", &i);
                getchar();
            } while (i != 0 && i != 1 && i != 2);
            if (i == 0)
            {
                delete_cl_item(cl_head, p->Course_Number);
            }
            else if (i == 1)
            {
                goto re_entry;
            }
            else if (i == 2)
            {
                free(p);
                return;
            }
            //ÕâÒ»¶Îdo while¿ÉÒÔÓÅ»¯Ò»ÏÂ
        }

        printf("Course Name:");
        cpystring("", p->Course_Name, COURSE_NAME_LINE); //     ? 
        fgets(p->Course_Name, COURSE_NAME_LINE, stdin);
        fgets_demo(p->Course_Name);

        printf("Credits:");
        scanf("%lf", &p->Credits);
        getchar();

        printf("Lecturer:");
        cpystring("", p->Lecturer, NAME_LINE);
        fgets(p->Lecturer, NAME_LINE, stdin);
        fgets_demo(p->Lecturer);

        printf("Max Seats:");
        scanf("%d", &p->Max_Enrollment);

        p->Current_Students = 0;

        printf("Category:\n");
        printf("0->HSS,1->SS\n");
        do
        {
            scanf("%d", &i);
        } while (i != 0 && i != 1);
        p->Category = i;
        p->next = NULL;

        Insert_class(p, cl_head);

        getchar();
        printf("continue?(y/n)");
        scanf("%c", &out);
        if (out == 'n' || out == 'N')
            flag = OFF;

    } while (flag);

    save_cl_list(cl_head);

    fclose(fp);
}

void Insert_class(Class_List *p, Class_List *head)
{
    Class_List *l = head;
    Class_List *r = head->next;
    while (r && r->Course_Number < p->Course_Number)
    {
        l = r;
        r = r->next;
    }
    l->next = p;
    p->next = r;
}

void free_malloc_cl_list(Class_List *cl_head)
{
    Class_List *l = cl_head;
    Class_List *r = cl_head->next;
    while (r != NULL)
    {
        l = r;
        r = r->next;
        free(l);
    }
    cl_head->next = NULL;
}

Class_List *check_course_number(Class_List *cl_head, int number)
{
    Class_List *p = NULL;
    while (cl_head != NULL)
    {
        if (cl_head->Course_Number == number)
        {
            p = cl_head;
            break;
        }
        cl_head = cl_head->next;
    }
    return p;
}

void delete_cl_item(Class_List *cl_head, int number)
{
    Class_List *l = cl_head;
    Class_List *r = cl_head->next;
    flag = OFF;
    while (r != NULL)
    {
        if (r->Course_Number == number)
        {
            l->next = r->next;
            free(r);
            flag = ON;
            break;
        }
        l = r;
        r = r->next;
    }
    if (flag)
    {
        printf("delete success!\n");
    }
    else
    {
        printf("cannot find\n");
    }
}

void save_cl_list(Class_List *cl_head)
{
    FILE *fp = NULL;
    char *cl_file = "class_list.txt";
    Class_List *p = NULL;
    Class_List *head = cl_head;

    if ((fp = fopen(cl_file, "wb")) == NULL)
    {
        printf("fopen error!\n");
        exit(1);
    }
    while (head != NULL)
    {
        p = head;
        head = head->next;
        if ((fwrite(p, sizeof(Class_List) - sizeof(p->next), 1, fp)) != 1)
        {
            printf("fwrite error!\n");
            exit(1);
        }
    }
}

void read_cl_list(Class_List *cl_head)
{
    FILE *fp = NULL;
    char *cl_file = "class_list.txt";
    Class_List *p = NULL;
    Class_List temp_cl = {0};

    if ((fp = fopen(cl_file, "rb")) == NULL)
    {
        printf("%s fopen error!\n", cl_file);
        exit(1);
    }

    while ((fread(&temp_cl, sizeof(Class_List) - sizeof(temp_cl.next), 1, fp)) == 1)
    {
        if ((p = (Class_List *)malloc(sizeof(Class_List))) == NULL)
        {
            printf("read_cl_list malloc error!\n");
            exit(1);
        }
        copy_cl(&temp_cl, p);
        p->next = NULL;
        cl_head->next = p;
        cl_head = cl_head->next;
    }

    fclose(fp);
}

void copy_cl(Class_List *paste, Class_List *Wall)
{

    Wall->Course_Number = paste->Course_Number;
    cpystring(paste->Course_Name, Wall->Course_Name, COURSE_NAME_LINE);
    Wall->Credits = paste->Credits;
    cpystring(paste->Lecturer, Wall->Lecturer, NAME_LINE);
    Wall->Max_Enrollment = paste->Max_Enrollment;
    Wall->Current_Students = paste->Current_Students;
    Wall->Category = paste->Category;
}

void Browse_Courses(Class_List *cl_head)
{
    Class_List *r = cl_head->next;

    printf("Course Number | Course Name | Credits | Lecturer | Seats | Category |\n");

    while (r != NULL)
    {
        printf("%14d|", r->Course_Number);
        printf("%13s|", r->Course_Name);
        printf("%9.1f|", r->Credits);
        printf("%10s|", r->Lecturer);
        printf("%3d/%3d|", r->Current_Students, r->Max_Enrollment);
        if (r->Category)
            printf("%10s", "SS");
        else
            printf("%10s", "HSS");
        printf("\n");
        r = r->next;
    }
}