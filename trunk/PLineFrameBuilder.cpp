#include "PLineFrameBuilder.h"

PLineFrameBuilder::PLineFrameBuilder()
{
	acutPrintf(_T("Constructor of PLineFrameBuilder called ...\n"));

}

PLineFrameBuilder::~PLineFrameBuilder()
{
	acutPrintf(_T("Destructor of PLineFrameBuilder called ...\n"));

}


void PLineFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& plineObject, int granularity)
{
	acutPrintf(_T("Building the points using PLineFrameBuilder  ...\n"));
	_pPLine = AcDbPolyline::cast(plineObject);
	
	AcGePoint3d startPoint;
	_pPLine->getStartPoint(startPoint);
	arrayPoints.append(startPoint);
	
	
	double length, endParam = 0;
	
	_pPLine->getEndParam(endParam);

	_pPLine->getDistAtParam(endParam, length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 0; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pPLine->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	AcGePoint3d endPoint;
	_pPLine->getPointAtParam(endParam, endPoint);
	arrayPoints.append(endPoint);

	acutPrintf(_T("Built the points using PLineFrameBuilder  ...\n"));


}

void PLineFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using PLineFrameBuilder  ...\n"));
	
}

void PLineFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using PLineFrameBuilder  ...\n"));
	
}