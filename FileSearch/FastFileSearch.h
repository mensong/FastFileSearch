#pragma once

class CDriveIndex;

#ifndef FILESEARCH_EXPORTS
typedef CDriveIndex* (*FN_CreateIndex)(WCHAR Drive);
typedef void (*FN_DeleteIndex)(CDriveIndex *di);
typedef WCHAR* (*FN_Search)(CDriveIndex *di, WCHAR *szQuery, WCHAR *szPath, BOOL bSort, BOOL bEnhancedSearch, int maxResults, BOOL *bFoundAll);
typedef void (*FN_FreeResultsBuffer)(WCHAR *szResults);
typedef BOOL (*FN_SaveIndexToDisk)(CDriveIndex *di, WCHAR *szPath);
typedef CDriveIndex* (*FN_LoadIndexFromDisk)(WCHAR *szPath);

#define DEF_PROC(hDll, name) \
	FN_##name name = (FN_##name)::GetProcAddress(hDll, #name); \
	this->name = name


class FILESEARCH
{
private:
	static FILESEARCH* s_ins;

public:
	static FILESEARCH& Ins()
	{
		if (!s_ins)
			s_ins = new FILESEARCH;
		return *s_ins;
	}

	static void Release()
	{
		if (s_ins)
		{
			delete s_ins;
			s_ins = NULL;
		}
	}

	FILESEARCH()
	{
		hDll = LoadLibraryA("FileSearch.dll");
		if (hDll)
		{			
			DEF_PROC(hDll, CreateIndex);
			DEF_PROC(hDll, DeleteIndex);
			DEF_PROC(hDll, Search);
			DEF_PROC(hDll, FreeResultsBuffer);
			DEF_PROC(hDll, SaveIndexToDisk);
			DEF_PROC(hDll, LoadIndexFromDisk);
		}
		else
		{
			::MessageBoxA(NULL, "找不到FileSearch.dll模块", "找不到模块", MB_OK | MB_ICONERROR);
		}
	}
	~FILESEARCH()
	{
		if (hDll)
		{
			FreeLibrary(hDll);
			hDll = NULL;
		}
	}

	FN_CreateIndex		  CreateIndex;
	FN_DeleteIndex		  DeleteIndex;
	FN_Search			  Search;
	FN_FreeResultsBuffer  FreeResultsBuffer;
	FN_SaveIndexToDisk	  SaveIndexToDisk;
	FN_LoadIndexFromDisk  LoadIndexFromDisk;

	HMODULE hDll;
};
__declspec(selectany) FILESEARCH* FILESEARCH::s_ins = NULL;

#endif