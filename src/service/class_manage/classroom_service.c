#include "../include/service/class_manage/classroom_service.h"
#include "../../include/dao/class_manage/classroom_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 全局教室链表指针
static LinkedList* classroom_list = NULL;

// 初始化教室链表
static void init_classroom_list() {
    if (classroom_list == NULL) {
        classroom_list = get_classroom_dao()->load_all();
        if (classroom_list == NULL) {
            classroom_list = list_create();
        }
    }
}

// 添加教室
ErrorCode add_classroom(Classroom* classroom) {
    // 参数检查
    if (classroom == NULL) {
        return ERR_INVALID_INPUT;
    }

    init_classroom_list();

    // 检查教室ID是否已存在
    Classroom* existing = get_classroom_dao()->get_by_id(classroom->id);
    if (existing != NULL) {
        return ERR_DUPLICATE;
    }

    // 创建新教室对象（深拷贝）
    Classroom* new_classroom = (Classroom*)safe_malloc(sizeof(Classroom));
    *new_classroom = *classroom; // 结构体直接拷贝

    // 添加到链表
    ErrorCode error = list_append(classroom_list, new_classroom);
    if (error != SUCCESS) {
        safe_free((void**)&new_classroom);
        return error;
    }

    // 持久化到文件
    error = get_classroom_dao()->save_all(classroom_list);
    if (error != SUCCESS) {
        // 回滚：从链表中移除
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

// 根据ID获取教室
Classroom* get_classroom(int id) {
    init_classroom_list();
    return get_classroom_dao()->get_by_id(id);
}

// 获取所有教室
LinkedList* get_all_classrooms() {
    init_classroom_list();
    return classroom_list;
}

// 更新教室信息
ErrorCode update_classroom(int id, const char* building, const char* number, int capacity, int type) {
    Classroom* room = get_classroom(id);
    if (room == NULL) return ERR_NOT_FOUND;

    // 更新字段（保留原值如果新值为NULL/0）
    if (building) strncpy_s(room->building, sizeof(room->building), building, _TRUNCATE);
    if (number) strncpy_s(room->number, sizeof(room->number), number, _TRUNCATE);
    if (capacity > 0) room->capacity = capacity;
    if (type >= 0) room->type = type;

    return get_classroom_dao()->save_all(classroom_list);
}

// 删除教室
ErrorCode delete_classroom(int id) {
    init_classroom_list();

    ListNode* prev = NULL, * curr = classroom_list->head;
    while (curr != NULL) {
        Classroom* room = (Classroom*)curr->data;
        if (room->id == id) {
            // 从链表中移除
            if (prev) prev->next = curr->next;
            else classroom_list->head = curr->next;

            if (curr == classroom_list->tail) {
                classroom_list->tail = prev;
            }

            classroom_list->size--;

            // 释放内存
            get_classroom_dao()->free_classroom(room);
            safe_free((void**)&curr);

            // 保存更改
            return get_classroom_dao()->save_all(classroom_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

// 获取教室服务实例（唯一实现）
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