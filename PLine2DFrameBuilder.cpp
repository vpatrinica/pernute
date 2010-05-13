#include "PLine2DFrameBuilder.h"

PLine2DFrameBuilder::PLine2DFrameBuilder()
{
	acutPrintf(_T("Constructor of PLine2DFrameBuilder called ...\n"));

}

PLine2DFrameBuilder::~PLine2DFrameBuilder()
{
	acutPrintf(_T("Destructor of PLine2DFrameBuilder called ...\n"));

}


void PLine2DFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& pline2dObject, int granularity)
{
	acutPrintf(_T("Building the points using PLine2DFrameBuilder  ...\n"));
	_pPLine2d = AcDb2dPolyline::cast(pline2dObject);
	
	AcGePoint3d startPoint;
	_pPLine2d->getStartPoint(startPoint);
	arrayPoints.append(startPoint);
	
	
	double length, endParam = 0;
	
	_pPLine2d->getEndParam(endParam);

	_pPLine2d->getDistAtParam(endParam, length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 0; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pPLine2d->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	AcGePoint3d endPoint;
	_pPLine2d->getPointAtParam(endParam, endPoint);
	arrayPoints.append(endPoint);

	acutPrintf(_T("Built the points using PLine2DFrameBuilder  ...\n"));


}

void PLine2DFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using PLine2DFrameBuilder  ...\n"));
	
}

void PLine2DFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using PLine2DFrameBuilder  ...\n"));
	
}