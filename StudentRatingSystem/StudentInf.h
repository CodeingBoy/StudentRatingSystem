#pragma once

typedef struct StudentInf{
	double	studentID;					// ѧ��
	wchar_t	name[5];					// ����
	wchar_t studentClass[20];			// �༶
	float mark_subject1;		// ��Ŀ1�ɼ�
	float mark_subject2;		// ��Ŀ2�ɼ�
	float mark_subject3;		// ��Ŀ3�ɼ�
	float mark_total;			// �ܳɼ�
	byte hasAward = 0;
} studentInf;