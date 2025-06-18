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
// 添加以下实现

ErrorCode add_schedule_impl(Schedule* schedule) {
    if (schedule == NULL) return ERR_INVALID_INPUT;

    // 检查时间冲突
    if (get_schedule_dao()->check_conflict(schedule->classroom_id,
        schedule->week,
        schedule->day,
        schedule->slot)) {
        return ERR_DUPLICATE;
    }

    // 创建新排课对象
    Schedule* new_schedule = (Schedule*)safe_malloc(sizeof(Schedule));
    *new_schedule = *schedule;

    // 添加到链表
    ErrorCode error = list_append(schedule_list, new_schedule);
    if (error != SUCCESS) {
        safe_free((void**)&new_schedule);
        return error;
    }

    // 保存到文件
    return get_schedule_dao()->save_all(schedule_list);
}

ErrorCode update_schedule_impl(int id, int course_id, int classroom_id,
    int week, int day, int slot) {
    Schedule* schedule = get_schedule_dao()->get_by_id(id);
    if (schedule == NULL) return ERR_NOT_FOUND;

    // 检查时间冲突（排除自身）
    if (get_schedule_dao()->check_conflict(classroom_id, week, day, slot)) {
        if (!(schedule->classroom_id == classroom_id &&
            schedule->week == week &&
            schedule->day == day &&
            schedule->slot == slot)) {
            return ERR_DUPLICATE;
        }
    }

    // 更新字段
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
            // 从链表中移除
            if (prev) prev->next = curr->next;
            else schedule_list->head = curr->next;

            if (curr == schedule_list->tail) {
                schedule_list->tail = prev;
            }

            schedule_list->size--;

            // 释放内存
            get_schedule_dao()->free_schedule(schedule);
            safe_free((void**)&curr);

            // 保存更改
            return get_schedule_dao()->save_all(schedule_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

// 更新get_schedule_service()函数
ScheduleService* get_schedule_service() {
    static ScheduleService service = {
        // 原有初始化
        .add_schedule = add_schedule_impl,
        .update_schedule = update_schedule_impl,
        .delete_schedule = delete_schedule_impl
        // 其他初始化...
    };
    return &service;
}