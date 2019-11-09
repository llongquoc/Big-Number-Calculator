
// CalculatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
	, _x(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RES, _x);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDIV)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonMUL)
	ON_BN_CLICKED(IDC_BUTTON_EQUALS, &CCalculatorDlg::OnBnClickedButtonEQUALS)
	ON_BN_CLICKED(IDC_BUTTON_AND, &CCalculatorDlg::OnBnClickedButtonAND)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPLUS)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMINUS)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CCalculatorDlg::OnBnClickedButtonOR)
	ON_BN_CLICKED(IDC_BUTTON_XOR, &CCalculatorDlg::OnBnClickedButtonXOR)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CCalculatorDlg::OnBnClickedButtonNOT)
	ON_BN_CLICKED(IDC_BUTTON_LSH, &CCalculatorDlg::OnBnClickedButtonLSH)
	ON_BN_CLICKED(IDC_BUTTON_RSH, &CCalculatorDlg::OnBnClickedButtonRSH)
	ON_BN_CLICKED(IDC_BUTTON_ROL, &CCalculatorDlg::OnBnClickedButtonROL)
	ON_BN_CLICKED(IDC_BUTTON_ROR, &CCalculatorDlg::OnBnClickedButtonROR)
	ON_BN_CLICKED(IDC_BUTTON_HEX, &CCalculatorDlg::OnBnClickedButtonHEX)
	ON_BN_CLICKED(IDC_BUTTON_DEC, &CCalculatorDlg::OnBnClickedButtonDEC)
	ON_BN_CLICKED(IDC_BUTTON_BIN, &CCalculatorDlg::OnBnClickedButtonBIN)
	ON_BN_CLICKED(IDC_BUTTON_QInt, &CCalculatorDlg::OnBnClickedButtonQInt)
	ON_BN_CLICKED(IDC_BUTTON_QFloat, &CCalculatorDlg::OnBnClickedButtonQFloat)
	ON_BN_CLICKED(IDC_BUTTON_AC, &CCalculatorDlg::OnBnClickedButtonAC)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::DisplayQFloat(CString x)
{
	string s(CW2A(x.GetString()));
	Qfloat temp;
	if (_base == 0)
	{
		CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
		dec->SetWindowText(x);
		if (s != ovl && s != udl && s != NaN && s != inf)
		{
			temp.scanQfloat(s);
			s = temp.decToBin();
		}
		CString res(s.c_str(), s.length());
		CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
		bin->SetWindowText(res);
	}
	else
	{
		CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
		bin->SetWindowText(x);
		if (s != ovl && s != udl && s != NaN && s != inf)
		{
			temp.binToDec(s);
			s = temp.printQfloat();
		}
		CString res(s.c_str(), s.length());
		CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
		dec->SetWindowText(res);
	}
}

void CCalculatorDlg::DisplayQInt(CString x)
{
	string s(CW2A(x.GetString()));
	QInt temp;
	if (_base == 0)
	{
		CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
		dec->SetWindowText(x);
		temp.Scan(10, s);
		string toBin = temp.ToBin();
		CString resBin(toBin.c_str(), toBin.length());
		CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
		bin->SetWindowText(resBin);
		string toHex = temp.ToHex();
		CString resHex(toHex.c_str(), toHex.length());
		CEdit *hex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
		hex->SetWindowText(resHex);
	}
	else
		if (_base == 1)
		{
			CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
			bin->SetWindowText(x);
			temp.Scan(2, s);
			string toDec = temp.ToDec();
			CString resDec(toDec.c_str(), toDec.length());
			CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
			dec->SetWindowText(resDec);
			string toHex = temp.ToHex();
			CString resHex(toHex.c_str(), toHex.length());
			CEdit *hex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
			hex->SetWindowText(resHex);
		}
		else
		{
			CEdit *hex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
			hex->SetWindowText(x);
			temp.Scan(16, s);
			string toBin = temp.ToBin();
			CString resBin(toBin.c_str(), toBin.length());
			CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
			bin->SetWindowText(resBin);
			string toDec = temp.ToDec();
			CString resDec(toDec.c_str(), toDec.length());
			CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
			dec->SetWindowText(resDec);
		}
}

void CCalculatorDlg::Calculate()
{
	if (!_check)
	{
		_operand = _x;
		_check = 1;
	}
	else
	{
		string s1(CW2A(_operand.GetString()));
		string s2(CW2A(_x.GetString()));
		if (_mode)
		{
			Qfloat temp1, temp2;
			if (_base == 0)
			{
				temp1.scanQfloat(s1);
				temp2.scanQfloat(s2);
			}
			else
			{
				temp1.binToDec(s1);
				temp2.binToDec(s2);
			}
			string _compute;
			switch (_operator)
			{
			case '+':
			{
				_compute = temp1 + temp2;
				break;
			}
			case '-':
			{
				_compute = temp1 - temp2;
				break;
			}
			case 'x':
			{
				_compute = temp1 * temp2;
				break;
			}
			case '/':
			{
				_compute = temp1 / temp2;
				break;
			}
			}
			if (_base == 0)
			{
				if (_compute != ovl && _compute != udl && _compute != NaN && _compute != inf)
				{
					temp1.binToDec(_compute);
					_compute = temp1.printQfloat();
				}
			}
			CString res(_compute.c_str(), _compute.length());
			_res = res;
		}
		else
		{
			QInt temp1, temp2;
			if (_base == 0)
			{
				temp1.Scan(10, s1);
				temp2.Scan(10, s2);
			}
			else
				if (_base == 1)
				{
					temp1.Scan(2, s1);
					temp2.Scan(2, s2);
				}
				else
				{
					temp1.Scan(16, s1);
					temp2.Scan(16, s2);
				}
			QInt _compute;
			switch (_operator)
			{
			case '+':
			{
				_compute = temp1 + temp2;
				break;
			}
			case '-':
			{
				_compute = temp1 - temp2;
				break;
			}
			case 'x':
			{
				_compute = temp1 * temp2;
				break;
			}
			case '/':
			{
				_compute = temp1 / temp2;
				break;
			}
			case '&':
			{
				_compute = temp1 & temp2;
				break;
			}
			case '|':
			{
				_compute = temp1 | temp2;
				break;
			}
			case '^':
			{
				_compute = temp1 ^ temp2;
				break;
			}
			case '<':
			{
				_compute = temp1 << temp2;
				break;
			}
			case '>':
			{
				_compute = temp1 >> temp2;
				break;
			}
			case 'L':
			{
				_compute = temp1.rol(temp2);
				break;
			}
			case 'R':
			{
				_compute = temp1.ror(temp2);
				break;
			}
			}
		string tmp;
		if (_base == 0)
			tmp = _compute.ToDec();
		else
			if (_base == 1)
				tmp = _compute.ToBin();
			else
				tmp = _compute.ToHex();
		CString res(tmp.c_str(), tmp.length());
		_res = res;
		}
		_operand = _res;
	}
}

bool CCalculatorDlg::CheckInput()
{
	string s(CW2A(_x.GetString()));
	bool checkDot = 0;
	bool checkS0 = 0;
	if (s == "")
		return 0;
	if (_base == 0)
		for (int i = 0; i < s.size(); i++)
		{
			if (_mode && s[i] == '.')
				if (!checkDot)
				{
					checkDot = 1;
					continue;
				}
				else
					return 0;
			if ((s[0] == '+' || s[0] == '-') && checkS0 == 0)
			{
				checkS0 = 1;
				continue;
			}
			if (!(s[i] >= '0' && s[i] <= '9'))
				return 0;
		}
	else
		if (_base == 1)
			for (int i = 0; i < s.size(); i++)
			{
				if ((s[0] == '+' || s[0] == '-') && checkS0 == 0)
				{
					checkS0 = 1;
					continue;
				}
				if (!(s[i] == '0' || s[i] == '1'))
					return 0;
			}
		else
			if (_base == 2)
				for (int i = 0; i < s.size(); i++)
				{
					if ((s[0] == '+' || s[0] == '-') && checkS0 == 0)
					{
						checkS0 = 1;
						continue;
					}
					if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'A' && s[i] <= 'F')))
						return 0;
				}
	return 1;
}

void CCalculatorDlg::OnBnClickedButtonDIV()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '/';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonMUL()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = 'x';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonEQUALS()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_operator != 'N')
		Calculate();
	else
		_res = _x;
	_operator = 'N';
	if (_mode)
		DisplayQFloat(_res);
	else
		DisplayQInt(_res);
	_check = 0;
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(_res);
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonAND()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '&';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonPLUS()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '+';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonMINUS()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '-';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonOR()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '|';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonXOR()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '^';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonNOT()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	string s(CW2A(_x.GetString()));
	QInt temp;
	if (_base == 0)
		temp.Scan(10, s);
	else
		if (_base == 1)
			temp.Scan(2, s);
		else
			temp.Scan(16, s);
	QInt _compute = ~temp;
	if (_base == 0)
		s = _compute.ToDec();
	else
		if (_base == 1)
			s = _compute.ToBin();
		else
			s = _compute.ToHex();
	CString res(s.c_str(), s.length());
	_res = res;
	_operator = '~';
	DisplayQInt(_res);
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(_res);
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonLSH()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '<';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonRSH()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = '>';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonROL()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = 'L';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonROR()
{
	GetDlgItemText(IDC_EDIT_RES, _x);
	if (!CheckInput())
	{
		AfxMessageBox(L"Nhập không hợp lệ, mời nhập lại!");
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
		tmp->SetWindowText(L"");
		tmp->SetFocus();
		tmp->SetSel(-1);
		return;
	}
	if (_mode)
		DisplayQFloat(_x);
	else
		DisplayQInt(_x);
	Calculate();
	_operator = 'R';
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonHEX()
{
	_base = 2;
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonDEC()
{
	_base = 0;
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}


void CCalculatorDlg::OnBnClickedButtonBIN()
{
	_base = 1;
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}

void CCalculatorDlg::OnBnClickedButtonQInt()
{
	if (_mode)
	{
		_mode = 0;
		CEdit *reshex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
		reshex->EnableWindow(true);
		CButton *hex = (CButton*)GetDlgItem(IDC_BUTTON_HEX);
		hex->EnableWindow(true);
		CButton *and = (CButton*)GetDlgItem(IDC_BUTTON_AND);
		and->EnableWindow(true);
		CButton * or = (CButton*)GetDlgItem(IDC_BUTTON_OR);
		or ->EnableWindow(true);
		CButton *xor = (CButton*)GetDlgItem(IDC_BUTTON_XOR);
		xor->EnableWindow(true);
		CButton * not = (CButton*)GetDlgItem(IDC_BUTTON_NOT);
		not->EnableWindow(true);
		CButton *lsh = (CButton*)GetDlgItem(IDC_BUTTON_LSH);
		lsh->EnableWindow(true);
		CButton *rsh = (CButton*)GetDlgItem(IDC_BUTTON_RSH);
		rsh->EnableWindow(true);
		CButton *rol = (CButton*)GetDlgItem(IDC_BUTTON_ROL);
		rol->EnableWindow(true);
		CButton *ror = (CButton*)GetDlgItem(IDC_BUTTON_ROR);
		ror->EnableWindow(true);
	}
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}

void CCalculatorDlg::OnBnClickedButtonQFloat()
{
	if (!_mode)
	{
		CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
		tmp->SetWindowText(L"");
		_mode = 1;
		CEdit *reshex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
		reshex->EnableWindow(false);
		CButton *hex = (CButton*)GetDlgItem(IDC_BUTTON_HEX);
		hex->EnableWindow(false);
		CButton *and = (CButton*)GetDlgItem(IDC_BUTTON_AND);
		and->EnableWindow(false);
		CButton *or = (CButton*)GetDlgItem(IDC_BUTTON_OR);
		or->EnableWindow(false);
		CButton *xor = (CButton*)GetDlgItem(IDC_BUTTON_XOR);
		xor->EnableWindow(false);
		CButton *not = (CButton*)GetDlgItem(IDC_BUTTON_NOT);
		not->EnableWindow(false);
		CButton *lsh = (CButton*)GetDlgItem(IDC_BUTTON_LSH);
		lsh->EnableWindow(false);
		CButton *rsh = (CButton*)GetDlgItem(IDC_BUTTON_RSH);
		rsh->EnableWindow(false);
		CButton *rol = (CButton*)GetDlgItem(IDC_BUTTON_ROL);
		rol->EnableWindow(false);
		CButton *ror = (CButton*)GetDlgItem(IDC_BUTTON_ROR);
		ror->EnableWindow(false);
		if (_base == 2)
			_base = 0;
	}
	CEdit *tmp = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	tmp->SetWindowText(L"");
	tmp->SetFocus();
	tmp->SetSel(-1);
}

void CCalculatorDlg::OnBnClickedButtonAC()
{
	CEdit *res = (CEdit*)GetDlgItem(IDC_EDIT_RES);
	res->SetWindowText(L"");
	res->SetFocus();
	res->SetSel(-1);
	CEdit *dec = (CEdit*)GetDlgItem(IDC_EDIT_RESDEC);
	dec->SetWindowText(L"");
	CEdit *bin = (CEdit*)GetDlgItem(IDC_EDIT_RESBIN);
	bin->SetWindowText(L"");
	if (!_mode)
	{
		CEdit *hex = (CEdit*)GetDlgItem(IDC_EDIT_RESHEX);
		hex->SetWindowText(L"");
	}
}