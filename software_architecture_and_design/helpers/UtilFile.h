#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <io.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <direct.h>
#include <unordered_set>
#include <filesystem>
#include <fstream>

inline void makePath(std::string path)
{
    if (path == "")
        return;
    size_t start = 0, end = 0;
    do
    {
        end = path.find("\\", start);
        _mkdir(end != std::string::npos ? path.substr(0, end + 1).c_str() : path.c_str());
        start = end + 1;
    } while (end != std::string::npos);
}

inline static char* fileRead(const std::string& path, unsigned long long* fileSize = NULL, bool text = false)
{
    FILE* file = fopen( path.c_str(), "rb" );
    if(!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    size_t bufLen = ftell(file);
    if(fileSize)
        *fileSize = bufLen;
    rewind( file );

    char* buffer = new char[bufLen + (text ? 1 : 0)];
    size_t last = fread(buffer, 1, bufLen, file);
    if(text)
        buffer[last] = 0;

    fclose(file);
    return buffer;
}

inline static char* fileReadStr(const std::string& path)
{
    return fileRead(path, 0, true);
}

inline bool isImageExtension(const std::filesystem::path& filePath) {
    std::string extension = filePath.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    static const std::unordered_set<std::string> validExtensions = { ".jpg", ".jpeg", ".png", ".gif", ".bmp" };
    return validExtensions.count(extension) > 0;
}

inline static int fileWrite(const std::string& name, const char* bulk, int len, bool append = false, bool exclusive = false)
{
    size_t pos = name.rfind("\\");
    if(pos != std::string::npos)
        makePath(name.substr(0, pos));

    FILE* f = NULL;
    if(append)
        f = fopen(name.c_str(), "ab");
    else
    {
        int fd = _open(name.c_str(), (exclusive ? _O_EXCL : 0) | _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _S_IREAD | _S_IWRITE);
        f = fd == -1 ? NULL : _fdopen(fd, "wb");
    }
    if(!f)
        return 0;

    int result = fwrite(bulk, 1, len, f);
    fclose(f);
    return result;
}

inline static int fileWriteStr(const std::string& name, std::string str, bool append = false, bool exclusive = false)
{
    return fileWrite(name, str.c_str(), str.length(), append, exclusive);
}

inline static std::string getFileStr(const std::string& path) {
    std::ifstream input_file(path, std::ios::binary);
    std::string file_contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    return file_contents;
}

inline static void writeFileStr(const std::string& path, const char * buff, int size) {
    std::ofstream output_file(path, std::ios::binary);
    output_file.write(buff, size);
    output_file.close();
}

inline static int fileAppend(const std::string& name, std::string str)
{
    return fileWriteStr(name, str, true);
}

// tries to open file in "exclusive" mode: if the file does not exist, then the function creates it, otherwise it fails.
inline static int fileWriteExclusive(const std::string& name, std::string str)
{
    return fileWriteStr(name, str, false, true);
}

// number of files in directory
/*inline static int fileCount(const char* dir)
{
    int result = 0;
    DIR* d = opendir(dir);
    struct dirent* ent;
    while(ent = readdir(d))
    {
        std::string name = ent->d_name;
        if(name != "." && name != "..")
            result++;
    }
    closedir(d);
    return result;
}
*/
inline bool fileExists(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "r");
    if(!f)
        return false;
    fclose(f);
    return true;
}
