
#include "../include/service/class_manage/teacher_service.h"
#include "../include/dao/class_manage/teacher_dao.h"
#include <stdio.h>
#include <string.h>

static LinkedList* teacher_list = NULL;

// 前向声明
static LinkedList* get_all_teachers();

// 修改 init_teacher_list 函数
void init_teacher_list() {
    if (teacher_list == NULL) {
        teacher_list = get_teacher_dao()->load_all();
        if (teacher_list == NULL) {
            // 如果加载失败，创建空列表并尝试初始化默认数据
            teacher_list = list_create();
            initialize_teacher_data_if_needed();
            teacher_list = get_teacher_dao()->load_all();
        }
    }
}

Teacher* get_teacher(int id) {
    init_teacher_list();
    if (teacher_list == NULL) return NULL;

    ListIterator it = list_begin(teacher_list);
    while (it != NULL) {
        Teacher* teacher = (Teacher*)it->data;
        if (teacher->id == id) {
            return teacher;
        }
        it = list_next(it);
    }
    return NULL;
}

ErrorCode add_teacher(int id, const char* name, const char* title, const char* department) {
    if (name == NULL || title == NULL || department == NULL) {
        return ERR_INVALID_INPUT;
    }

    init_teacher_list();

    if (get_teacher(id) != NULL) {
        return ERR_DUPLICATE;
    }

    Teacher* new_teacher = (Teacher*)safe_malloc(sizeof(Teacher));
    new_teacher->id = id;

    strncpy_s(new_teacher->name, sizeof(new_teacher->name), name, _TRUNCATE);
    strncpy_s(new_teacher->title, sizeof(new_teacher->title), title, _TRUNCATE);
    strncpy_s(new_teacher->department, sizeof(new_teacher->department), department, _TRUNCATE);

    ErrorCode error = list_append(teacher_list, new_teacher);
    if (error != SUCCESS) {
        safe_free((void**)&new_teacher);
        return error;
    }

    error = get_teacher_dao()->save_all(teacher_list);
    return error;
}

ErrorCode update_teacher(int id, const char* name, const char* title, const char* department) {
    Teacher* teacher = get_teacher(id);
    if (teacher == NULL) return ERR_NOT_FOUND;

    if (name) strncpy_s(teacher->name, sizeof(teacher->name), name, _TRUNCATE);
    if (title) strncpy_s(teacher->title, sizeof(teacher->title), title, _TRUNCATE);
    if (department) strncpy_s(teacher->department, sizeof(teacher->department), department, _TRUNCATE);

    return get_teacher_dao()->save_all(teacher_list);
}

ErrorCode delete_teacher(int id) {
    init_teacher_list();

    ListNode* prev = NULL, * curr = teacher_list->head;
    while (curr != NULL) {
        Teacher* teacher = (Teacher*)curr->data;
        if (teacher->id == id) {
            if (prev) prev->next = curr->next;
            else teacher_list->head = curr->next;

            if (curr == teacher_list->tail) {
                teacher_list->tail = prev;
            }

            teacher_list->size--;

            get_teacher_dao()->free_teacher(teacher);
            safe_free((void**)&curr);

            return get_teacher_dao()->save_all(teacher_list);
        }
        prev = curr;
        curr = curr->next;
    }
    return ERR_NOT_FOUND;
}

// 实现 get_all_teachers 函数
static LinkedList* get_all_teachers() {
    init_teacher_list();
    return teacher_list;
}

TeacherService* get_teacher_service() {
    static TeacherService service = {
        .add_teacher = add_teacher,
        .get_teacher = get_teacher,
        .update_teacher = update_teacher,
        .delete_teacher = delete_teacher,
        .get_all_teachers = get_all_teachers
    };
    return &service;
}