#include "framework\PluginDefinition.h"
#include "framework\menuCmdID.h"
#include "app.h"
#include "sql/sql.h"
#include <string>
#include <cstdlib>
#include <memory>
using namespace std;

//
// The data of Notepad++ that you can use in your plugin commands
// 全局变量
//
extern NppData nppData;

void about()
{
    ::MessageBox(NULL, TEXT("NppSql用于把mybatis日志转换成SQL语句"), TEXT("简介"), MB_OK);
}

void toSql()
{
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    // 选中的内容的长度
    int length = 0;
    length = ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, 0);
    if (length != 0)
    {
        unique_ptr<char[]> content(new char[length + 1]);
        ::SendMessage(curScintilla, SCI_GETSELTEXT, 0, (LPARAM)content.get());
        string result = to_sql(string(content.get()));
        write_in_new_docment(result.c_str());
    }
}

void write_in_new_docment(const char *content)
{
    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)content);
}