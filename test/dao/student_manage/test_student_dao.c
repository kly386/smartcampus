//#include<stdio.h>  
//#include<stdlib.h>  
//
//// 加载数据方法1  
//static int* load_data_methed1() {  
//    int* data = (int*)malloc(3 * sizeof(int)); // 分配3个整数的内存  
//    data[0] = 100;  
//    data[1] = 200;  
//    data[z2] = 300;  
//    return data; // 返回分配的内存地址  
//}  
//int* load_data_methed2() {
//    int* data = (int*)malloc(34* sizeof(int)); // 分配3个整数的内存  
//    data[0] = 10;
//    data[1] = 20;
//    data[2] = 30;
//	data[3] = 40;
//    return data; // 返回分配的内存地址  
//}
//int main() {  
//	int* (*load_all)();//声明函数指针
//	load_all = load_data_methed2; // 指向load_data_methed1函数，函数名代表函数地址
//
//	int* user_data = load_all(); // 调用函数指针，获取数据
//    for(int i = 0; i < 4; i++) {  
//        printf("%d\n", user_data[i]); // 输出数据  
//	}
//	printf("\n");   
//    return 0;  
//}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dao/student_manage/student_dao.h"
#include "core/list.h"

// 简单断言宏
#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            printf("[失败] %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return 0; \
        } \
    } while (0)

// 测试保存和加载学生信息
int test_save_and_load() {
    StudentDAO* dao = get_student_dao();
    LinkedList* list = list_create();

    // 构造测试数据
    Student* s1 = (Student*)malloc(sizeof(Student));
    strcpy_s(s1->id, sizeof(s1->id), "1001");
    strcpy_s(s1->name, sizeof(s1->name), "张三");
    s1->gpa = 3.8f;
    strcpy_s(s1->major, sizeof(s1->major), "计算机");

    Student* s2 = (Student*)malloc(sizeof(Student));
    strcpy_s(s2->id, sizeof(s2->id), "1002");
    strcpy_s(s2->name, sizeof(s2->name), "李四");
    s2->gpa = 3.5f;
    strcpy_s(s2->major, sizeof(s2->major), "数学");

    list_append(list, s1);
    list_append(list, s2);

    // 保存到文件
    ASSERT_TRUE(dao->save_all(list) == 0);

    // 释放原链表
    list_destroy(&list, (void (*)(void*))dao->free_student);

    // 从文件加载
    LinkedList* loaded = dao->load_all();
    ASSERT_TRUE(loaded != NULL);
    ASSERT_TRUE(loaded->size == 2);

    // 检查数据一致性
    ListIterator it = list_begin(loaded);
    Student* stu = (Student*)it->data;
    ASSERT_TRUE(strcmp(stu->id, "1001") == 0);
    ASSERT_TRUE(strcmp(stu->name, "张三") == 0);
    ASSERT_TRUE(stu->gpa == 3.8f);
    ASSERT_TRUE(strcmp(stu->major, "计算机") == 0);

    it = list_next(it);
    stu = (Student*)it->data;
    ASSERT_TRUE(strcmp(stu->id, "1002") == 0);
    ASSERT_TRUE(strcmp(stu->name, "李四") == 0);
    ASSERT_TRUE(stu->gpa == 3.5f);
    ASSERT_TRUE(strcmp(stu->major, "数学") == 0);

    // 释放加载的链表
    list_destroy(&loaded, (void (*)(void*))dao->free_student);

    return 1;
}

// 测试空链表保存
int test_save_empty() {
    StudentDAO* dao = get_student_dao();
    LinkedList* list = list_create();
    ASSERT_TRUE(dao->save_all(list) == 0);
    list_destroy(&list, (void (*)(void*))dao->free_student);
    return 1;
}

// 测试文件不存在时加载
int test_load_no_file() {
    // 先删除文件
    remove("data/student_manage/students.dat");
    StudentDAO* dao = get_student_dao();
    LinkedList* list = dao->load_all();
    ASSERT_TRUE(list == NULL);
    return 1;
}

int main() {
    int total = 0, passed = 0;
    printf("==== student_dao 单元测试 ====\n");

    total++; if (test_save_and_load()) { printf("[通过] 保存与加载\n"); passed++; }
    total++; if (test_save_empty()) { printf("[通过] 空链表保存\n"); passed++; }
    total++; if (test_load_no_file()) { printf("[通过] 文件不存在时加载\n"); passed++; }

    printf("==== 通过 %d/%d ====\n", passed, total);
    return (passed == total) ? 0 : 1;
}