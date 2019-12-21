
#ifndef _MY_BITMAP
#define _MY_BITMAP
class CMyBitmap:public CBitmap
{
public:
  //	CMyBitmap();
  virtual BOOL LoadBitmap(LPCTSTR szFilename)
  {
    
    ASSERT(szFilename);
    
    DeleteObject();
    
    HBITMAP hBitmap = NULL;
    
    hBitmap = (HBITMAP)LoadImage(NULL, szFilename, IMAGE_BITMAP, 0, 0,
      
      LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
    
    return Attach(hBitmap);
    
  };
  
};
#endif