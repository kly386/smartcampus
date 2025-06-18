#pragma once
#ifndef COMMON_H
#define COMMON_H
// ��ֹͷ�ļ����ظ�������ʹ�ú궨�屣����ȷ��ͷ�ļ�����ֻ������һ��

#include <stdlib.h> // �ṩ�ڴ������
#include <stdio.h>  // �ṩ�����������
#include <stdbool.h> // �ṩ��������֧��

// �ڴ氲ȫ����
void* safe_malloc(size_t size); // ��װ��׼malloc�������ڴ����ʧ�ܵļ��ʹ���,size_tΪ����Ӧϵͳ��С
void safe_free(void** ptr);    // ��װ��׼free����ֹ����ָ�룬�ͷź��Զ���NULL

// �����붨��
typedef enum {
    SUCCESS = 0,   // �����ɹ�
    ERR_MEMORY_ALLOC,  // �ڴ����ʧ��
    ERR_FILE_OPEN,     // �ļ���ʧ��
    ERR_FILE_WRITE,    // �ļ�д��ʧ��
    ERR_FILE_READ,    // �ļ���ȡ�Ǳ�
    ERR_DUPLICATE,    // �ظ������
    ERR_NOT_FOUND,    // δ�ҵ�����
    ERR_INVALID_INPUT // ��Ч�������
} ErrorCode;



// ������-�����뵽������Ϣ��ת��������������������ת��Ϊ�˿ɶ��Ĵ�������
const char* error_message(ErrorCode err);

#endif  // ����ͷ�ļ�������
