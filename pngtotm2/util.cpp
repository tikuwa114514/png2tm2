#include "util.h"

void ErrMSG(std::wstring txt) {
	MessageBox(NULL, txt.c_str(),
		TEXT("Error"), MB_ICONWARNING);
}

size_t wstrsize(std::wstring wstr) {
	return (wcslen(wstr.c_str()) + 1) * sizeof(wchar_t);
}

void wstr2chr(std::wstring wstr,char* buffer) 
{
	size_t size = wstrsize(wstr);
	std::wcstombs(buffer, wstr.c_str(), size);
}


DWORD convertimage(std::wstring imagepath, std::wstring dirpath) {
	std::wstring extentionname;
	size_t size;
	size = wstrsize(imagepath);
	extentionname = imagepath.substr(imagepath.find_last_of('.'), size);
	if (extentionname == L".png" || extentionname == L".PNG")
	{
		return convertpng2tm2(imagepath,dirpath);
	}
	else if (extentionname == L".tm2" || extentionname == L".TM2")
	{
		return converttm2png(imagepath, dirpath);
	}
	else
	{
		return -1;
	}
	return 0;
}

DWORD converttm2png(std::wstring tm2path, std::wstring dirpath) {
	std::wstring tm2name, pngpath;
	size_t sizetm2path = wstrsize(tm2path);

	size_t s, g;
	s = tm2path.find_last_of('\\') + 1;
	g = tm2path.find_last_of('.');
	tm2name = tm2path.substr(s, g - s);
	pngpath = dirpath + L"\\" + tm2name + L".png";

	char* tm2pathchr = new char[sizetm2path];
	wstr2chr(tm2path, tm2pathchr);
	size_t sizepngpath = wstrsize(pngpath);
	char* pngpathchr = new char[sizepngpath];
	wstr2chr(pngpath, pngpathchr);



	FILE* tm2fp;
	tm2fp = fopen(tm2pathchr, "rb");
	if (tm2fp == NULL)
	{
		ErrMSG(L"Faild read tm2");
		return -1;
	}

	fseek(tm2fp, 0, SEEK_END);
	long int tm2size = ftell(tm2fp);
	fseek(tm2fp, 0, SEEK_SET);
	char* tm2buffer;
	tm2buffer = (char *)calloc(tm2size, sizeof(char));
	fread(tm2buffer, sizeof(char), tm2size, tm2fp);

	int error = OutbreakTm2ToPng(tm2buffer, pngpathchr);
	if (error==0)
	{
		ErrMSG(L"Faild convrt png to tm2");
		free(tm2buffer);
		return -1;
	}
	
	free(tm2buffer);
	return 0;
}

DWORD convertpng2tm2(std::wstring pngpath, std::wstring dirpath) {
	std::wstring pngname, tm2path;
	size_t s,g;
	s = pngpath.find_last_of('\\') + 1;
	g = pngpath.find_last_of('.');
	pngname = pngpath.substr(s, g-s);

	if (pngname == pngpath)
	{
		ErrMSG(L"Faild get file name");
		return -1;
	}

	tm2path = dirpath + L"\\" + pngname + L".tm2";
	uint32_t dataSize;
	int w, h;

	size_t sizepngpath = wstrsize(pngpath);
	char* pngpathchr = new char[sizepngpath];
	wstr2chr(pngpath, pngpathchr);
	
	size_t sizetm2path = wstrsize(tm2path);
	char* tm2pathchr = new char[sizetm2path];
	wstr2chr(tm2path, tm2pathchr);
	
	void* data = OutbreakPngToTm2(pngpathchr, 0, &w, &h, &dataSize);
	if (data)
	{
		FILE* outfp;
		outfp = fopen(tm2pathchr, "wb");
		if (outfp == NULL)
		{
			ErrMSG(L"Faild write tm2");
			delete pngpathchr; delete tm2pathchr;
			return -1;
		}
		if (fwrite(data, sizeof(char), dataSize, outfp) < 1) {
			ErrMSG(L"Faild save tm2");
		}
		fclose(outfp);
		free(data);
		delete pngpathchr; delete tm2pathchr;
		return 0;
	}
	else
	{
		ErrMSG(L"Faild Convert PNG to TM2");
		delete pngpathchr; delete tm2pathchr;
		return -1;
	}
}