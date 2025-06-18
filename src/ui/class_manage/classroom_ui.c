// ui/course_schedule/classroom_ui.c
#include "../include/ui/class_manage/classroom_ui.h"
#include "../include/service/class_manage/classroom_service.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_classroom_menu() {
    printf("\n===== ���ҹ��� =====\n");
    printf("1. ��ӽ���\n");
    printf("2. �޸Ľ�����Ϣ\n");
    printf("3. ɾ������\n");
    printf("4. �鿴���н���\n");
    printf("0. �����ϼ��˵�\n");
    printf("====================\n");
    printf("��ѡ�����: ");
}

void add_classroom_ui() {
    int id, capacity, type;
    char building[10], number[10];

    printf("\n------ ��ӽ��� ------\n");
    printf("����ID: ");
    scanf_s("%d", &id);
    getchar();

    printf("��ѧ¥(��:A): ");
    scanf_s("%9s", building, (unsigned)_countof(building));
    getchar();

    printf("���Һ�(��:101): ");
    scanf_s("%9s", number, (unsigned)_countof(number));
    getchar();

    printf("����: ");
    scanf_s("%d", &capacity);
    getchar();

    printf("����(0:��ͨ����, 1:ʵ����): ");
    scanf_s("%d", &type);
    getchar();

    // �������Ҷ���
    Classroom* new_classroom = (Classroom*)safe_malloc(sizeof(Classroom));
    new_classroom->id = id;
    strncpy_s(new_classroom->building, sizeof(new_classroom->building), building, _TRUNCATE);
    strncpy_s(new_classroom->number, sizeof(new_classroom->number), number, _TRUNCATE);
    new_classroom->capacity = capacity;
    new_classroom->type = type;

    // ���÷������ӽ���
    ErrorCode error = get_classroom_service()->add_classroom(new_classroom);
    printf("%s\n", error_message(error));
    system("pause");
}

void list_all_classrooms_ui() {
    printf("\n------ �����б� ------\n");

    LinkedList* list = get_classroom_service()->get_all_classrooms();
    if (list == NULL || list->size == 0) {
        printf("���޽������ݣ�\n");
        system("pause");
        return;
    }

    printf("%-6s %-10s %-10s %-8s %-10s\n",
        "ID", "��ѧ¥", "���Һ�", "����", "����");
    printf("----------------------------------------\n");

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Classroom* room = (Classroom*)it->data;
        printf("%-6d %-10s %-10s %-8d %-10s\n",
            room->id, room->building, room->number,
            room->capacity, room->type == 0 ? "��ͨ����" : "ʵ����");
        it = list_next(it);
    }

    printf("\n�� %zu �����\n", list->size);
    system("pause");
}

void handle_classroom_input() {
    int choice;
    while (1) {
        system("cls");
        show_classroom_menu();

        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч��������һ������.\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            add_classroom_ui();
            break;
        case 2:
            printf("�޸Ľ�����Ϣ - ��ʵ��\n");
            system("pause");
            break;
        case 3:
            printf("ɾ������ - ��ʵ��\n");
            system("pause");
            break;
        case 4:
            list_all_classrooms_ui();
            break;
        case 0:
            return;
        default:
            printf("��Ч���룬������ѡ��\n");
            system("pause");
        }
    }
}