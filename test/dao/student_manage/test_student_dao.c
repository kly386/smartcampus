//#include<stdio.h>  
//#include<stdlib.h>  
//
//// �������ݷ���1  
//static int* load_data_methed1() {  
//    int* data = (int*)malloc(3 * sizeof(int)); // ����3���������ڴ�  
//    data[0] = 100;  
//    data[1] = 200;  
//    data[z2] = 300;  
//    return data; // ���ط�����ڴ��ַ  
//}  
//int* load_data_methed2() {
//    int* data = (int*)malloc(34* sizeof(int)); // ����3���������ڴ�  
//    data[0] = 10;
//    data[1] = 20;
//    data[2] = 30;
//	data[3] = 40;
//    return data; // ���ط�����ڴ��ַ  
//}
//int main() {  
//	int* (*load_all)();//��������ָ��
//	load_all = load_data_methed2; // ָ��load_data_methed1��������������������ַ
//
//	int* user_data = load_all(); // ���ú���ָ�룬��ȡ����
//    for(int i = 0; i < 4; i++) {  
//        printf("%d\n", user_data[i]); // �������  
//	}
//	printf("\n");   
//    return 0;  
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dao/student_manage/student_dao.h"
#include "core/list.h"

// �򵥶��Ժ�
#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            printf("[ʧ��] %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return 0; \
        } \
    } while (0)

// ���Ա���ͼ���ѧ����Ϣ
int test_save_and_load() {
    StudentDAO* dao = get_student_dao();
    LinkedList* list = list_create();

    // �����������
    Student* s1 = (Student*)malloc(sizeof(Student));
    strcpy_s(s1->id, sizeof(s1->id), "1001");
    strcpy_s(s1->name, sizeof(s1->name), "����");
    s1->gpa = 3.8f;
    strcpy_s(s1->major, sizeof(s1->major), "�����");

    Student* s2 = (Student*)malloc(sizeof(Student));
    strcpy_s(s2->id, sizeof(s2->id), "1002");
    strcpy_s(s2->name, sizeof(s2->name), "����");
    s2->gpa = 3.5f;
    strcpy_s(s2->major, sizeof(s2->major), "��ѧ");

    list_append(list, s1);
    list_append(list, s2);

    // ���浽�ļ�
    ASSERT_TRUE(dao->save_all(list) == 0);

    // �ͷ�ԭ����
    list_destroy(&list, (void (*)(void*))dao->free_student);

    // ���ļ�����
    LinkedList* loaded = dao->load_all();
    ASSERT_TRUE(loaded != NULL);
    ASSERT_TRUE(loaded->size == 2);

    // �������һ����
    ListIterator it = list_begin(loaded);
    Student* stu = (Student*)it->data;
    ASSERT_TRUE(strcmp(stu->id, "1001") == 0);
    ASSERT_TRUE(strcmp(stu->name, "����") == 0);
    ASSERT_TRUE(stu->gpa == 3.8f);
    ASSERT_TRUE(strcmp(stu->major, "�����") == 0);

    it = list_next(it);
    stu = (Student*)it->data;
    ASSERT_TRUE(strcmp(stu->id, "1002") == 0);
    ASSERT_TRUE(strcmp(stu->name, "����") == 0);
    ASSERT_TRUE(stu->gpa == 3.5f);
    ASSERT_TRUE(strcmp(stu->major, "��ѧ") == 0);

    // �ͷż��ص�����
    list_destroy(&loaded, (void (*)(void*))dao->free_student);

    return 1;
}

// ���Կ�������
int test_save_empty() {
    StudentDAO* dao = get_student_dao();
    LinkedList* list = list_create();
    ASSERT_TRUE(dao->save_all(list) == 0);
    list_destroy(&list, (void (*)(void*))dao->free_student);
    return 1;
}

// �����ļ�������ʱ����
int test_load_no_file() {
    // ��ɾ���ļ�
    remove("data/student_manage/students.dat");
    StudentDAO* dao = get_student_dao();
    LinkedList* list = dao->load_all();
    ASSERT_TRUE(list == NULL);
    return 1;
}

int main() {
    int total = 0, passed = 0;
    printf("==== student_dao ��Ԫ���� ====\n");

    total++; if (test_save_and_load()) { printf("[ͨ��] ���������\n"); passed++; }
    total++; if (test_save_empty()) { printf("[ͨ��] ��������\n"); passed++; }
    total++; if (test_load_no_file()) { printf("[ͨ��] �ļ�������ʱ����\n"); passed++; }

    printf("==== ͨ�� %d/%d ====\n", passed, total);
    return (passed == total) ? 0 : 1;
}