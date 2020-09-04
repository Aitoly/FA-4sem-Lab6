#pragma once

class TimeClass
{
public:
	HWND hWEditDate, hWEditMounth, hWEditYear, hWEditHours, hWEditMin, hWEditSec, hWEditMSec
		, hEditTimerSec, hEditTimerMSec;
	int edit_sec, edit_msec;

	TimeClass();
	~TimeClass();
	
	void GetNowTime();
	void SetTimeForWindow();
	bool GetTimeFromWindow();
	void PlusTime();

private:
	time_t now;
	tm ltm;
	char buff[256];
	WCHAR buffW[256];
	SYSTEMTIME mainData;

	void ConvertToWChar();
	void ConvertToChar();
	void add(double seconds);
};

