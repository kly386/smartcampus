#include <stdio.h>
#include <stdlib.h>
#include "core/list.h"
#include "core/common.h"

// �򵥶��Ժ�
#define ASSERT_TRUE(expr) \
    do { \
        if (!(expr)) { \
            printf("[ʧ��] %s:%d: %s\n", __FILE__, __LINE__, #expr); \
            return 0; \
        } \
    } while (0)

// int�����ͷź���
void free_int(void* data) {
    if (data) free(data);
}

// ����������������
int test_create_destroy() {
    LinkedList* list = list_create();
    ASSERT_TRUE(list != NULL);
    ASSERT_TRUE(list->head == NULL && list->tail == NULL && list->size == 0);
    list_destroy(&list, free_int);
    ASSERT_TRUE(list == NULL);
    return 1;
}

// �������Ԫ��
int test_append() {
    LinkedList* list = list_create();
    for (int i = 0; i < 5; ++i) {
        int* p = (int*)malloc(sizeof(int));
        *p = i * 10;
        ASSERT_TRUE(list_append(list, p) == SUCCESS);
    }
    ASSERT_TRUE(list->size == 5);

    // �����������
    int expected = 0;
    for (ListIterator it = list_begin(list); it != NULL; it = list_next(it)) {
        ASSERT_TRUE(*(int*)it->data == expected * 10);
        expected++;
    }

    list_destroy(&list, free_int);
    return 1;
}

// ���Կ�ָ��ͷǷ�����
int test_invalid_input() {
    ASSERT_TRUE(list_append(NULL, NULL) == ERR_INVALID_INPUT);
    LinkedList* list = list_create();
    ASSERT_TRUE(list_append(list, NULL) == ERR_INVALID_INPUT);
    list_destroy(&list, free_int);
    return 1;
}

// ���Ե���������
int test_iterator() {
    LinkedList* list = list_create();
    int sum = 0;
    for (int i = 1; i <= 3; ++i) {
        int* p = (int*)malloc(sizeof(int));
        *p = i;
        list_append(list, p);
    }
    for (ListIterator it = list_begin(list); it != NULL; it = list_next(it)) {
        sum += *(int*)it->data;
    }
    ASSERT_TRUE(sum == 6); // 1+2+3
    list_destroy(&list, free_int);
    return 1;
}

int main() {
    int total = 0, passed = 0;
    printf("==== list.c ��Ԫ���� ====\n");
    total++; if (test_create_destroy()) { printf("[ͨ��] ����������\n"); passed++; }
    total++; if (test_append()) { printf("[ͨ��] ���Ԫ��\n"); passed++; }
    total++; if (test_invalid_input()) { printf("[ͨ��] �Ƿ�����\n"); passed++; }
    total++; if (test_iterator()) { printf("[ͨ��] ����������\n"); passed++; }
    printf("==== ͨ�� %d/%d ====\n", passed, total);
    return (passed == total) ? 0 : 1;
	/*printf("LinkedList��СΪ���٣�%zu\n", sizeof(LinkedList));    */
	//return 0; // ����0��ʾ����ͨ��  
}