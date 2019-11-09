
// CalculatorDlg.h : header file
//

#pragma once


#include"QInt.h"
#include"Qfloat.h"


// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void Calculate();
	void DisplayQFloat(CString x);
	void DisplayQInt(CString x);
	bool CheckInput();
	afx_msg void OnBnClickedButtonDIV();
	afx_msg void OnBnClickedButtonMUL();
	afx_msg void OnBnClickedButtonEQUALS();
	afx_msg void OnBnClickedButtonAND();
	afx_msg void OnBnClickedButtonPLUS();
	afx_msg void OnBnClickedButtonMINUS();
	afx_msg void OnBnClickedButtonOR();
	afx_msg void OnBnClickedButtonXOR();
	afx_msg void OnBnClickedButtonNOT();
	afx_msg void OnBnClickedButtonLSH();
	afx_msg void OnBnClickedButtonRSH();
	afx_msg void OnBnClickedButtonROL();
	afx_msg void OnBnClickedButtonROR();
	afx_msg void OnBnClickedButtonHEX();
	afx_msg void OnBnClickedButtonDEC();
	afx_msg void OnBnClickedButtonBIN();
	afx_msg void OnBnClickedButtonQInt();
	afx_msg void OnBnClickedButtonQFloat();
	afx_msg void OnBnClickedButtonAC();
private:
	CString _x;
	CString _operand;
	bool _check = 0;
	char _operator = 'N';
	CString _res;
	int _base = 0;
	bool _mode = 0;
};
