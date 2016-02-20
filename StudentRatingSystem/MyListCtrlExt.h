#pragma once
#include "ListCtrlExt.h"
class CMyListCtrlExt :
	public CListCtrlExt
{
public:
	CMyListCtrlExt();
	~CMyListCtrlExt();
	BOOL OnNMDblclk(NMHDR * pNMHDR, LRESULT * pResult);
};

