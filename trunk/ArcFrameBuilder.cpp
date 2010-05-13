
#include "ArcFrameBuilder.h"

ArcFrameBuilder::ArcFrameBuilder()
{
	acutPrintf(_T("Constructor of ArcFrameBuilder called ...\n"));

}

ArcFrameBuilder::~ArcFrameBuilder()
{
	acutPrintf(_T("Destructor of ArcFrameBuilder called ...\n"));

}


void ArcFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& ArcObject, int granularity)
{
	acutPrintf(_T("Building the points using ArcFrameBuilder  ...\n"));
	_pArc = AcDbArc::cast(ArcObject);
	
	AcGePoint3d startPoint;
	_pArc->getStartPoint(startPoint);
	arrayPoints.append(startPoint);
	
	
	double length, endParam = 0;
	
	_pArc->getEndParam(endParam);

	_pArc->getDistAtParam(endParam, length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 0; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pArc->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	AcGePoint3d endPoint;
	_pArc->getPointAtParam(endParam, endPoint);
	arrayPoints.append(endPoint);

	acutPrintf(_T("Built the points using ArcFrameBuilder  ...\n"));


}

void ArcFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using ArcFrameBuilder  ...\n"));
	
}

void ArcFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using ArcFrameBuilder  ...\n"));
	
}