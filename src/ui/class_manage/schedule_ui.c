// ui/course_schedule/schedule_ui.c
#include "../include/ui/class_manage/schedule_ui.h"
#include "../include/service/class_manage//schedule_service.h"
#include "../include/service/class_manage/course_service.h"
#include "../include/service/class_manage/classroom_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>

void add_schedule_ui() {
    Schedule new_schedule;
    printf("\n------ ������ſ� ------\n");

    // ��ȡ�ſ���Ϣ
    printf("�ſ�ID: ");
    scanf_s("%d", &new_schedule.id);
    getchar();

    printf("�γ�ID: ");
    scanf_s("%d", &new_schedule.course_id);
    getchar();

    // ��֤�γ��Ƿ����
    if (get_course_service()->get_course(new_schedule.course_id) == NULL) {
        printf("����: �γ̲����ڣ�\n");
        system("pause");
        return;
    }

    printf("����ID: ");
    scanf_s("%d", &new_schedule.classroom_id);
    getchar();

    // ��֤�����Ƿ����
    if (get_classroom_service()->get_classroom(new_schedule.classroom_id) == NULL) {
        printf("����: ���Ҳ����ڣ�\n");
        system("pause");
        return;
    }

    printf("�ܴ�(1-16): ");
    scanf_s("%d", &new_schedule.week);
    getchar();

    printf("����(1-7): ");
    scanf_s("%d", &new_schedule.day);
    getchar();

    printf("�ڴ�(1-12): ");
    scanf_s("%d", &new_schedule.slot);
    getchar();

    // ���÷��������ſ�
    ErrorCode result = get_schedule_service()->add_schedule(&new_schedule);
    if (result != SUCCESS) {
        printf("����ſ�ʧ��: %s\n", error_message(result));
    }
    else {
        printf("�ſ���ӳɹ���\n");
    }
    system("pause");
}

//void delete_schedule_ui() {
//    int schedule_id;
//    printf("\n------ ɾ���ſ� ------\n");
//    printf("������Ҫɾ�����ſ�ID: ");
//    scanf_s("%d", &schedule_id);
//    getchar();
//
//    // �Ȼ�ȡ�ſ���Ϣ����ȷ��
//    Schedule* schedule = get_schedule_service()->get_schedule(schedule_id);
//    if (schedule == NULL) {
//        printf("����: δ�ҵ����ſμ�¼��\n");
//        system("pause");
//        return;
//    }
//
//    // ��ʾ�ſ�����
//    printf("\n����ɾ�������ſ�:\n");
//    printf("�ſ�ID: %d\n", schedule->id);
//    printf("�γ�ID: %d\n", schedule->course_id);
//    printf("����ID: %d\n", schedule->classroom_id);
//    printf("ʱ��: ��%d�� ����%d ��%d��\n",
//        schedule->week, schedule->day, schedule->slot);
//
//    // ȷ��ɾ��
//    printf("\nȷ��ɾ����(Y/N): ");
//    char confirm;
//    scanf_s("%c", &confirm, 1);
//    getchar();
//
//    if (confirm == 'Y' || confirm == 'y') {
//        ErrorCode result = get_schedule_service()->delete_schedule(schedule_id);
//        if (result != SUCCESS) {
//            printf("ɾ���ſ�ʧ��: %s\n", error_message(result));
//        }
//        else {
//            printf("�ſ�ɾ���ɹ���\n");
//        }
//    }
//    else {
//        printf("��ȡ��ɾ������\n");
//    }
//    system("pause");
//}
//
//void modify_schedule_ui() {
//    int schedule_id;
//    printf("\n------ �޸��ſ���Ϣ ------\n");
//    printf("������Ҫ�޸ĵ��ſ�ID: ");
//    scanf_s("%d", &schedule_id);
//    getchar();
//
//    // ��ȡ�����ſ���Ϣ
//    Schedule* schedule = get_schedule_service()->get_schedule(schedule_id);
//    if (schedule == NULL) {
//        printf("����: δ�ҵ����ſμ�¼��\n");
//        system("pause");
//        return;
//    }
//
//    // ��ʾ��ǰ��Ϣ
//    printf("\n��ǰ�ſ���Ϣ:\n");
//    printf("1. �γ�ID: %d\n", schedule->course_id);
//    printf("2. ����ID: %d\n", schedule->classroom_id);
//    printf("3. �ܴ�: %d\n", schedule->week);
//    printf("4. ����: %d\n", schedule->day);
//    printf("5. �ڴ�: %d\n", schedule->slot);
//
//    // ��ȡ�޸���Ϣ
//    Schedule modified = *schedule;
//    int choice;
//    printf("\n��ѡ��Ҫ�޸ĵ���(1-5, 0���沢�˳�): ");
//    while (1) {
//        scanf_s("%d", &choice);
//        getchar();
//
//        if (choice == 0) break;
//
//        switch (choice) {
//        case 1:
//            printf("�µĿγ�ID: ");
//            scanf_s("%d", &modified.course_id);
//            getchar();
//            break;
//        case 2:
//            printf("�µĽ���ID: ");
//            scanf_s("%d", &modified.classroom_id);
//            getchar();
//            break;
//        case 3:
//            printf("�µ��ܴ�(1-16): ");
//            scanf_s("%d", &modified.week);
//            getchar();
//            break;
//        case 4:
//            printf("�µ�����(1-7): ");
//            scanf_s("%d", &modified.day);
//            getchar();
//            break;
//        case 5:
//            printf("�µĽڴ�(1-12): ");
//            scanf_s("%d", &modified.slot);
//            getchar();
//            break;
//        default:
//            printf("��Чѡ��\n");
//        }
//        printf("�����ѡ��Ҫ�޸ĵ���(1-5, 0���沢�˳�): ");
//    }
//
//    // ���÷��������ſ�
//    ErrorCode result = get_schedule_service()->update_schedule(schedule_id,
//        modified.course_id, modified.classroom_id,
//        modified.week, modified.day, modified.slot);
//
//    if (result != SUCCESS) {
//        printf("�޸��ſ�ʧ��: %s\n", error_message(result));
//    }
//    else {
//        printf("�ſ��޸ĳɹ���\n");
//    }
//    system("pause");
//}

void view_all_schedules() {
    printf("\n===== �����ſ���Ϣ =====\n");

    // ��ȡ�ſη���ʵ��
    ScheduleService* service = get_schedule_service();
    if (service == NULL) {
        printf("�ſη����ʼ��ʧ�ܣ�\n");
        system("pause");
        return;
    }

    // ��ȡ�����ſ�����
    LinkedList* schedules = service->get_all_schedules();
    if (schedules == NULL || schedules->size == 0) {
        printf("�����ſ����ݣ�\n");
        system("pause");
        return;
    }

    // ��ӡ��ͷ
    printf("%-6s %-10s %-15s %-10s %-10s %-10s %-15s\n",
        "ID", "�γ�ID", "�γ�����", "����ID", "�ܴ�", "����", "�ڴ�");
    printf("------------------------------------------------------------\n");

    // �����ſ�����
    ListIterator it = list_begin(schedules);
    while (it != NULL) {
        Schedule* schedule = (Schedule*)it->data;

        // ��ȡ�γ���Ϣ
        Course* course = get_course_service()->get_course(schedule->course_id);
        const char* course_name = course ? course->name : "δ֪�γ�";

        printf("%-6d %-10d %-15s %-10d %-10d %-10d %-15d\n",
            schedule->id,
            schedule->course_id,
            course_name,
            schedule->classroom_id,
            schedule->week,
            schedule->day,
            schedule->slot);

        it = list_next(it);
    }

    printf("\n�� %zu ���ſμ�¼\n", schedules->size);
    system("pause");
}

void show_schedule_menu() {
    printf("\n===== �ſι���˵� =====\n");
    printf("1. �鿴�����ſ�\n");
    printf("2. ����ſ�\n");
    printf("3. �޸��ſ�\n");
    printf("4. ɾ���ſ�\n");
    printf("0. �����ϼ��˵�\n");
    printf("========================\n");
    printf("��ѡ�����: ");
}

void handle_schedule_input() {
    int choice;
    while (1) {
        system("cls");
        show_schedule_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч�����������֣�\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            view_all_schedules();
            break;
        case 2:
            add_schedule_ui();
            break;
        case 3:
            //modify_schedule_ui();
            break;
        case 4:
           // delete_schedule_ui();
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�����������룡\n");
            system("pause");
        }
    }
}