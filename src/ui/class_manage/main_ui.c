// ui/course_schedule/main_ui.c
#include "../../include/ui/class_manage/main_ui.h"
#include "../../include/ui/class_manage/teacher_ui.h"
#include "../../include/ui/class_manage/course_ui.h"
#include "../../include/ui/class_manage/classroom_ui.h"
#include "../../include/ui/class_manage/schedule_ui.h"
#include <stdio.h>
#include <stdlib.h>



void show_course_schedule_menu() {
    printf("\n===== 简易排课系统 =====\n");
    printf("1. 教师管理\n");
    printf("2. 课程管理\n");
    printf("3. 教室管理\n");
    printf("4. 课表管理\n");
    printf("5. 查看全部课表\n");
    printf("0. 返回主菜单\n");
    printf("========================\n");
    printf("请选择操作: ");
}

void handle_course_schedule_input() {
    int choice;
    while (1) {
        system("cls");
        show_course_schedule_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入一个数字.\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            handle_teacher_input();
            break;
        case 2:
            handle_course_input();
            break;
        case 3:
            handle_classroom_input();
            break;
        case 4:
            handle_schedule_input();
            break;
        case 5:
            view_all_schedules();
            break;
        case 0:
            return;
        default:
            printf("无效输入，请重新选择\n");
            system("pause");
        }
    }
}