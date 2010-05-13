#pragma once

#include "FramePointsBuilder.h"
#include "dbspline.h"
#include "dbents.h"

class SplineFrameBuilder : public FramePointsBuilder
{

	public:
		SplineFrameBuilder();
		~SplineFrameBuilder();
		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int );
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();

	private:	

		AcDbSpline * _pSpline;
	
};
