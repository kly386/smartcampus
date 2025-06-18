#include<stdio.h>
#include "ui/student_manage/student_ui.h"
#include "../include/ui/class_manage/main_ui.h"

void show_main_menu() {
    printf("\n===== 智慧校园中台 =====\n");
    printf("1. 学生管理（实现中）\n");
    printf("2. 排课管理（待实现）\n");  // 预留扩展
    printf("3. 地图管理（待实现）\n");  // 预留扩展
    printf("4. 退出系统\n");
    printf("===========================\n");
    printf("请选择操作: ");
}

int main() {
    // 在app.c的main()开头调用
    initialize_teacher_data_if_needed();
    int choice; //接收用户的输入的
    while (1) {
        show_main_menu();

        // 接收用户的输入
        //先做一个保护
        if (scanf_s("%d", &choice) != 1) {
            printf("输入无效，请输入一个数字.\n");
            while (getchar() != '\n');
            continue;
        }

        //正常的选择操作
        switch (choice) {
        case 1:
            //printf("进入学生管理系统\n");
            handle_student_input();
            break;
        case 2:
            printf("进入排课管理系统\n");
            handle_course_schedule_input();
            break;
        case 3:
            printf("进入地图管理系统\n");
            break;
        case 4:
            printf("退出系统\n");
            return 0;
        default:
            printf("无效输入，请重新选择\n");
            while (getchar() != '\n');
        }
    }
}