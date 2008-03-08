/////////////////////////////////////////////////////////////////////////////
// Name:        treebook.h
// Purpose:     documentation for wxTreebookEvent class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxTreebookEvent
    @wxheader{treebook.h}
    
    This class represents the events generated by a treebook control: currently,
    there are four of them. The PAGE_CHANGING and PAGE_CHANGED - have exactly the
    same
    behaviour as wxNotebookEvent.
    
    The other two NODE_COLLAPSED and NODE_EXPANDED are triggered when page node in
    the tree control
    is collapsed/expanded. The page index could be retreived by calling
    wxTreebookEvent::GetSelection.
    
    
    @library{wxcore}
    @category{events}
    
    @seealso
    wxNotebookEvent, wxTreebook
*/
class wxTreebookEvent : public wxNotifyEvent
{
public:
    /**
        @sa wxNotebookEvent
    */
    wxTreebookEvent(wxEventType commandType = wxEVT_@NULL, int id = 0,
                    int nSel = wxNOT_FOUND,
                    int nOldSel = wxNOT_FOUND);

    /**
        Returns the page that was selected before the change, wxNOT_FOUND if none was
        selected.
    */
    int GetOldSelection();

    /**
        Returns the currently selected page, or wxNOT_FOUND if none was selected.
    */
    int GetSelection();
};


/**
    @class wxTreebook
    @wxheader{treebook.h}
    
    This class is an extension of the Notebook class that allows a tree structured
    set of pages to be shown in a control.
    A classic example is a netscape preferences dialog that shows a tree
    of preference sections on the left and select section page on the right.
    
    To use the class simply create it and populate with pages using
    wxTreebook::InsertPage,
    wxTreebook::InsertSubPage,
    wxTreebook::AddPage,
    wxTreebook::AddSubPage.
    
    If your tree is no more than 1 level in depth then you could
    simply use wxTreebook::AddPage and 
    wxTreebook::AddSubPage to sequentially populate your tree
    by adding at every step a page or a subpage to the end of the tree.
    
    @library{wxcore}
    @category{miscwnd}
    
    @seealso
    wxNotebook, wxTreebookEvent, wxImageList, @ref overview_samplenotebook
    "notebook sample"
*/
class wxTreebook : public wxBookCtrl overview
{
public:
    //@{
    /**
        Creates an empty TreeBook control.
        
        @param parent 
        The parent window. Must be non-@NULL.
        
        @param id 
        The window identifier.
        
        @param pos 
        The window position.
        
        @param size 
        The window size.
        
        @param style 
        The window style. See wxNotebook.
        
        @param name 
        The name of the control (used only under Motif).
    */
    wxTreebook();
        wxTreebook(wxWindow* parent, wxWindowID id,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxTBK_DEFAULT,
                   const wxString& name = wxEmptyString);
    //@}

    /**
        Destroys the wxTreebook object.
        
        Also deletes all the pages owned by the control (inserted previously into it).
    */
    ~wxTreebook();

    /**
        Adds a new page. The page is placed at the topmost level after all other pages.
        @NULL could be specified for page to create an empty page.
    */
    bool AddPage(wxWindow* page, const wxString& text,
                 bool bSelect = @false,
                 int imageId = wxNOT_FOUND);

    /**
        Adds a new child-page to the last top-level page.
        @NULL could be specified for page to create an empty page.
    */
    bool AddSubPage(wxWindow* page, const wxString& text,
                    bool bSelect = @false,
                    int imageId = wxNOT_FOUND);

    /**
        Sets the image list for the page control and takes ownership of the list.
        
        @sa wxImageList, SetImageList()
    */
    void AssignImageList(wxImageList* imageList);

    /**
        Changes the selection for the given page, returning the previous selection.
        
        The call to this function does not generate the page changing events.
        This is the only difference with SetSelection().
        See @ref overview_progevent "this topic" for more info.
    */
    int ChangeSelection(size_t page);

    /**
        Shortcut for wxTreebook::ExpandNode(pageId, @false).
    */
    bool CollapseNode(size_t pageId);

    /**
        Creates a treebook control. See wxTreebook() for the description of the
        parameters.
    */
    bool Create(wxWindow* parent, wxWindowID id,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxTBK_DEFAULT,
                const wxString& name = wxEmptyString);

    /**
        Deletes all pages inserted into the treebook. No event is generated.
    */
    bool DeleteAllPages();

    /**
        Deletes the page at the specified position and all its children. Could trigger
        page selection change
        in a case when selected page is removed. In that case its parent is selected
        (or the next page if no parent).
    */
    bool DeletePage(size_t pagePos);

    /**
        Expands (collapses) the pageId node. Returns the previous state.
        May generate page changing events (if selected page
        is under the collapsed branch, then its parent is autoselected).
    */
    bool ExpandNode(size_t pageId, bool expand = @true);

    /**
        Returns the image index for the given page.
    */
    int GetPageImage(size_t n);

    /**
        Returns the parent page of the given one or @c wxNOT_FOUND if this is a
        top-level page.
    */
    int GetPageParent(size_t page);

    /**
        Returns the string for the given page.
    */
    wxString GetPageText(size_t n);

    /**
        Returns the currently selected page, or wxNOT_FOUND if none was selected.
        
        Note that this method may return either the previously or newly selected page
        when called from the EVT_TREEBOOK_PAGE_CHANGED handler
        depending on the platform and so wxTreebookEvent::GetSelection should be used
        instead in this case.
    */
    int GetSelection();

    /**
        Inserts a new page just before the page indicated by pagePos.
        The new page is placed before pagePos page and on the same level.
        @NULL could be specified for page to create an empty page.
    */
    bool InsertPage(size_t pagePos, wxWindow* page,
                    const wxString& text,
                    bool bSelect = @false,
                    int imageId = wxNOT_FOUND);

    /**
        Inserts a sub page under the specified page.
        
        @NULL could be specified for page to create an empty page.
    */
    bool InsertSubPage(size_t pagePos, wxWindow* page,
                       const wxString& text,
                       bool bSelect = @false,
                       int imageId = wxNOT_FOUND);

    /**
        Gets the pagePos page state -- whether it is expanded or collapsed
    */
    bool IsNodeExpanded(size_t pageId);

    /**
        Sets the image list for the page control. It does not take ownership of the
        image list, you must delete it yourself.
        
        @sa wxImageList, AssignImageList()
    */
    void SetImageList(wxImageList* imageList);

    /**
        Sets the image index for the given page. ImageId is an index into the image list
        which was set with SetImageList().
    */
    bool SetPageImage(size_t page, int imageId);

    /**
        Sets the text for the given page.
    */
    bool SetPageText(size_t page, const wxString& text);

    /**
        Sets the selection for the given page, returning the previous selection.
        
        The call to this function generates the page changing events.
        
        This function is deprecated and should not be used in new code. Please use the
        ChangeSelection() function instead.
        
        @sa GetSelection()
    */
    int SetSelection(size_t n);
};
