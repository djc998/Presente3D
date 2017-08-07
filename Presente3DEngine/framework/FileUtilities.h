#ifndef fileutilities_header
#define fileutilities_header

namespace Presente3D
{

class FileUtilities
{
protected:
    FileUtilities() { };
    FileUtilities(const FileUtilities&);
    FileUtilities& operator=(const FileUtilities&);

public:
    static FileUtilities& getInstance();

    // Returns whether file or directory exists
    bool Exists(const std::string& strFileOrDir);
    // Returns whether entity is a directory
    bool IsDir(const std::string& strDir);
    // Returns whether entity is a file
    bool IsFile(const std::string& strFile);

    // Makes path "clean": removes starting / trailing spaces, removes trailing slashes
    std::string CleanupPath(const std::string& strPath);

    // Returns current executable directory
    std::string GetCurrentExecDir();


};


};

#endif