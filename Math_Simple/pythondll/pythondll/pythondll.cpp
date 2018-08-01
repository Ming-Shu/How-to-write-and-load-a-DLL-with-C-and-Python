// pythondll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define LIBDLL extern "C" __declspec(dllexport)


LIBDLL int sum(int a, int b)
{
	return a+b;
}

LIBDLL int mult(int a, int b)
{
	return a * b;
}

LIBDLL void sentMessage()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"DLL FROM PYTHON?",
		(LPCWSTR)L"Python Tutorials",
		MB_ICONWARNING |MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
		);
}