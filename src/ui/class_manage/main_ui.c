// ui/course_schedule/main_ui.c
#include "../../include/ui/class_manage/main_ui.h"
#include "../../include/ui/class_manage/teacher_ui.h"
#include "../../include/ui/class_manage/course_ui.h"
#include "../../include/ui/class_manage/classroom_ui.h"
#include "../../include/ui/class_manage/schedule_ui.h"
#include <stdio.h>
#include <stdlib.h>



void show_course_schedule_menu() {
    printf("\n===== �����ſ�ϵͳ =====\n");
    printf("1. ��ʦ����\n");
    printf("2. �γ̹���\n");
    printf("3. ���ҹ���\n");
    printf("4. �α����\n");
    printf("5. �鿴ȫ���α�\n");
    printf("0. �������˵�\n");
    printf("========================\n");
    printf("��ѡ�����: ");
}

void handle_course_schedule_input() {
    int choice;
    while (1) {
        system("cls");
        show_course_schedule_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч��������һ������.\n");
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
            printf("��Ч���룬������ѡ��\n");
            system("pause");
        }
    }
}