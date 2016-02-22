#pragma once

typedef struct StudentInf{
	double	studentID;					// 学号
	wchar_t	name[5];					// 姓名
	wchar_t studentClass[20];			// 班级
	float mark_subject1;		// 科目1成绩
	float mark_subject2;		// 科目2成绩
	float mark_subject3;		// 科目3成绩
	float mark_total;			// 总成绩
	byte hasAward = 0;
} studentInf;