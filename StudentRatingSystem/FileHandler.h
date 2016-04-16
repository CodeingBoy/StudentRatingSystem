#pragma once
class CFileHandler
{
    public:
        CFileHandler(const wchar_t *filename, bool bRead);
        ~CFileHandler();
        bool ReadLine(wchar_t *output);
        wchar_t *ReadLine();
        bool Write(wchar_t *content);
        bool WriteLine(wchar_t *content);
        int GetError();
        bool isEOF();
    private:
        bool bRead = true; // ��ȡ���Ǳ���
        int err;
        FILE *fp;
};

