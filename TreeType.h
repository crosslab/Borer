// TreeType.h: interface for the CTreeType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREETYPE_H__B3378694_9AD2_4136_9766_EF9EC54988E6__INCLUDED_)
#define AFX_TREETYPE_H__B3378694_9AD2_4136_9766_EF9EC54988E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct NODE_TYPE
{
  WORD wNbItems;
  WORD wBufSize;
  HTREEITEM hti;
  void * dwTurd;
  UINT uState;
  char *buf;
}; 

enum TREE_TYPE_ERROR
{
  TTE_MEMORY,
    TTE_INVALID_FILE,
    TTE_INVALID_CSV_FILE,
    TTE_OPEN,
    TTE_READ,
    TTE_WRITE,
    TTE_CLOSE,
    TTE_EMPTY_FILE,
    TTE_INVALID_DIRECTORY,
    TTE_MAX_LEVEL,
};

enum HINT
{
  HINT_NONE = 0,
    HINT_NEW,
    HINT_LOAD_DIRECTORY,
    HINT_LOAD_TREE_TYPE,
    HINT_LOAD_IDENT_TYPE,
    HINT_LOAD_CSV_TYPE,
    HINT_SAVE_TREE_TYPE,
    HINT_SAVE_IDENT_TYPE,
    HINT_SAVE_CSV_TYPE,
};

enum FILE_FORMAT
{
  FF_TREE_TYPE,
    FF_INDENT_TYPE,
    FF_CSV_TYPE,
    FF_MAX_TYPES,
    
    FF_DIRECTORY_TYPE, // Special type to read directories
    FF_CLIPBOARD_TYPE, // Special type to copy to/from the Clipboard
};

struct  HINT_EXT
{
  HINT m_hint;
  FILE_FORMAT m_ff;
  
  HINT_EXT(HINT hint, FILE_FORMAT ff)
  {
    m_hint = hint;
    m_ff = ff;
  }
};

struct EXTENSION
{
  char *m_text;
  char *m_name;
  
  EXTENSION(char *text, char *name)
  {
    m_text = text;
    m_name = name;
  }
};

class CTreeType  
{
public:
  CTreeType();
  virtual ~CTreeType();
  BOOL AllocateTree(size_t uCount);
  void DeAllocateTree();
  
  WORD m_wTotalNbItems;
  NODE_TYPE *m_pnt;
};

#endif // !defined(AFX_TREETYPE_H__B3378694_9AD2_4136_9766_EF9EC54988E6__INCLUDED_)

