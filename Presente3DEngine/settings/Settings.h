#pragma once

#include <string>

class Settings
{
public:
	static void SetPresentationXML(const char* path);
    static void SetExecutablePath(const char* path);
    static std::string GetExecutablePath();
    static std::string GetExecutableFolder();
    static std::string GetPublicResourcesFolder();
    static std::string GetCustomResourcesFile();
    static std::string GetConfigFilePath();
    static std::string GetLogFilePath();
    static std::string GetPresenteScreenshotsFolder();

	static const char* GetPresentationXML();
    static std::string GetPresentationXMLFolder();
	static int GetWindowWidth();
	static int GetWindowHeight();

    // 
    static std::string GetUserDocumentsFolderPath();
    static std::string GetUserDocumentsPresenteFolderPath();

    static std::string GetUserApplicationDataFolderPath();
    static std::string GetUserTempPresente3DFolderPath();
    static std::string GetTempPresentationFilePath();

    static bool isQuadBufferSelected(){return quadbuffer;};
    static void setQuadBuffer(bool v){quadbuffer = v;};
private:
	static std::string presentation_path;
    static std::string executable_path;
	static int window_width;
	static int window_height;
    
    static bool quadbuffer;
};