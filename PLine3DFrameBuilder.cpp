#include "PLine3DFrameBuilder.h"

PLine3DFrameBuilder::PLine3DFrameBuilder()
{
	acutPrintf(_T("Constructor of PLine3DFrameBuilder called ...\n"));

}

PLine3DFrameBuilder::~PLine3DFrameBuilder()
{
	acutPrintf(_T("Destructor of PLine3DFrameBuilder called ...\n"));

}


void PLine3DFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& pline3dObject, int granularity)
{
	acutPrintf(_T("Building the points using PLine3DFrameBuilder  ...\n"));
	_pPLine3d = AcDb3dPolyline::cast(pline3dObject);
	
	AcGePoint3d startPoint;
	_pPLine3d->getStartPoint(startPoint);
	arrayPoints.append(startPoint);
	
	
	double length, endParam = 0;
	
	_pPLine3d->getEndParam(endParam);

	_pPLine3d->getDistAtParam(endParam, length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 0; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pPLine3d->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	AcGePoint3d endPoint;
	_pPLine3d->getPointAtParam(endParam, endPoint);
	arrayPoints.append(endPoint);

	acutPrintf(_T("Built the points using PLine3DFrameBuilder  ...\n"));


}

void PLine3DFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using PLine3DFrameBuilder  ...\n"));
	
}

void PLine3DFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using PLine3DFrameBuilder  ...\n"));
	
}