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
			// ˫������ӵ�һ��
			InsertItem(GetItemCount() - 2, _T("")); // ��+��֮���½�����

		}
	}

	return CListCtrlExt::OnNMDblclk(pNMHDR, pResult);
}

BEGIN_MESSAGE_MAP(CMyListCtrlExt, CListCtrlExt)
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMyListCtrlExt::OnLButtonDown(UINT nFlags, CPoint point)
{
	HideEditor(); // ���ر༭��

	CListCtrlExt::OnLButtonDown(nFlags, point);
}
