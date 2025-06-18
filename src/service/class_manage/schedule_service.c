#include "../include/service/class_manage/schedule_service.h"
#include "../include/service/class_manage/course_service.h"
#include "../include/service/class_manage/classroom_service.h"
#include "../include/dao/class_manage/schedule_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>

static LinkedList* schedule_list = NULL;

LinkedList* get_all_schedules_impl() {
    if (schedule_list == NULL) {
        schedule_list = get_schedule_dao()->load_all();
    }
    return schedule_list;
}

// service/course_schedule/schedule_service.c
// �������ʵ��

ErrorCode add_schedule_impl(Schedule* schedule) {
    if (schedule == NULL) return ERR_INVALID_INPUT;

    // ���ʱ���ͻ
    if (get_schedule_dao()->check_conflict(schedule->classroom_id,
        schedule->week,
        schedule->day,
        schedule->slot)) {
        return ERR_DUPLICATE;
    }

    // �������ſζ���
    Schedule* new_schedule = (Schedule*)safe_malloc(sizeof(Schedule));
    *new_schedule = *schedule;

    // ��ӵ�����
    ErrorCode error = list_append(schedule_list, new_schedule);
    if (error != SUCCESS) {
        safe_free((void**)&new_schedule);
        return error;
    }

    // ���浽�ļ�
    return get_schedule_dao()->save_all(schedule_list);
}

ErrorCode update_schedule_impl(int id, int course_id, int classroom_id,
    int week, int day, int slot) {
    Schedule* schedule = get_schedule_dao()->get_by_id(id);
    if (schedule == NULL) return ERR_NOT_FOUND;

    // ���ʱ���ͻ���ų�����
    if (get_schedule_dao()->check_conflict(classroom_id, week, day, slot)) {
        if (!(schedule->classroom_id == classroom_id &&
            schedule->week == week &&
            schedule->day == day &&
            schedule->slot == slot)) {
            return ERR_DUPLICATE;
        }
    }

    // �����ֶ�
    schedule->course_id = course_id;
    schedule->classroom_id = classroom_id;
    schedule->week = week;
    schedule->day = day;
    schedule->slot = slot;

    return get_schedule_dao()->save_all(schedule_list);
}

ErrorCode delete_schedule_impl(int id) {
    ListNode* prev = NULL, * curr = schedule_list->head;
    while (curr != NULL) {
        Schedule* schedule = (Schedule*)curr->data;
        if (schedule->id == id) {
            // ���������Ƴ�
            if (prev) prev->next = curr->next;
            else schedule_list->head = curr->next;

            if (curr == schedule_list->tail) {
                schedule_list->tail = prev;
            }

            schedule_list->size--;

            // �ͷ��ڴ�
            get_schedule_dao()->free_schedule(schedule);
            safe_free((void**)&curr);

            // �������
            return get_schedule_dao()->save_all(schedule_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

// ����get_schedule_service()����
ScheduleService* get_schedule_service() {
    static ScheduleService service = {
        // ԭ�г�ʼ��
        .add_schedule = add_schedule_impl,
        .update_schedule = update_schedule_impl,
        .delete_schedule = delete_schedule_impl
        // ������ʼ��...
    };
    return &service;
}