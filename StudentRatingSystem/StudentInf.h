#pragma once

// ����ʹ�� C++ ������������Խ��и��õķ�װ����Ϊ��������Ŀ��ʹ���˽ṹ��

typedef struct StudentInf{
	double	studentID;					// ѧ��
	wchar_t	name[5];					// ����
	wchar_t studentClass[20];			// �༶
	double mark_subject1;		// ��Ŀ1�ɼ�
	double mark_subject2;		// ��Ŀ2�ɼ�
	double mark_subject3;		// ��Ŀ3�ɼ�
	double mark_total;			// �ܳɼ�
	char hasAward = -1;
} studentInf;