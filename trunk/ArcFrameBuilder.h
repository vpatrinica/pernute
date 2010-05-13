#pragma once

#include "FramePointsBuilder.h"
#include "dbpl.h"
#include "dbents.h"

class ArcFrameBuilder : public FramePointsBuilder
{

	public:
		ArcFrameBuilder();
		~ArcFrameBuilder();
		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int );
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();

	private:	

		AcDbArc * _pArc;
	
};
