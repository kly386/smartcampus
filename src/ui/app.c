#include<stdio.h>
#include "ui/student_manage/student_ui.h"
#include "../include/ui/class_manage/main_ui.h"

void show_main_menu() {
    printf("\n===== �ǻ�У԰��̨ =====\n");
    printf("1. ѧ������ʵ���У�\n");
    printf("2. �ſι�����ʵ�֣�\n");  // Ԥ����չ
    printf("3. ��ͼ������ʵ�֣�\n");  // Ԥ����չ
    printf("4. �˳�ϵͳ\n");
    printf("===========================\n");
    printf("��ѡ�����: ");
}

int main() {
    // ��app.c��main()��ͷ����
    initialize_teacher_data_if_needed();
    int choice; //�����û��������
    while (1) {
        show_main_menu();

        // �����û�������
        //����һ������
        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч��������һ������.\n");
            while (getchar() != '\n');
            continue;
        }

        //������ѡ�����
        switch (choice) {
        case 1:
            //printf("����ѧ������ϵͳ\n");
            handle_student_input();
            break;
        case 2:
            printf("�����ſι���ϵͳ\n");
            handle_course_schedule_input();
            break;
        case 3:
            printf("�����ͼ����ϵͳ\n");
            break;
        case 4:
            printf("�˳�ϵͳ\n");
            return 0;
        default:
            printf("��Ч���룬������ѡ��\n");
            while (getchar() != '\n');
        }
    }
}