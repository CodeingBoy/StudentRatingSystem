#pragma once

// 可以使用 C++ 的面向对象特性进行更好的封装，但为了尊重题目，使用了结构体

typedef struct StudentInf{
	double	studentID;					// 学号
	wchar_t	name[5];					// 姓名
	wchar_t studentClass[20];			// 班级
	double mark_subject1;		// 科目1成绩
	double mark_subject2;		// 科目2成绩
	double mark_subject3;		// 科目3成绩
	double mark_total;			// 总成绩
	char hasAward = -1;
} studentInf;