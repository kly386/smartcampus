// ui/course_schedule/teacher_ui.c
#include "../include/ui/class_manage/teacher_ui.h"
#include "../include/service/class_manage//teacher_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_teacher_menu() {
    printf("\n===== ��ʦ���� =====\n");
    printf("1. ��ӽ�ʦ\n");
    printf("2. �޸Ľ�ʦ��Ϣ\n");
    printf("3. ɾ����ʦ\n");
    printf("4. �鿴���н�ʦ\n");
    printf("0. �����ϼ��˵�\n");
    printf("=====================\n");
    printf("��ѡ�����: ");
}

void add_teacher_ui() {
    int id;
    char name[20];
    char title[20];
    char department[30];

    printf("\n------ ��ӽ�ʦ ------\n");
    printf("��ʦID: ");
    scanf_s("%d", &id);
    getchar(); // ������뻺����

    printf("����: ");
    scanf_s("%19s", name, (unsigned)_countof(name));
    getchar();

    printf("ְ��: ");
    scanf_s("%19s", title, (unsigned)_countof(title));
    getchar();

    printf("����Ժϵ: ");
    scanf_s("%29s", department, (unsigned)_countof(department));
    getchar();

    ErrorCode error = get_teacher_service()->add_teacher(id, name, title, department);
    printf("%s\n", error_message(error));
    system("pause");
}

// ui/course_schedule/teacher_ui.c (��������)
void modify_teacher_ui() {
    int id;
    printf("\n------ �޸Ľ�ʦ��Ϣ ------\n");
    printf("������Ҫ�޸ĵĽ�ʦID: ");
    scanf_s("%d", &id);
    getchar();

    // ��ȡ���н�ʦ��Ϣ
    Teacher* teacher = get_teacher_service()->get_teacher(id);
    if (teacher == NULL) {
        printf("����: δ�ҵ��ý�ʦ��¼��\n");
        system("pause");
        return;
    }

    // ��ʾ��ǰ��Ϣ
    printf("\n��ǰ��ʦ��Ϣ:\n");
    printf("1. ����: %s\n", teacher->name);
    printf("2. ְ��: %s\n", teacher->title);
    printf("3. ����Ժϵ: %s\n", teacher->department);

    // ��ȡ�޸���Ϣ
    char name[20], title[20], department[30];
    int choice;
    printf("\n��ѡ��Ҫ�޸ĵ���(1-3, 0���沢�˳�): ");
    while (1) {
        scanf_s("%d", &choice);
        getchar();

        if (choice == 0) break;

        switch (choice) {
        case 1:
            printf("�µ�����: ");
            scanf_s("%19s", name, (unsigned)_countof(name));
            getchar();
            strncpy_s(teacher->name, sizeof(teacher->name), name, _TRUNCATE);
            break;
        case 2:
            printf("�µ�ְ��: ");
            scanf_s("%19s", title, (unsigned)_countof(title));
            getchar();
            strncpy_s(teacher->title, sizeof(teacher->title), title, _TRUNCATE);
            break;
        case 3:
            printf("�µ�����Ժϵ: ");
            scanf_s("%29s", department, (unsigned)_countof(department));
            getchar();
            strncpy_s(teacher->department, sizeof(teacher->department), department, _TRUNCATE);
            break;
        default:
            printf("��Чѡ��\n");
        }
        printf("�����ѡ��Ҫ�޸ĵ���(1-3, 0���沢�˳�): ");
    }

    // ���÷������½�ʦ
    ErrorCode result = get_teacher_service()->update_teacher(teacher->id,
        teacher->name, teacher->title, teacher->department);

    if (result != SUCCESS) {
        printf("�޸Ľ�ʦ��Ϣʧ��: %s\n", error_message(result));
    }
    else {
        printf("��ʦ��Ϣ�޸ĳɹ���\n");
    }
    system("pause");
}


// ui/course_schedule/teacher_ui.c (��������)
void delete_teacher_ui() {
    int teacher_id;
    printf("\n------ ɾ����ʦ ------\n");
    printf("������Ҫɾ���Ľ�ʦID: ");
    scanf_s("%d", &teacher_id);
    getchar();

    // �Ȼ�ȡ��ʦ��Ϣ����ȷ��
    Teacher* teacher = get_teacher_service()->get_teacher(teacher_id);
    if (teacher == NULL) {
        printf("����: δ�ҵ��ý�ʦ��¼��\n");
        system("pause");
        return;
    }

    // ��ʾ��ʦ����
    printf("\n����ɾ�����½�ʦ:\n");
    printf("��ʦID: %d\n", teacher->id);
    printf("����: %s\n", teacher->name);
    printf("ְ��: %s\n", teacher->title);
    printf("����Ժϵ: %s\n", teacher->department);

    // ȷ��ɾ��
    printf("\nȷ��ɾ����(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    getchar();

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode result = get_teacher_service()->delete_teacher(teacher->id);
        if (result != SUCCESS) {
            printf("ɾ����ʦʧ��: %s\n", error_message(result));
        }
        else {
            printf("��ʦɾ���ɹ���\n");
        }
    }
    else {
        printf("��ȡ��ɾ������\n");
    }
    system("pause");
}


void list_all_teachers_ui() {
    printf("\n------ ��ʦ�б� ------\n");

    LinkedList* list = get_teacher_service()->get_all_teachers();
    if (list == NULL || list->size == 0) {
        printf("���޽�ʦ���ݣ�\n");
        system("pause");
        return;
    }

    printf("%-6s %-20s %-20s %-30s\n", "ID", "����", "ְ��", "Ժϵ");
    printf("------------------------------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Teacher* teacher = (Teacher*)it->data;
        printf("%-6d %-20s %-20s %-30s\n",
            teacher->id, teacher->name, teacher->title, teacher->department);
        it = list_next(it);
    }

    printf("\n�� %zu ����ʦ\n", list->size);
    system("pause");
}

// ui/course_schedule/teacher_ui.c (����handle_teacher_input����)
// �޸� handle_teacher_input �����е� case 2,3,4 ����
void handle_teacher_input() {
    int choice;
    while (1) {
        system("cls");
        show_teacher_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч�����������֣�\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_teacher_ui();
            break;
        case 2:
            modify_teacher_ui();  // �Ƴ� initialize_teacher_data_if_needed()
            break;
        case 3:
            delete_teacher_ui();  // �Ƴ� initialize_teacher_data_if_needed()
            break;
        case 4:
            list_all_teachers_ui();
            break;
        case 0:
            return;
        default:
            printf("��Чѡ�����������룡\n");
            system("pause");
        }
    }
}