#pragma once

#include "FramePointsBuilder.h"
#include "dbpl.h"
#include "dbents.h"

class PLine3DFrameBuilder : public FramePointsBuilder
{

	public:
		PLine3DFrameBuilder();
		~PLine3DFrameBuilder();
		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int );
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();

	private:	

		AcDb3dPolyline * _pPLine3d;
	
};

	
