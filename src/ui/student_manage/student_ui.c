#include "ui/student_manage/student_ui.h"
#include <stdio.h>
#include <stdlib.h>
#include "core/common.h"
#include "service/student_manage/student_service.h"


//��ʾѧ��������ϵͳ����ҳ��
void show_student_menu() {
    printf("\n===== ѧ����Ϣ����ϵͳ =====\n");
    printf("1. ���ѧ��\n");
    printf("2. ɾ��ѧ��\n");
    printf("3. �޸�ѧ����Ϣ\n");
    printf("4. ��ѯѧ��\n");
    printf("5. ��ʾ����ѧ��\n");
    printf("6. ��רҵͳ��GPA\n");
    printf("0. �������˵�\n");
    printf("===========================\n");
    printf("��ѡ�����: ");
}

// ���ѧ��ҳ��
void add_student_ui() {
    char id[10], name[20], major[30];
    float gpa;

    //��ӡ����+��Ϣ¼��
    printf("\n------ ���ѧ�� ------\n");
    printf("ѧ�ţ�"); scanf_s("%9s", id, (unsigned)_countof(id));
    printf("������"); scanf_s("%19s", name, (unsigned)_countof(name));
    printf("GPA��"); scanf_s("%f", &gpa);
    printf("רҵ��"); scanf_s("%29s", major, (unsigned)_countof(major));


    //���¼����ѧ������ӵ���ѧ�������С������һ�ȡ��ӳɹ�������Ϣ
    //����student_service�е�add_student��ʵ�ָò���
    ErrorCode error = get_student_service()->add_student(id, name, gpa, major);
    printf("%s\n", error_message(error));
}

// ɾ��ѧ��ҳ��--����ID
void delete_student_ui() {
    char id[10];
    printf("\n------ ɾ��ѧ�� ------\n");
    printf("������Ҫɾ����ѧ��ѧ�ţ�");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // ������뻺����

    // �Ȳ�ѯȷ��ѧ������
    Student* stu = get_student_service()->get_student(id);
    if (stu == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
        system("pause");
        return;
    }

    // ��ʾѧ����Ϣ��ȷ��
    printf("\n�ҵ�����ѧ��:\n");
    printf("ѧ�ţ�%s\n", stu->id);
    printf("������%s\n", stu->name);
    printf("GPA��%.2f\n", stu->gpa);
    printf("רҵ��%s\n\n", stu->major);

    // ȷ��ɾ��
    printf("ȷ��ɾ����ѧ����(Y/N): ");
    char confirm;
    scanf_s("%c", &confirm, 1);
    while (getchar() != '\n');

    if (confirm == 'Y' || confirm == 'y') {
        ErrorCode error = get_student_service()->delete_student(id);
        printf("\n%s\n", error_message(error));
    }
    else {
        printf("\n��ȡ��ɾ������\n");
    }
    system("pause");
}

// ��ѯѧ��ҳ��--����ID
void query_student_ui() {
    char id[10];
    printf("\n------ ��ѯѧ�� ------\n");
    printf("������ѧ�ţ�");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // ������뻺����

    // ����student_service��get_studentʵ�ָò���
    Student* stu = get_student_service()->get_student(id);

    // ��ӡѧ����Ϣ
    if (stu == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
    }
    else {
        printf("\n===== ѧ����ϸ��Ϣ =====\n");
        printf("ѧ�ţ�%s\n", stu->id);
        printf("������%s\n", stu->name);
        printf("GPA��%.2f\n", stu->gpa);
        printf("רҵ��%s\n", stu->major);
        printf("========================\n");
    }
    system("pause"); // ��ͣ�ȴ��û��鿴
}

// �޸�ѧ����Ϣ
void update_student_ui() {
    char id[10], name[20], major[30];
    float gpa;

    printf("\n------ �޸�ѧ����Ϣ ------\n");
    printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
    scanf_s("%9s", id, (unsigned)_countof(id));
    while (getchar() != '\n'); // ������뻺����

    // �Ȼ�ȡѧ����Ϣ
    Student* stu = get_student_service()->get_student(id);
    if (stu == NULL) {
        printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����\n", id);
        system("pause");
        return;
    }

    // ��ʾ��ǰ��Ϣ����ȡ����Ϣ
    printf("\n��ǰѧ����Ϣ:\n");
    printf("ѧ�ţ�%s\n", stu->id);
    printf("������%s\n", stu->name);
    printf("GPA��%.2f\n", stu->gpa);
    printf("רҵ��%s\n\n", stu->major);

    printf("�����������������ձ��ֲ��䣩��");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; // �Ƴ����з�
    if (strlen(name) == 0) {
        strcpy(name, stu->name); // ����ԭֵ
    }

    printf("��������GPA������0���ֲ��䣩��");
    char gpa_str[20];
    fgets(gpa_str, sizeof(gpa_str), stdin);
    if (sscanf_s(gpa_str, "%f", &gpa) != 1 || gpa == 0) {
        gpa = stu->gpa; // ����ԭֵ
    }

    printf("��������רҵ�����ձ��ֲ��䣩��");
    fgets(major, sizeof(major), stdin);
    major[strcspn(major, "\n")] = '\0';
    if (strlen(major) == 0) {
        strcpy(major, stu->major); // ����ԭֵ
    }

    // ����ѧ����Ϣ
    ErrorCode error = get_student_service()->update_student(id, name, gpa, major);
    printf("\n%s\n", error_message(error));
    system("pause");
}


// �г�����ѧ����Ϣ
void list_all_student_ui() {
    printf("\n------ ѧ���б� ------\n");

    // ��ȡѧ������
    LinkedList* list = get_student_service()->get_all_students();
    if (list == NULL || list->size == 0) {
        printf("����ѧ�����ݣ�\n");
        system("pause");
        return;
    }

    // ��ӡ��ͷ
    printf("%-10s %-20s %-8s %-30s\n", "ѧ��", "����", "GPA", "רҵ");
    printf("------------------------------------------------------------\n");

    // ���������ӡÿ��ѧ����Ϣ
    ListIterator it = list_begin(list);
    int count = 0;
    while (it != NULL) {
        Student* stu = (Student*)it->data;
        if (stu != NULL) {
            printf("%-10s %-20s %-8.2f %-30s\n",
                stu->id, stu->name, stu->gpa, stu->major);
            count++;
        }
        it = list_next(it);
    }

    printf("\n�� %d ��ѧ��\n", count);
    system("pause");
}

// ��רҵͳ����Ϣ

// �����û����루1.��� 2.ɾ��...)
// �����û�����
void handle_student_input() {
    int choice;
    while (1) {
        system("cls"); // ����
        show_student_menu();

        // �����û�����
        if (scanf_s("%d", &choice) != 1) {
            printf("������Ч��������һ������.\n");
            while (getchar() != '\n');
            system("pause");
            continue;
        }
        while (getchar() != '\n'); // ������뻺����

        switch (choice) {
        case 1:
            add_student_ui();
            break;
        case 2:
            delete_student_ui();
            break;
        case 3:
            update_student_ui();
            break;
        case 4:
            query_student_ui();
            break;
        case 5:
            list_all_student_ui();
            break;
        case 6:
            printf("��רҵͳ��GPA-��ʵ��\n");
            system("pause");
            break;
        case 0:
            return; // ����������
        default:
            printf("��Ч���룬������ѡ��\n");
            system("pause");
        }
    }
}