#pragma once

typedef struct StudentInf{
	double	studentID;					// ѧ��
	wchar_t	name[5];					// ����
	wchar_t studentClass[20];			// �༶
	unsigned short mark_subject1;		// ��Ŀ1�ɼ�
	unsigned short mark_subject2;		// ��Ŀ2�ɼ�
	unsigned short mark_subject3;		// ��Ŀ3�ɼ�
} studentInf;