// dao/course_schedule/classroom_dao.c
#include "../include/dao/class_manage/classroom_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASSROOM_FILE "data/course_schedule/classrooms.dat"

static LinkedList* classroom_list = NULL;

LinkedList* load_all_classrooms() {
    FILE* file = fopen(CLASSROOM_FILE, "rb");
    if (file == NULL) {
        // 文件不存在时创建空链表
        classroom_list = list_create();
        return classroom_list;
    }

    classroom_list = list_create();
    Classroom room;

    while (fread(&room, sizeof(Classroom), 1, file) == 1) {
        Classroom* new_room = (Classroom*)safe_malloc(sizeof(Classroom));
        memcpy(new_room, &room, sizeof(Classroom));
        list_append(classroom_list, new_room);
    }

    fclose(file);
    return classroom_list;
}

ErrorCode save_all_classrooms(LinkedList* list) {
    if (list == NULL) {
        return ERR_INVALID_INPUT;
    }

    FILE* file = fopen(CLASSROOM_FILE, "wb");
    if (file == NULL) {
        return ERR_FILE_OPEN;
    }

    ListIterator it = list_begin(list);
    while (it != NULL) {
        Classroom* room = (Classroom*)it->data;
        if (fwrite(room, sizeof(Classroom), 1, file) != 1) {
            fclose(file);
            return ERR_FILE_WRITE;
        }
        it = list_next(it);
    }

    fclose(file);
    return SUCCESS;
}

Classroom* get_classroom_by_id(int id) {
    if (classroom_list == NULL) {
        load_all_classrooms();
    }

    ListIterator it = list_begin(classroom_list);
    while (it != NULL) {
        Classroom* room = (Classroom*)it->data;
        if (room->id == id) {
            return room;
        }
        it = list_next(it);
    }
    return NULL;
}

void free_classroom_memory(Classroom* classroom) {
    safe_free((void**)&classroom);
}

ClassroomDAO* get_classroom_dao() {
    static ClassroomDAO dao = {
        .load_all = load_all_classrooms,
        .save_all = save_all_classrooms,
        .free_classroom = free_classroom_memory,
        .get_by_id = get_classroom_by_id
    };
    return &dao;
}