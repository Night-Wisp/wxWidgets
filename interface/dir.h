/////////////////////////////////////////////////////////////////////////////
// Name:        dir.h
// Purpose:     documentation for wxDirTraverser class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxDirTraverser
    @wxheader{dir.h}
    
    wxDirTraverser is an abstract interface which must be implemented by objects
    passed to wxDir::Traverse function.
    
    Example of use (this works almost like wxDir::GetAllFiles):
    
    @code
    class wxDirTraverserSimple : public wxDirTraverser
        {
        public:
            wxDirTraverserSimple(wxArrayString& files) : m_files(files) { }
    
            virtual wxDirTraverseResult OnFile(const wxString& filename)
            {
                m_files.Add(filename);
                return wxDIR_CONTINUE;
            }
    
            virtual wxDirTraverseResult OnDir(const wxString& WXUNUSED(dirname))
            {
                return wxDIR_CONTINUE;
            }
    
        private:
            wxArrayString& m_files;
        };
    
        // get the names of all files in the array
        wxArrayString files;
        wxDirTraverserSimple traverser(files);
    
        wxDir dir(dirname);
        dir.Traverse(traverser);
    @endcode
    
    @library{wxbase}
    @category{file}
*/
class wxDirTraverser 
{
public:
    /**
        This function is called for each directory. It may return @c wxSIR_STOP 
        to abort traversing completely, @c wxDIR_IGNORE to skip this directory but
        continue with others or @c wxDIR_CONTINUE to enumerate all files and
        subdirectories in this directory.
        
        This is a pure virtual function and must be implemented in the derived class.
    */
    virtual wxDirTraverseResult OnDir(const wxString& dirname);

    /**
        This function is called for each file. It may return @c wxDIR_STOP to abort
        traversing (for example, if the file being searched is found) or 
        @c wxDIR_CONTINUE to proceed.
        
        This is a pure virtual function and must be implemented in the derived class.
    */
    virtual wxDirTraverseResult OnFile(const wxString& filename);

    /**
        This function is called for each directory which we failed to open for
        enumerating. It may return @c wxSIR_STOP to abort traversing completely,
        @c wxDIR_IGNORE to skip this directory but continue with others or 
        @c wxDIR_CONTINUE to retry opening this directory once again.
        
        The base class version always returns @c wxDIR_IGNORE.
    */
    virtual wxDirTraverseResult OnOpenError(const wxString& openerrorname);
};


/**
    @class wxDir
    @wxheader{dir.h}
    
    wxDir is a portable equivalent of Unix open/read/closedir functions which
    allow enumerating of the files in a directory. wxDir allows to enumerate files
    as well as directories.
    
    wxDir also provides a flexible way to enumerate files recursively using 
    wxDir::Traverse or a simpler 
    wxDir::GetAllFiles function.
    
    Example of use:
    
    @code
    wxDir dir(wxGetCwd());
    
        if ( !dir.IsOpened() )
        {
            // deal with the error here - wxDir would already log an error message
            // explaining the exact reason of the failure
            return;
        }
    
        puts("Enumerating object files in current directory:");
    
        wxString filename;
    
        bool cont = dir.GetFirst(, filespec, flags);
        while ( cont )
        {
            printf("%s\n", filename.c_str());
    
            cont = dir.GetNext();
        }
    @endcode
    
    @library{wxbase}
    @category{file}
*/
class wxDir 
{
public:
    //@{
    /**
        Opens the directory for enumeration, use IsOpened() 
        to test for errors.
    */
    wxDir();
        wxDir(const wxString& dir);
    //@}

    /**
        Destructor cleans up the associated resources. It is not virtual and so this
        class is not meant to be used polymorphically.
    */
    ~wxDir();

    /**
        Test for existence of a directory with the given name
    */
    static bool Exists(const wxString& dir);

    /**
        The function returns the path of the first file matching the given @e filespec
        or an empty string if there are no files matching it.
        
        The @e flags parameter may or may not include @c wxDIR_FILES, the
        function always behaves as if it were specified. By default, @e flags 
        includes @c wxDIR_DIRS and so the function recurses into the subdirectories
        but if this flag is not specified, the function restricts the search only to
        the directory @e dirname itself.
        
        See also: Traverse()
    */
    static wxString FindFirst(const wxString& dirname,
                              const wxString& filespec,
                              int flags = wxDIR_DEFAULT);

    /**
        The function appends the names of all the files under directory @e dirname 
        to the array @e files (note that its old content is preserved). Only files
        matching the @e filespec are taken, with empty spec matching all the files.
        
        The @e flags parameter should always include @c wxDIR_FILES or the array
        would be unchanged and should include @c wxDIR_DIRS flag to recurse into
        subdirectories (both flags are included in the value by default).
        
        See also: Traverse()
    */
    static size_t GetAllFiles(const wxString& dirname,
                              wxArrayString * files,
                              const wxString& filespec = wxEmptyString,
                              int flags = wxDIR_DEFAULT);

    /**
        Start enumerating all files matching @e filespec (or all files if it is
        empty) and @e flags, return @true on success.
    */
    bool GetFirst(wxString* filename,
                  const wxString& filespec = wxEmptyString,
                  int flags = wxDIR_DEFAULT);

    /**
        Returns the name of the directory itself. The returned string does not have the
        trailing path separator (slash or backslash).
    */
    wxString GetName();

    /**
        Continue enumerating files which satisfy the criteria specified by the last
        call to GetFirst().
    */
    bool GetNext(wxString* filename);

    /**
        Returns the size (in bytes) of all files recursively found in @c dir or
        @c wxInvalidSize in case of error.
        
        In case it happens that while traversing folders a file's size can not be read,
        that file is added to the @c filesSkipped array, if not @NULL, and then
        skipped.
        This usually happens with some special folders which are locked by the
        operating system
        or by another process. Remember that when @c filesSkipped-GetCount() is not
        zero,
        then the returned value is not 100% accurate and, if the skipped files were
        big, it could be
        far from real size of the directory.
        
        See also: wxFileName::GetHumanReadableSize,
        wxGetDiskSpace
    */
    static wxULongLong GetTotalSize(const wxString& dir,
                                    wxArrayString* filesSkipped = @NULL);

    /**
        Returns @true if the directory contains any files matching the given 
        @e filespec. If @e filespec is empty, look for any files at all. In any
        case, even hidden files are taken into account.
    */
    bool HasFiles(const wxString& filespec = wxEmptyString);

    /**
        Returns @true if the directory contains any subdirectories (if a non
        empty @e filespec is given, only check for directories matching it).
        The hidden subdirectories are taken into account as well.
    */
    bool HasSubDirs(const wxString& dirspec = wxEmptyString);

    /**
        Returns @true if the directory was successfully opened by a previous call to 
        Open().
    */
    bool IsOpened();

    /**
        Open the directory for enumerating, returns @true on success
        or @false if an error occurred.
    */
    bool Open(const wxString& dir);

    /**
        Enumerate all files and directories under the given directory recursively
        calling the element of the provided wxDirTraverser 
        object for each of them.
        
        More precisely, the function will really recurse into subdirectories if 
        @e flags contains @c wxDIR_DIRS flag. It will ignore the files (but
        still possibly recurse into subdirectories) if @c wxDIR_FILES flag is
        given.
        
        For each found directory, @ref wxDirTraverser::ondir sink.OnDir is called
        and @ref wxDirTraverser::onfile sink.OnFile is called for every file.
        Depending on the return value, the enumeration may continue or stop.
        
        The function returns the total number of files found or @c (size_t)-1 on
        error.
        
        See also: GetAllFiles()
    */
    size_t Traverse(wxDirTraverser& sink,
                    const wxString& filespec = wxEmptyString,
                    int flags = wxDIR_DEFAULT);
};
