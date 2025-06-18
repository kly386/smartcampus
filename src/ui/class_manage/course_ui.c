// ui/class_manage/course_ui.c
#include "../../include/ui/class_manage/course_ui.h"
#include "../../include/service/class_manage/course_service.h"
#include "../core/common.h"
#include "../core/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_course_menu() {
    printf("\n===== �γ̹��� =====\n");
    printf("1. ��ӿγ�\n");
    printf("2. �޸Ŀγ���Ϣ\n");
    printf("3. ɾ���γ�\n");
    printf("4. �鿴���пγ�\n");
    printf("0. �������˵�\n");
    printf("=====================\n");
    printf("��ѡ�����: ");
}

void add_course_ui() {
    int id, credit, hours, teacher_id, student_count;
    char name[30];

    printf("\n------ ��ӿγ� ------\n");
    printf("�γ�ID: ");
    scanf_s("%d", &id);
    getchar();

    printf("�γ�����: ");
    scanf_s("%29s", name, (unsigned)_countof(name));
    getchar();

    printf("ѧ��: ");
    scanf_s("%d", &credit);
    getchar();

    printf("��ʱ: ");
    scanf_s("%d", &hours);
    getchar();

    printf("�ον�ʦID: ");
    scanf_s("%d", &teacher_id);
    getchar();

    printf("ѧ������: ");
    scanf_s("%d", &student_count);
    getchar();

    // �����¿γ̶�����ӵ��б�
    Course* new_course = (Course*)safe_malloc(sizeof(Course));
    new_course->id = id;
    strncpy_s(new_course->name, sizeof(new_course->name), name, _TRUNCATE);
    new_course->credit = credit;
    new_course->hours = hours;
    new_course->teacher_id = teacher_id;
    new_course->student_count = student_count;

    // ���÷������ӿγ�
    ErrorCode error = get_course_service()->add_course(new_course);
    printf("%s\n", error_message(error));
    system("pause");
}

void modify_course_ui() {
    int id;
    printf("\n------ �޸Ŀγ���Ϣ ------\n");
    printf("������Ҫ�޸ĵĿγ�ID: ");
    scanf_s("%d", &id);
    getchar();

    // ��ȡҪ�޸ĵĿγ���Ϣ
    Course* course = get_course_service()->get_course(id);
    if (course == NULL) {
        printf("����: δ�ҵ��ÿγ̼�¼��\n");
        system("pause");
        return;
    }

    // ��ʾ��ǰ��Ϣ
    printf("\n��ǰ�γ���Ϣ:\n");
    printf("1. �γ�����: %s\n", course->name);
    printf("2. ѧ��: %d\n", course->credit);
    printf("3. ��ʱ: %d\n", course->hours);
    printf("4. �ον�ʦID: %d\n", course->teacher_id);
    printf("5. ѧ������: %d\n", course->student_count);

    // ��ȡ�޸���Ϣ
    Course modified = *course;
    int choice;
    printf("\n��ѡ��Ҫ�޸ĵ���(1-5, 0��ʾ�˳�): ");
    while (1) {
        scanf_s("%d", &choice);
        getchar();

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("�µĿγ�����: ");
            scanf_s("%29s", modified.name, (unsigned)_countof(modified.name));
            getchar();
            break;
        case 2:
            printf("�µ�ѧ��: ");
            scanf_s("%d", &modified.credit);
            getchar();
            break;
        case 3:
            printf("�µĿ�ʱ: ");
            scanf_s("%d", &modified.hours);
            getchar();
            break;
        case 4:
            printf("�µ��ον�ʦID: ");
            scanf_s("%d", &modified.teacher_id);
            getchar();
            break;
        case 5:
            printf("�µ�ѧ������: ");
            scanf_s("%d", &modified.student_count);
            getchar();
            break;
        default:
            printf("��Чѡ�����������롣\n");
        }
        printf("��ѡ��Ҫ�޸ĵ���(1-5, 0��ʾ�˳�): ");
    }

    // ���÷������¿γ���Ϣ
    ErrorCode result = get_course_service()->update_course(id, &modified);

    if (result != SUCCESS) {
        printf("�޸Ŀγ���Ϣʧ��: %s\n", error_message(result));
    }
    else {
        printf("�γ���Ϣ�޸ĳɹ���\n");
    }
    system("pause");
}

void delete_course_ui() {
    int course_id;
    printf("\n------ ɾ���γ� ------\n");
    printf("������Ҫɾ���Ŀγ�ID: ");
    scanf_s("%d", &course_id);
    getchar();

    // �Ȼ�ȡ�γ���Ϣ����ȷ��
    Course* course = get_course_service()->get_course(course_id);
    if (course == NULL) {
        printf("����: δ�ҵ��ÿγ̼�¼��\n");
        system("pause");
        return;
    }

    // ��ʾ�γ���Ϣ
    printf("\n����ɾ���Ŀγ���Ϣ:\n");
    printf("�γ�ID: %d\n", course->id);
    printf("�γ�����: %s\n", course->name);
    printf("ѧ��: %d\n", course->credit);
    printf("��ʱ: %d\n", course->hours);
    printf("�ον�ʦID: %d\n", course->teacher_id);
    printf("ѧ������: %d\n", course->student_count);

    // ȷ��ɾ��
    printf("\nȷ��ɾ����?(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    getchar();

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode result = get_course_service()->delete_course(course_id);
        if (result != SUCCESS) {
            printf("ɾ���γ�ʧ��: %s\n", error_message(result));
        }
        else {
            printf("�γ�ɾ���ɹ���\n");
        }
    }
    else {
        printf("ȡ��ɾ��������\n");
    }
    system("pause");
}

void list_all_courses_ui() {
    printf("\n------ �γ��б� ------\n");

    LinkedList* list = get_course_service()->get_all_courses();
    if (list == NULL || list->size == 0) {
        printf("���޿γ����ݡ�\n");
        system("pause");
        return;
    }

    printf("%-6s %-30s %-6s %-6s %-10s %-6s\n",
        "ID", "�γ�����", "ѧ��", "��ʱ", "��ʦID", "ѧ����");
    printf("------------------------------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Course* course = (Course*)it->data;
        printf("%-6d %-30s %-6d %-6d %-10d %-6d\n",
            course->id, course->name, course->credit,
            course->hours, course->teacher_id, course->student_count);
        it = list_next(it);
    }

    printf("\n�� %zu �ſγ�\n", list->size);
    system("pause");
}

void handle_course_input() {
    int choice;
    while (1) {
        system("cls");
        show_course_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч������������һ��������\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_course_ui();
            break;
        case 2:
            modify_course_ui();
            break;
        case 3:
            delete_course_ui();
            break;
        case 4:
            list_all_courses_ui();
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�����������롣\n");
            system("pause");
        }
    }
}