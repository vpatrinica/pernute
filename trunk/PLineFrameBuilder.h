#pragma once

#include "FramePointsBuilder.h"
#include "dbpl.h"
#include "dbents.h"

class PLineFrameBuilder : public FramePointsBuilder
{

	public:
		PLineFrameBuilder();
		~PLineFrameBuilder();
		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int );
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();

	private:	

		AcDbPolyline * _pPLine;
	
};

	