#include "../include/service/class_manage/classroom_service.h"
#include "../../include/dao/class_manage/classroom_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ȫ�ֽ�������ָ��
static LinkedList* classroom_list = NULL;

// ��ʼ����������
static void init_classroom_list() {
    if (classroom_list == NULL) {
        classroom_list = get_classroom_dao()->load_all();
        if (classroom_list == NULL) {
            classroom_list = list_create();
        }
    }
}

// ��ӽ���
ErrorCode add_classroom(Classroom* classroom) {
    // �������
    if (classroom == NULL) {
        return ERR_INVALID_INPUT;
    }

    init_classroom_list();

    // ������ID�Ƿ��Ѵ���
    Classroom* existing = get_classroom_dao()->get_by_id(classroom->id);
    if (existing != NULL) {
        return ERR_DUPLICATE;
    }

    // �����½��Ҷ��������
    Classroom* new_classroom = (Classroom*)safe_malloc(sizeof(Classroom));
    *new_classroom = *classroom; // �ṹ��ֱ�ӿ���

    // ��ӵ�����
    ErrorCode error = list_append(classroom_list, new_classroom);
    if (error != SUCCESS) {
        safe_free((void**)&new_classroom);
        return error;
    }

    // �־û����ļ�
    error = get_classroom_dao()->save_all(classroom_list);
    if (error != SUCCESS) {
        // �ع������������Ƴ�
        ListNode* prev = NULL, * curr = classroom_list->head;
        while (curr != NULL) {
            if (curr->data == new_classroom) {
                if (prev) prev->next = curr->next;
                else classroom_list->head = curr->next;

                if (curr == classroom_list->tail) {
                    classroom_list->tail = prev;
                }

                classroom_list->size--;
                safe_free((void**)&curr);
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        safe_free((void**)&new_classroom);
    }

    return error;
}

// ����ID��ȡ����
Classroom* get_classroom(int id) {
    init_classroom_list();
    return get_classroom_dao()->get_by_id(id);
}

// ��ȡ���н���
LinkedList* get_all_classrooms() {
    init_classroom_list();
    return classroom_list;
}

// ���½�����Ϣ
ErrorCode update_classroom(int id, const char* building, const char* number, int capacity, int type) {
    Classroom* room = get_classroom(id);
    if (room == NULL) return ERR_NOT_FOUND;

    // �����ֶΣ�����ԭֵ�����ֵΪNULL/0��
    if (building) strncpy_s(room->building, sizeof(room->building), building, _TRUNCATE);
    if (number) strncpy_s(room->number, sizeof(room->number), number, _TRUNCATE);
    if (capacity > 0) room->capacity = capacity;
    if (type >= 0) room->type = type;

    return get_classroom_dao()->save_all(classroom_list);
}

// ɾ������
ErrorCode delete_classroom(int id) {
    init_classroom_list();

    ListNode* prev = NULL, * curr = classroom_list->head;
    while (curr != NULL) {
        Classroom* room = (Classroom*)curr->data;
        if (room->id == id) {
            // ���������Ƴ�
            if (prev) prev->next = curr->next;
            else classroom_list->head = curr->next;

            if (curr == classroom_list->tail) {
                classroom_list->tail = prev;
            }

            classroom_list->size--;

            // �ͷ��ڴ�
            get_classroom_dao()->free_classroom(room);
            safe_free((void**)&curr);

            // �������
            return get_classroom_dao()->save_all(classroom_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

// ��ȡ���ҷ���ʵ����Ψһʵ�֣�
ClassroomService* get_classroom_service() {
    static ClassroomService service = {
        .add_classroom = add_classroom,
        .get_classroom = get_classroom,
        .get_all_classrooms = get_all_classrooms,
        .update_classroom = update_classroom,
        .delete_classroom = delete_classroom
    };
    return &service;
}