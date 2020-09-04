#include <wtypes.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include "TimeClass.h"

TimeClass::TimeClass() : edit_sec(1), edit_msec(0)
{}

TimeClass::~TimeClass() {}

void TimeClass::GetNowTime()
{
    GetLocalTime(&mainData);
}

void TimeClass::SetTimeForWindow()
{
    _itoa_s(mainData.wDay, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wMonth, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditMounth, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wYear, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditYear, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wHour, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditHours, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wMinute, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditMin, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wSecond, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditSec, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(mainData.wMilliseconds, buff, 10);
    ConvertToWChar();
    SendMessage(hWEditMSec, WM_SETTEXT, NULL, (LPARAM)buffW);



    _itoa_s(edit_sec, buff, 10);
    ConvertToWChar();
    SendMessage(hEditTimerSec, WM_SETTEXT, NULL, (LPARAM)buffW);

    _itoa_s(edit_msec % 1000, buff, 10);
    ConvertToWChar();
    SendMessage(hEditTimerMSec, WM_SETTEXT, NULL, (LPARAM)buffW);
}

bool TimeClass::GetTimeFromWindow()
{
    SendMessage(hEditTimerSec, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    edit_sec = atoi(buff);
    if (edit_sec > 59)
    {
        edit_sec = 59;
        _itoa_s(edit_sec, buff, 10);
        ConvertToWChar();
        SendMessage(hEditTimerSec, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hEditTimerMSec, WM_GETTEXT, 5, (LPARAM)buffW);
    ConvertToChar();
    edit_msec = atoi(buff);
    if (edit_msec > 999)
    {
        edit_msec = 999;
        _itoa_s(edit_msec, buff, 10);
        ConvertToWChar();
        SendMessage(hEditTimerMSec, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    edit_msec += edit_sec * 1000;

    ////

    SendMessage(hWEditYear, WM_GETTEXT, 5, (LPARAM)buffW);
    ConvertToChar();
    mainData.wYear = atoi(buff);
    if (mainData.wYear < 1700)
    {
        mainData.wYear = 1700;
        _itoa_s(mainData.wYear, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditYear, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    if (mainData.wYear > 2056)
    {
        mainData.wYear = 2056;
        _itoa_s(mainData.wYear, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditYear, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hWEditMounth, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    mainData.wMonth = atoi(buff);
    if (mainData.wMonth > 12)
    {
        mainData.wMonth = 12;
        _itoa_s(mainData.wMonth, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditMounth, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    if (mainData.wMonth < 1)
    {
        mainData.wMonth = 1;
        _itoa_s(mainData.wMonth, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditMounth, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hWEditDate, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    mainData.wDay = atoi(buff);
    if (mainData.wDay < 1)
    {
        mainData.wDay = 1;
        _itoa_s(mainData.wDay, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    switch (mainData.wMonth)
    {
    case 1:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 2:
        if (mainData.wYear % 4 == 0 && mainData.wYear % 100 != 0)
        {
            if (mainData.wDay > 29)//високосный
            {
                mainData.wDay = 29;
                _itoa_s(mainData.wDay, buff, 10);
                ConvertToWChar();
                SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
            }
        }
        else
        {
            if (mainData.wYear % 400 == 0)
            {
                if (mainData.wDay > 29)//високосный
                {
                    mainData.wDay = 29;
                    _itoa_s(mainData.wDay, buff, 10);
                    ConvertToWChar();
                    SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
                }
            }
            else
            {
                if (mainData.wDay > 28)//не високосный
                {
                    mainData.wDay = 28;
                    _itoa_s(mainData.wDay, buff, 10);
                    ConvertToWChar();
                    SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
                }
            }
        }
        break;
    case 3:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 4:
        if (mainData.wDay > 30)
        {
            mainData.wDay = 30;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 5:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 6:
        if (mainData.wDay > 30)
        {
            mainData.wDay = 30;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 7:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 8:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 9:
        if (mainData.wDay > 30)
        {
            mainData.wDay = 30;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 10:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 11:
        if (mainData.wDay > 30)
        {
            mainData.wDay = 30;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    case 12:
        if (mainData.wDay > 31)
        {
            mainData.wDay = 31;
            _itoa_s(mainData.wDay, buff, 10);
            ConvertToWChar();
            SendMessage(hWEditDate, WM_SETTEXT, NULL, (LPARAM)buffW);
        }
        break;
    }
    

    /////

    SendMessage(hWEditHours, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    mainData.wHour = atoi(buff);
    if (mainData.wHour > 23)
    {
        mainData.wHour = 23;
        _itoa_s(mainData.wHour, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditHours, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    if (mainData.wHour < 1)
    {
        mainData.wHour = 1;
        _itoa_s(mainData.wHour, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditHours, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hWEditMin, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    mainData.wMinute = atoi(buff);
    if (mainData.wMinute > 59)
    {
        mainData.wMinute = 59;
        _itoa_s(mainData.wMinute, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditMin, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    if (mainData.wMinute < 1)
    {
        mainData.wMinute = 1;
        _itoa_s(mainData.wMinute, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditMin, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hWEditSec, WM_GETTEXT, 3, (LPARAM)buffW);
    ConvertToChar();
    mainData.wSecond = atoi(buff);
    if (mainData.wSecond > 59)
    {
        mainData.wSecond = 59;
        _itoa_s(mainData.wSecond, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditSec, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    if (mainData.wSecond < 1)
    {
        mainData.wSecond = 1;
        _itoa_s(mainData.wSecond, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditSec, WM_SETTEXT, NULL, (LPARAM)buffW);
    }

    SendMessage(hWEditMSec, WM_GETTEXT, 4, (LPARAM)buffW);
    ConvertToChar();
    mainData.wMilliseconds = atoi(buff);
    if (mainData.wMilliseconds > 999)
    {
        mainData.wMilliseconds = 999;
        _itoa_s(mainData.wMilliseconds, buff, 10);
        ConvertToWChar();
        SendMessage(hWEditMSec, WM_SETTEXT, NULL, (LPARAM)buffW);
    }
    
    int t = mainData.wDay + mainData.wMonth + mainData.wYear + mainData.wHour + mainData.wMinute + mainData.wSecond +
        mainData.wMilliseconds;

    return (t && edit_msec);
}

void TimeClass::PlusTime()
{
    union
    {
        ULARGE_INTEGER li;
        FILETIME ft;
    };

    add(edit_msec);

    mainData;
}

void TimeClass::add(double seconds) {

    FILETIME f;
    SystemTimeToFileTime(&mainData, &f);

    ULARGE_INTEGER u;
    memcpy(&u, &f, sizeof(u));

    const double c_dSecondsPer100nsInterval = 100. * 1.E-6;//9
    u.QuadPart += seconds / c_dSecondsPer100nsInterval;

    memcpy(&f, &u, sizeof(f));

    FileTimeToSystemTime(&f, &mainData);
}

void TimeClass::ConvertToWChar()
{
    int size = strlen(buff);
    int i;
    for (i = 0; i < size; ++i)
    {
        buffW[i] = buff[i];
    }
    buffW[i] = '\0';
}

void TimeClass::ConvertToChar()
{
    int size = sizeof(buffW)/2;
    int i;
    for (i = 0; i < size; ++i)
    {
        buff[i] = buffW[i];
    }
    buff[i] = '\0';
}
