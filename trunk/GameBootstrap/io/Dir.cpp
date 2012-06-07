#include "Dir.h"

using namespace io;

Dir::Dir(string path)
{
	this->path = path;
}

Dir::~Dir()
{
}

bool Dir::create(string path)
{
	return CreateDirectoryA(path.c_str(), NULL)==TRUE;
	//_mkdir(TEMPDIR);
}

list<string> Dir::getFiles(string dirpath, list<string> filter, bool recursive)
{
	HANDLE fileHandle = INVALID_HANDLE_VALUE;
    DWORD dwError=0;
    WIN32_FIND_DATA findFileData;
    wstring spec;       

    wstring path(L"C:\\");

    list<string> files;
    
    if (!dirpath.empty())
    {
        path.clear();
        path.resize(dirpath.size());
        copy(dirpath.begin(), dirpath.end(), path.begin());
    }

    if (path[path.size() - 1] == wchar_t("\\"))
    {
        spec = path + L"*";
    }
    else
    {
		spec = path + L"\\" + L"*";
    }
    HANDLE hFind = FindFirstFile(spec.c_str(), &findFileData);

    if (INVALID_HANDLE_VALUE == hFind) 
    {
       return files;
    }    

    // List all the files in the directory with some info about them.
    do
    {
       if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
       {
           if (recursive)
		   {
			   if (wcscmp(findFileData.cFileName, L".") != 0 && wcscmp(findFileData.cFileName, L"..") != 0)
				{
					wstring str(findFileData.cFileName);
					string subdir(str.begin(), str.end());

					if (dirpath[dirpath.size() -1] != wchar_t("\\"))
					   dirpath.append("\\");

					list<string> subdirFiles = getFiles(dirpath+subdir, filter, recursive);
					files.splice(files.end(), subdirFiles);                                 
				}
		   }
       }
       else
       {
            wstring str(findFileData.cFileName);
            string fileWithPath(dirpath);
            fileWithPath.append("\\");
            fileWithPath.append(string(str.begin(), str.end()));

			// si hay filtros de extensiones los aplica
			if (filter.size() > 0)
			{
				string extension = fileWithPath.substr( fileWithPath.find_last_of(".")+1);
				list<string>::iterator it;			
				for(it=filter.begin(); it!=filter.end();it++)
				{
					if ((*it).compare(extension) == 0)
					{
						files.push_back(fileWithPath);
						break;
					}
				}
			}
			else
				files.push_back(fileWithPath);
       }
    }
    while (FindNextFile(hFind, &findFileData) != 0);
 
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) 
    {
           return files;
    }

    FindClose(hFind);

    return files;
}

list<string> Dir::getFilesWithoutPath(string dirpath, list<string> filter, bool recursive)
{
	list<string> tmp = getFiles(dirpath, filter, recursive);
	list<string> files;
	list<string>::iterator it;
	for(it=tmp.begin();it!=tmp.end();it++)
		files.push_back( (*it).substr((*it).find_last_of("\\")+1) );

	return files;
}

bool Dir::remove(string dirPath, bool subdirs)
{
	list<string> filters;
	list<string> files = Dir::getFiles(dirPath, filters, subdirs);
	list<string>::iterator it;
	for (it=files.begin(); it!=files.end(); it++)
	{
		File f(*it);
		try
		{
			f.remove();
		}
		catch (IOException e)
		{
			return false;
		}
	}

	return (RemoveDirectoryA(dirPath.c_str())==TRUE);
}

bool Dir::removeFile(string filePath)
{
	File f(filePath);
	try
	{
		f.remove();
	}
	catch (IOException e)
	{
		return false;
	}

	return true;
}