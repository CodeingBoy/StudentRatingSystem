#include "stdafx.h"
#include "MyListCtrlExt.h"


CMyListCtrlExt::CMyListCtrlExt()
{
}


CMyListCtrlExt::~CMyListCtrlExt()
{
}

BOOL CMyListCtrlExt::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView)
	{
		int nItem = pNMListView->iItem, nSubItem = pNMListView->iSubItem;

		if (nItem == GetItemCount() - 2) {
			// 双击了添加的一行
			InsertItem(GetItemCount() - 2, _T("")); // 在+行之上新建空行

		}
	}

	return CListCtrlExt::OnNMDblclk(pNMHDR, pResult);
}

BEGIN_MESSAGE_MAP(CMyListCtrlExt, CListCtrlExt)
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMyListCtrlExt::OnLButtonDown(UINT nFlags, CPoint point)
{
	HideEditor(); // 隐藏编辑器

	CListCtrlExt::OnLButtonDown(nFlags, point);
}
