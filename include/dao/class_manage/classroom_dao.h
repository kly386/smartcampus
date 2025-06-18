#pragma once
// dao/course_schedule/classroom_dao.h
#pragma once
#ifndef CLASSROOM_DAO_H
#define CLASSROOM_DAO_H

#include "../../core/list.h"
#include "../../core/course_schedule.h"

// 教室数据访问对象结构体
typedef struct {
    /**
     * @brief 从文件加载所有教室数据到链表
     * @return 包含所有教室的链表指针
     */
    LinkedList* (*load_all)();

    /**
     * @brief 保存所有教室数据到文件
     * @param list 包含教室数据的链表
     * @return 操作结果错误码
     */
    ErrorCode(*save_all)(LinkedList* list);

    /**
     * @brief 释放教室内存
     * @param classroom 要释放的教室指针
     */
    void (*free_classroom)(Classroom* classroom);

    /**
     * @brief 根据ID查找教室
     * @param id 教室ID
     * @return 找到的教室指针，未找到返回NULL
     */
    Classroom* (*get_by_id)(int id);
} ClassroomDAO;

/**
 * @brief 获取教室DAO单例
 * @return ClassroomDAO实例指针
 */
ClassroomDAO* get_classroom_dao();

#endif // CLASSROOM_DAO_H