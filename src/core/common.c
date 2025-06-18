#include "core/common.h"

// ��ȫ�ڴ����
// ���Է���ָ����С���ڴ�;�������ʧ�ܣ���ӡ������Ϣ���˳�����;���ط�����ڴ�ָ��
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "[ERROR] �ڴ����ʧ��\n");
        exit(ERR_MEMORY_ALLOC);
    }
    return ptr;
}

// ��ȫ�ͷ��ڴ�
// ���ָ���Ƿ���Ч����NULL��;�ͷ��ڴ�;��ָ����ΪNULL����������ָ��
void safe_free(void** ptr) {
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}

// ������Ϣ����:ͨ��switch��佫������ӳ��Ϊ�ɶ��ַ���
const char* error_message(ErrorCode err) {
    switch (err) {
    case SUCCESS:          return "�����ɹ�";
    case ERR_MEMORY_ALLOC: return "�ڴ����ʧ��";
    case ERR_FILE_OPEN:    return "�ļ���ʧ��";
    case ERR_FILE_WRITE:   return "�ļ�д��ʧ��";
    case ERR_FILE_READ:    return "�ļ���ȡʧ��";
    case ERR_DUPLICATE:    return "��¼�Ѵ���";
    case ERR_NOT_FOUND:    return "��¼������";
    case ERR_INVALID_INPUT:return "������Ч";
    default:               return "δ֪����";
    }
}