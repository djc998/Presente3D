// This has been taken from
// http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Obfuscated+Zip+I%2FO


#ifndef presente3ddata_header
#define presente3ddata_header


#include "OgreArchive.h"
#include "OgreArchiveFactory.h"

#define PRESENTE3DDATA_FILE_EXT "overlay"

// Forward declaration for zziplib to avoid header file dependency.
typedef struct zzip_dir ZZIP_DIR;
typedef struct zzip_file ZZIP_FILE;
 
namespace Presente3D
{
    /** Specialisation of the Archive class to allow reading of files from an
        presente3d data format source archive.
    @remarks
        This archive format supports presente3d data archives.
    */
    class Presente3DData : public Ogre::Archive 
    {
    protected:
        /// Handle to root zip file
        ZZIP_DIR* mZzipDir;
        /// Handle any errors from zzip
        void checkZzipError(int zzipError, const Ogre::String& operation) const;
        /// File list (since zziplib seems to only allow scanning of dir tree once)
        Ogre::FileInfoList mFileList;
 
    public:
        Presente3DData(const Ogre::String& name, const Ogre::String& archType );
        ~Presente3DData();
        /// @copydoc Archive::isCaseSensitive
        bool isCaseSensitive(void) const { return false; }
 
        /// @copydoc Archive::load
        void load();
        /// @copydoc Archive::unload
        void unload();
 
        /// @copydoc Archive::open
        Ogre::DataStreamPtr open(const Ogre::String& filename, bool readOnly = true) const;
 
        /// @copydoc Archive::list
        Ogre::StringVectorPtr list(bool recursive = true, bool dirs = false);
 
        /// @copydoc Archive::listFileInfo
        Ogre::FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);
 
        /// @copydoc Archive::find
        Ogre::StringVectorPtr find(const Ogre::String& pattern, bool recursive = true,
            bool dirs = false);
 
        /// @copydoc Archive::findFileInfo
        Ogre::FileInfoListPtr findFileInfo(const Ogre::String& pattern, bool recursive = true,
            bool dirs = false);
 
        /// @copydoc Archive::exists
        bool exists(const Ogre::String& filename);
 
        /// @copydoc Archive::getModifiedTime
        time_t getModifiedTime(const Ogre::String& filename);
    };
 
    /** Specialisation of ArchiveFactory for presente3d data files. */
    class Presente3DDataFactory : public Ogre::ArchiveFactory
    {
    public:
        virtual ~Presente3DDataFactory() {}
        /// @copydoc FactoryObj::getType
        const Ogre::String& getType(void) const;
        /// @copydoc FactoryObj::createInstance
        Ogre::Archive *createInstance( const Ogre::String& name ) 
        {
            // Change to match the file extension of your choosing.
            return new Presente3DData(name, PRESENTE3DDATA_FILE_EXT);
        }
        /// @copydoc FactoryObj::destroyInstance
        void destroyInstance( Ogre::Archive* arch) { OGRE_DELETE arch; }
    };
 
    /** Specialisation of DataStream to handle streaming data from zip archives. */
    class Presente3DDataStream : public Ogre::DataStream
    {
    protected:
        ZZIP_FILE* mZzipFile;
    public:
        /// Unnamed constructor
        Presente3DDataStream(ZZIP_FILE* zzipFile, size_t uncompressedSize);
        /// Constructor for creating named streams
        Presente3DDataStream(const Ogre::String& name, ZZIP_FILE* zzipFile, size_t uncompressedSize);
        ~Presente3DDataStream();
        /// @copydoc DataStream::read
        size_t read(void* buf, size_t count);
        /// @copydoc DataStream::skip
        void skip(long count);
        /// @copydoc DataStream::seek
        void seek( size_t pos );
        /// @copydoc DataStream::seek
        size_t tell(void) const;
        /// @copydoc DataStream::eof
        bool eof(void) const;
        /// @copydoc DataStream::close
        void close(void);
    };
}
#endif