
#include "../include/dao/class_manage/teacher_dao.h"
#include "../core/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEACHER_FILE "data/course_schedule/teachers.dat"

#define TEACHER_FILE "data/course_schedule/teachers.dat"

// �滻ԭ�е� load_all_teachers ����ʵ��
LinkedList* load_all_teachers() {
    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "rb");
    if (err != 0 || file == NULL) {
        printf("�޷��򿪽�ʦ�����ļ���\n");
        return NULL;
    }

    LinkedList* teachers = list_create();
    if (teachers == NULL) {
        fclose(file);
        return NULL;
    }

    Teacher teacher;
    while (fread(&teacher, sizeof(Teacher), 1, file) == 1) {
        Teacher* new_teacher = (Teacher*)safe_malloc(sizeof(Teacher));
        if (new_teacher == NULL) {
            list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
            fclose(file);
            return NULL;
        }
        *new_teacher = teacher;

        ErrorCode error = list_append(teachers, new_teacher);
        if (error != SUCCESS) {
            safe_free((void**)&new_teacher);
            list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
            fclose(file);
            return NULL;
        }
    }

    if (ferror(file)) {
        list_destroy(&teachers, (void (*)(void*))get_teacher_dao()->free_teacher);
        teachers = NULL;
    }

    fclose(file);

    if (teachers != NULL) {
        printf("�ɹ����� %zu ����ʦ����\n", teachers->size);
    }
    else {
        printf("���ؽ�ʦ����ʧ��\n");
    }

    return teachers;
}

       

ErrorCode save_all_teachers(LinkedList* list) {
    if (list == NULL) {
        return ERR_INVALID_INPUT;
    }

    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "wb");
    if (err != 0 || file == NULL) {
        return ERR_FILE_OPEN;
    }

    ErrorCode result = SUCCESS;
    ListIterator it = list_begin(list);
    while (it != NULL) {
        Teacher* teacher = (Teacher*)it->data;
        if (fwrite(teacher, sizeof(Teacher), 1, file) != 1) {
            result = ERR_FILE_WRITE;
            break;
        }
        it = list_next(it);
    }

    if (fflush(file) != 0) {
        result = ERR_FILE_WRITE;
    }

    fclose(file);
    return result;
}

void free_teacher_memory(Teacher* teacher) {
    safe_free((void**)&teacher);
}

// �޸� initialize_teacher_data_if_needed ����
void initialize_teacher_data_if_needed() {
    // ��鲢����Ŀ¼
    _mkdir("data");
    _mkdir("data/course_schedule");

    FILE* file = NULL;
    errno_t err = fopen_s(&file, TEACHER_FILE, "rb");
    if (err != 0 || file == NULL) {
        Teacher teachers[5] = {
            {1, "����", "����", "�������ѧ�뼼��ѧԺ"},
            {2, "����", "������", "��Ϣ����ѧԺ"},
            {3, "����", "��ʦ", "��ѧѧԺ"},
            {4, "����", "����", "����ѧԺ"},
            {5, "Ǯ��", "������", "��ѧ����ѧԺ"}
        };

        err = fopen_s(&file, TEACHER_FILE, "wb");
        if (err == 0 && file != NULL) {
            size_t written = fwrite(teachers, sizeof(Teacher), 5, file);
            fclose(file);
            if (written != 5) {
                remove(TEACHER_FILE); // д��ʧ����ɾ���ļ�
            }
        }
    }
    else {
        fclose(file);
    }
}

TeacherDAO* get_teacher_dao() {
    static TeacherDAO dao = {
        .load_all = load_all_teachers,
        .save_all = save_all_teachers,
        .free_teacher = free_teacher_memory
    };
    return &dao;
}