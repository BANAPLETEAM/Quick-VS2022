// NoticeDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "resource.h"
#include "SecurityLogDlg.h"


// CSecurityLogDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSecurityLogDlg, CMyDialog)
CSecurityLogDlg::CSecurityLogDlg(CWnd* pParent /*=NULL*/)
	: CMyDialog(CSecurityLogDlg::IDD, pParent)
{
}

CSecurityLogDlg::~CSecurityLogDlg()
{
}

void CSecurityLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BAR_STATIC, m_BarStatic);
}


BEGIN_MESSAGE_MAP(CSecurityLogDlg, CMyDialog)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// CSecurityLogDlg 메시지 처리기입니다.

BOOL CSecurityLogDlg::OnInitDialog()
{
	CMyDialog::OnInitDialog();

	CenterWindow(GetDesktopWindow());

	CImageList ImageList; 
	ImageList.Create(1,18,ILC_COLOR,1,1); 
	m_List.SetImageList(&ImageList,LVSIL_SMALL); 

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//LVS_EX_GRIDLINES
	m_List.InsertColumn(0,"날짜",LVCFMT_LEFT, 110);
	m_List.InsertColumn(1,"내용",LVCFMT_LEFT, 300);
	m_List.InsertColumn(2,"접수자회사",LVCFMT_LEFT, 80);
	m_List.InsertColumn(3,"접수자명",LVCFMT_LEFT, 90);
	m_List.InsertColumn(4,"PC번호",LVCFMT_LEFT, 60);
	m_List.InsertColumn(5,"디스크ID",LVCFMT_LEFT, 70);
	m_List.InsertColumn(6,"네트워크ID",LVCFMT_LEFT, 70);
	m_List.InsertColumn(7,"로그인시간",LVCFMT_LEFT, 80);
	m_List.InsertColumn(8,"호스트명",LVCFMT_LEFT, 70);

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CSecurityLogDlg::RefreshList()
{
	/*
	m_List.DeleteAllItems();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_security_log");
	pCmd.AddParameter(typeInt, typeInput, sizeof(int), m_ci.m_nCompanyCode);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		COleDateTime dtWrite;
		long nType, nStaffNo;
		CString strData1, strData2, strData3, strFormat;
		char buffer[20];
		COLOR_STRUCT *pcs = new COLOR_STRUCT;


		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nStaffNo", nStaffNo);
		pRs.GetFieldValue("sData1", strData1);
		pRs.GetFieldValue("sData2", strData2);
		pRs.GetFieldValue("sData3", strData3);
		pRs.GetFieldValue("dtWrite", dtWrite);

		strFormat = GetSecurityLog(nType, strData1, strData2, strData3);

		m_List.InsertItem(i, dtWrite.Format("%Y/%m/%d"));
		m_List.SetItemText(i, 1, dtWrite.Format("%H:%M"));
		m_List.SetItemText(i, 2, GetSecurityType(nType));
		m_List.SetItemText(i, 3, ltoa(nStaffNo, buffer, 10));
		m_List.SetItemText(i, 4, strFormat);
	
		pcs->crText = RGB(0,0,0);
		if(i % 2 == 0) 
			pcs->crBk = RGB(245, 245, 245);
		else 
			pcs->crBk = RGB(255, 255, 255);

		m_List.SetItemData(i, (DWORD_PTR)pcs); 
		pRs.MoveNext();
	}
	pRs.Close();
	*/
	m_List.DeleteAllItems();
	CMkRecordset pRs(m_pMkDb);
	CMkCommand pCmd(m_pMkDb, "select_security_log_1");
	pCmd.AddParameter(typeLong, typeInput, sizeof(int), LF->GetCurBranchInfo()->nCompanyCode);
	pCmd.AddParameter(typeBool, typeInput, sizeof(BOOL), LF->GetCurBranchInfo()->bIntegrated);
	if(!pRs.Execute(&pCmd)) return;

	for(int i = 0; i < pRs.GetRecordCount(); i++)
	{
		COleDateTime dtWrite;
		long nType, nStaffNo;
		CString strData1, strData2, strData3, strFormat;
		char buffer[20];
		COLOR_STRUCT *pcs = new COLOR_STRUCT;
		long nPCNum;
		CString strStaffInfo, strHddID;
		COleDateTime dtLoginTime;
		CString strMacAddress, strStaffCompanyInfo;
		CString strHostName;

		pRs.GetFieldValue("nType", nType);
		pRs.GetFieldValue("nStaffNo", nStaffNo);
		pRs.GetFieldValue("sData1", strData1);
		pRs.GetFieldValue("sData2", strData2);
		pRs.GetFieldValue("sData3", strData3);
		pRs.GetFieldValue("dtWrite", dtWrite);
		pRs.GetFieldValue("nPCNum", nPCNum);
		pRs.GetFieldValue("sStaffInfo", strStaffInfo);
		pRs.GetFieldValue("sHddID", strHddID);
		pRs.GetFieldValue("dtLoginTime", dtLoginTime);
		pRs.GetFieldValue("sMacAddress", strMacAddress);
		pRs.GetFieldValue("sStaffCompanyInfo", strStaffCompanyInfo);
		pRs.GetFieldValue("sHostName", strHostName);


		strFormat = GetSecurityLog(nType, strData1, strData2, strData3);

		m_List.InsertItem(i, dtWrite.Format("%Y/%m/%d %H:%M"));
		m_List.SetItemText(i, 1, strFormat);
		m_List.SetItemText(i, 2, strStaffCompanyInfo);
		m_List.SetItemText(i, 3, strStaffInfo);
		m_List.SetItemText(i, 4, ltoa(nPCNum, buffer, 10));
		m_List.SetItemText(i, 5, strHddID);
		m_List.SetItemText(i, 6, strMacAddress);
		m_List.SetItemText(i, 7, dtLoginTime.Format("%Y/%m/%d %H:%M"));
		m_List.SetItemText(i, 8, strHostName);

		pcs->crText = RGB(0,0,0);
		if(i % 2 == 0) 
			pcs->crBk = RGB(245, 245, 245);
		else 
			pcs->crBk = RGB(255, 255, 255);

		m_List.SetItemData(i, (DWORD_PTR)pcs); 
		pRs.MoveNext();
	}
	pRs.Close();
}

HBRUSH CSecurityLogDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CMyDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if(pWnd->GetDlgCtrlID() == IDC_BAR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);	
		return ::CreateSolidBrush(RGB(245,245,245));
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

CString CSecurityLogDlg::GetSecurityLog(long nType, CString strData1, CString strData2, CString strData3)
{

	//고정, 기정, 통계로 페이지가 나눠지면서 case 순서가 뒤죽박죽임..
	//중복되는 번호가 있는지 확인후 추가 해야함!!

	CString strFormat;

	switch(nType)
	{
	case 100:
		strFormat.Format("하루 지난 데이터 수정됨(접수번호: %s, 이전금액:%s, 새금액:%s)", strData1, strData2, strData3);
		break;
	case 101:
		strFormat.Format("접수화면에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 102:
		strFormat.Format("공동정산창[입출금내역]에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 103:
		strFormat.Format("접속리스트에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 104:
		strFormat.Format("기능페이지에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 105:
		strFormat.Format("녹취파일탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 106:
		strFormat.Format("미연결콜탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 201:
		strFormat.Format("고객탭[고객관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 202:
		strFormat.Format("고객탭[우수고객조회] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 203:
		strFormat.Format("고객탭[신규고객조회] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 204:
		strFormat.Format("고객탭[불량고객조회] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 205:
		strFormat.Format("고객탭[이용증감고객] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 206:
		strFormat.Format("고객탭[그룹관리_그룹] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 211:
		strFormat.Format("고객탭[휴면고객] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 212:
		strFormat.Format("고객탭[중복고객] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 213:
		strFormat.Format("고객탭[기간별조회] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 214:
		strFormat.Format("고객탭[불량고객조회2] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 215:
		strFormat.Format("고객탭[차단번호] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 301:
		strFormat.Format("고객정산탭[고객정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 351:
		strFormat.Format("고객정산탭[신용정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 302:
		strFormat.Format("기사정산탭[기사정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 303:
		strFormat.Format("기사정산탭[기사별건수] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	//case 306:
	//	strFormat.Format("정산탭[팀매출정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
	//	break;
	//case 308:
	//	strFormat.Format("정산탭[쿠폰정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
	//	break;
	case 310:
		strFormat.Format("고객정산탭[업체신용정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 312:
		strFormat.Format("기사정산탭[기사신용정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 314:
		strFormat.Format("고객정산탭[그룹정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 315:
		strFormat.Format("고객정산탭[그룹정산][출력] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 316:
		strFormat.Format("고객정산탭[그룹외오더] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;


	case 320:
		strFormat.Format("고객정산탭[마일리지] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 321:
		strFormat.Format("기사정산탭[기사일리지] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 322:
		strFormat.Format("기사정산탭[기사별건수(지입금)] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 323:
		strFormat.Format("고객정산탭[카드원천징수] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 324:
		strFormat.Format("고객정산탭[카드결제내역] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 325:
		strFormat.Format("기사정산탭[기사온라인출금] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 326:
		strFormat.Format("기사정산탭[기사출금요청] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 327:
		strFormat.Format("기사정산탭[단말기이력관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 328:
		strFormat.Format("기사정산탭[영업팀정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 329:
		strFormat.Format("기사정산탭[쿠폰정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 330:
		strFormat.Format("정산[현금영수증] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 331:
		strFormat.Format("정산[마일리지출금관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 401:
		strFormat.Format("직원탭[직원관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 402:  
		strFormat.Format("직원탭[기사관리(일부만적용됨)] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 406:
		strFormat.Format("직원탭[기사세부사항(일부만적용됨)] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 404:
		strFormat.Format("직원탭[서비스이용료] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 405:
		strFormat.Format("직원탭[출근관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 407:
		strFormat.Format("직원탭[삭제기사] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 501:
		strFormat.Format("입금탭[입금관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 502:
		strFormat.Format("입금탭[통장식로그] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 503:
		strFormat.Format("입금탭[통장식로그] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 504:
		strFormat.Format("입금탭[지입금관리] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 505:
		strFormat.Format("입금탭[최종정산 마감고지] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 506:
		strFormat.Format("입금탭[기사가상계좌할당] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 602:
		strFormat.Format("통계탭[금일콜수예측] 탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 603:
		strFormat.Format("통계탭[동분석] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 604:
		strFormat.Format("통계탭[접수자통계] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 605:
		strFormat.Format("통계탭[접수자통계_콜수] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 304:
		strFormat.Format("통계탭[일별건수] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 305:
		strFormat.Format("통계탭[지점간정산] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 306:
		strFormat.Format("통계탭[공유콜정산내역] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 313: 
		strFormat.Format("통계탭[공유콜] 에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 608:
		strFormat.Format("통계탭[SMS정산] 탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 609:
		strFormat.Format("통계탭[텔서버착신] 탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;
	case 610:
		strFormat.Format("통계탭[신규고객율] 탭에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 701:
		strFormat.Format("쿨카운트에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 801:
		strFormat.Format("쿨카운트에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	case 901:
		strFormat.Format("그룹정산[오더보기]에서 %s개의 데이터가 엑셀로 변환됨", strData1);
		break;

	//고정, 기정, 통계로 페이지가 나눠지면서 case 순서가 뒤죽박죽임..
		//중복되는 번호가 있는지 확인후 추가 해야함!!			
	}
	return strFormat;
}

CString CSecurityLogDlg::GetSecurityType(long nType)
{
	if(nType >= 100 && nType < 200)
		return "접수";
	else if(nType >= 200 && nType < 300)
		return "고객";

	return "기타";
}

void CSecurityLogDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//	if(!(pNMListView->uNewState & LVIS_SELECTED)) return;
	if(pNMListView->iItem < 0) return;

	MessageBox(m_List.GetItemText(pNMListView->iItem, 1), "보안로그", MB_ICONINFORMATION);
	*pResult = 0;
}
