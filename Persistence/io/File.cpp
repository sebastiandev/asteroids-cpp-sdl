#include "File.h"

using namespace io;

File::File(void) : name("")
{
}

File::File(string n) : name(n)
{
}

File::~File(void)
{
}

list<string> File::getFiles() //throw (IOException)
{
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA findFileData;
    wstring spec;
    stack<wstring> directories;
	list<string> files;
	wstring path(L"C:\\");
	wstring wfile;

	if (!name.empty())
	{
		path.clear();
		path.resize(name.size());
		copy(name.begin(), name.end(), path.begin());
	}

    directories.push(path);
    files.clear();

    while (!directories.empty())
	{
        path = directories.top();
        spec = path + L"\\" + L"*";
        directories.pop();

        fileHandle = FindFirstFile(spec.c_str(), &findFileData);
        if (fileHandle == INVALID_HANDLE_VALUE) 
		{
			string msg("Invalid file handler: ");
			msg.append(toString(GetLastError()));
            throw IOException(msg);
        }

        do
		{
            if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
			{
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
                    directories.push(path + L"\\" + findFileData.cFileName);
                }
                else
				{
					wfile = path + L"\\" + findFileData.cFileName;
					string filepath(wfile.begin(), wfile.end());
					size_t pathIndex = filepath.find_last_of("\\");
					if (pathIndex!=string::npos)
					{
						string filename(filepath.substr(pathIndex+1));
						size_t nameIndex = filename.find(".xml");
						if (nameIndex!=string::npos)
						{
							files.push_back(filename);
						}
					}
                }
            }
        } while (FindNextFile(fileHandle, &findFileData) != 0);

        if (GetLastError() != ERROR_NO_MORE_FILES)
		{
            FindClose(fileHandle);
			string msg("Error while retrieving files: ");
			msg.append(toString(GetLastError()));
            throw IOException(msg);
        }
        FindClose(fileHandle);
        fileHandle = INVALID_HANDLE_VALUE;
    }
	return files;
}

void File::remove(void) //throw (IOException)
{
	BOOL result = FALSE;
	wstring wname = toWString(name);
	LPCWSTR filename = wname.c_str();
	result = DeleteFile(filename);
	if (!result)
	{
		string message("Unable to delete file ");
		message.append(name).append(": ");
		throw IOException(message.append(toString(GetLastError())));
	}
}

string File::toString(DWORD dword)
{
	stringstream ss;
	ss << dword;
	return ss.str();
}

wstring File::toWString(const string& str)
{
    int length;
    int strLength = (int)str.length()+1;
    length = MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, 0, 0); 
    wchar_t* buf = new wchar_t[length];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), strLength, buf, length);
    wstring wstr(buf);
    delete[] buf;
    return wstr;
}
