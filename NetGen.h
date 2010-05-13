#pragma once

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"
#include <list>
#include <stdio.h>
#include <iostream>

#include  <ADSLIB.H>

#include "ResbufPtr.h"
#include "FramePointsBuilder.h"
#include "LineFrameBuilder.h"
#include "dbobjptr.h"
#include "dbspline.h"
#include "FramePointsConstructor.h"
#include "InteriorPointsConstructor.h"
#include "InputReader.h"


class NetGen: public AcDbEntity
{
public:
	ACRX_DECLARE_MEMBERS(NetGen);
	NetGen();
	virtual ~NetGen();


	void readInput();
	Acad::ErrorStatus processInput(AcDbObjectIdArray& );
	Acad::ErrorStatus doNet();
	Acad::ErrorStatus outputNet();
	

	

protected:
    virtual Adesk::Boolean  subWorldDraw(AcGiWorldDraw* );
    Acad::ErrorStatus       subTransformBy(const AcGeMatrix3d& );

private:
	InputReader* _inputReader;
	FramePointsConstructor * _fpConstructor;
	InteriorPointsConstructor * _ipConstructor;
};
