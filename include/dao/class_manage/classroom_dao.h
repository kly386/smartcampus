#pragma once
// dao/course_schedule/classroom_dao.h
#pragma once
#ifndef CLASSROOM_DAO_H
#define CLASSROOM_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

// �������ݷ��ʶ���ṹ��
typedef struct {
    /**
     * @brief ���ļ��������н������ݵ�����
     * @return �������н��ҵ�����ָ��
     */
    LinkedList* (*load_all)();

    /**
     * @brief �������н������ݵ��ļ�
     * @param list �����������ݵ�����
     * @return �������������
     */
    ErrorCode(*save_all)(LinkedList* list);

    /**
     * @brief �ͷŽ����ڴ�
     * @param classroom Ҫ�ͷŵĽ���ָ��
     */
    void (*free_classroom)(Classroom* classroom);

    /**
     * @brief ����ID���ҽ���
     * @param id ����ID
     * @return �ҵ��Ľ���ָ�룬δ�ҵ�����NULL
     */
    Classroom* (*get_by_id)(int id);
} ClassroomDAO;

/**
 * @brief ��ȡ����DAO����
 * @return ClassroomDAOʵ��ָ��
 */
ClassroomDAO* get_classroom_dao();

#endif // CLASSROOM_DAO_H