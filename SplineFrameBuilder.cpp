#include "SplineFrameBuilder.h"


SplineFrameBuilder::SplineFrameBuilder()
{
	acutPrintf(_T("Constructor of SplineFrameBuilder called ...\n"));

}

SplineFrameBuilder::~SplineFrameBuilder()
{
	acutPrintf(_T("Destructor of SplineFrameBuilder called ...\n"));

}


void SplineFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& SplineObject, int granularity)
{
	acutPrintf(_T("Building the points using SplineFrameBuilder  ...\n"));
	_pSpline = AcDbSpline::cast(SplineObject);
	
	AcGePoint3d startPoint;
	_pSpline->getStartPoint(startPoint);
	arrayPoints.append(startPoint);
	
	
	double length, endParam = 0;
	
	_pSpline->getEndParam(endParam);

	_pSpline->getDistAtParam(endParam, length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 0; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pSpline->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	AcGePoint3d endPoint;
	_pSpline->getPointAtParam(endParam, endPoint);
	arrayPoints.append(endPoint);

	acutPrintf(_T("Built the points using SplineFrameBuilder  ...\n"));


}

void SplineFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using SplineFrameBuilder  ...\n"));
	
}

void SplineFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using SplineFrameBuilder  ...\n"));
	
}