// service/class_manage/course_service.c
#include "../../include/service/class_manage/course_service.h"
#include "../../include/dao/class_manage/course_dao.h"
#include "../core/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static LinkedList* course_list = NULL;

void init_course_list() {
    if (course_list == NULL) {
        course_list = get_course_dao()->load_all();
    }
}

ErrorCode add_course(Course* course) {
    if (course == NULL) {
        return ERR_INVALID_INPUT;
    }

    init_course_list();

    // 检查课程ID是否已存在
    ListIterator it = list_begin(course_list);
    while (it != NULL) {
        Course* existing = (Course*)it->data;
        if (existing->id == course->id) {
            return ERR_DUPLICATE;
        }
        it = list_next(it);
    }

    // 添加到列表
    ErrorCode error = list_append(course_list, course);
    if (error != SUCCESS) {
        return error;
    }

    // 保存到文件
    return get_course_dao()->save_all(course_list);
}

LinkedList* get_all_courses() {
    init_course_list();
    return course_list;
}


Course* get_course(int id) {
    init_course_list();
    ListIterator it = list_begin(course_list);
    while (it != NULL) {
        Course* course = (Course*)it->data;
        if (course->id == id) {
            return course;
        }
        it = list_next(it);
    }
    return NULL;
}

ErrorCode update_course(int id, Course* course) {
    init_course_list();
    ListIterator it = list_begin(course_list);
    while (it != NULL) {
        Course* existing = (Course*)it->data;
        if (existing->id == id) {
            existing->id = course->id;
            strncpy_s(existing->name, sizeof(existing->name), course->name, _TRUNCATE);
            existing->credit = course->credit;
            existing->hours = course->hours;
            existing->teacher_id = course->teacher_id;
            existing->student_count = course->student_count;

            // 保存到文件
            return get_course_dao()->save_all(course_list);
        }
        it = list_next(it);
    }
    return ERR_NOT_FOUND;
}

ErrorCode delete_course(int id) {
    init_course_list();
    ListNode* prev = NULL, * curr = course_list->head;
    while (curr != NULL) {
        Course* course = (Course*)curr->data;
        if (course->id == id) {
            // 从列表中移除
            if (prev) prev->next = curr->next;
            else course_list->head = curr->next;

            if (curr == course_list->tail) {
                course_list->tail = prev;
            }

            course_list->size--;

            // 释放内存
            get_course_dao()->free_course(course);
            safe_free((void**)&curr);

            // 保存到文件
            return get_course_dao()->save_all(course_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

CourseService* get_course_service() {
    static CourseService service = {
        .add_course = add_course,
        .get_all_courses = get_all_courses,
        .get_course = get_course,
        .update_course = update_course,
        .delete_course = delete_course
    };
    return &service;
}