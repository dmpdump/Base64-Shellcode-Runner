#pragma once

INT scrun();

INT b64decode(
	_In_ const PBYTE Src,
	_In_ UINT SrcLen,
	_In_ PCHAR Dest,
	_In_ UINT DestLen
);