#pragma once

#include "FramePointsBuilder.h"
#include "dbpl.h"
#include "dbents.h"

class PLine2DFrameBuilder : public FramePointsBuilder
{

	public:
		PLine2DFrameBuilder();
		~PLine2DFrameBuilder();
		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int );
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();

	private:	

		AcDb2dPolyline * _pPLine2d;
	
};

/*

enum Poly2dType {
  k2dSimplePoly = 0,
  k2dFitCurvePoly = 1,
  k2dQuadSplinePoly = 2,
  k2dCubicSplinePoly = 3
};
enum Poly3dType {
  k3dSimplePoly = 0,
  k3dQuadSplinePoly = 1,
  k3dCubicSplinePoly = 2
};

 AcDb2dPolyline
 AcDb3dPolyline
 AcDbArc
 AcDbLine
 AcDbPolyline
 AcDbSpline
              

	



*/