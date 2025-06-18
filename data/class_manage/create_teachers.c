// create_teachers.c ���������ߣ�
#define _CRT_SECURE_NO_WARNINGS
#include "../core/course_schedule.h"
#include <stdio.h>
#include <string.h>

#define TEACHER_FILE "data/course_schedule/teachers.dat"

void create_initial_teachers() {
    Teacher teachers[5] = { 0 };

    // ��ʼ����ʦ���ݣ�ʹ��strncpy_s��
    teachers[0] = (Teacher){ 1, "����", "����", "�������ѧ�뼼��ѧԺ" };
    teachers[1] = (Teacher){ 2, "����", "������", "��Ϣ����ѧԺ" };
    teachers[2] = (Teacher){ 3, "����", "��ʦ", "��ѧѧԺ" };
    teachers[3] = (Teacher){ 4, "����", "����", "����ѧԺ" };
    teachers[4] = (Teacher){ 5, "Ǯ��", "������", "��ѧ����ѧԺ" };

    FILE* file = fopen(TEACHER_FILE, "wb");
    if (file) {
        fwrite(teachers, sizeof(Teacher), 5, file);
        fclose(file);
        printf("��ʼ��ʦ����������\n");
    }
    else {
        perror("�����ļ�ʧ��");
    }
}

