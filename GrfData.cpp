#include "stdafx.h"
#include "CommonDef.h"
#include "Borer.h"

#include "MainFrm.h"

#include "GrfData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CGrfData, CObject, 0)

CGrfData::CGrfData()
{
}

CGrfData::~CGrfData()
{
}

void CGrfData::Serialize(CArchive& ar)
{
}
