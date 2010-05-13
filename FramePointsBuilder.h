#pragma once

#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#error _DEBUG should not be defined except in internal Adesk debug builds
#endif

#include "dbobjptr.h"
#include "aced.h"
#include "dbsymtb.h"
#include "dbapserv.h"
#include "acgi.h"
#include "tchar.h"
#include <list>
#include <stdio.h>
#include <iostream>

#include  <ADSLIB.H>


class FramePointsBuilder
{

	public:

		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int){};
		virtual void getFramePoints(AcArray<AcGePoint3d> * _arrayPoints){};
		virtual void printFramePoints(){};

	protected:	
		
		FramePointsBuilder(){};
		AcArray<AcGePoint3d>* _result;
};