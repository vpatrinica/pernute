#include "LineFrameBuilder.h"

LineFrameBuilder::LineFrameBuilder()
{
	acutPrintf(_T("Constructor of LineFrameBuilder called ...\n"));

}

LineFrameBuilder::~LineFrameBuilder()
{
	acutPrintf(_T("Destructor of LineFrameBuilder called ...\n"));

}


void LineFrameBuilder::buildFramePoints(AcArray<AcGePoint3d>& arrayPoints, AcDbObjectPointer<AcDbEntity>& lineObject, int granularity)
{
	acutPrintf(_T("Building the points using LineFrameBuilder  ...\n"));
	_pLine = AcDbLine::cast(lineObject);
	arrayPoints.append(_pLine->startPoint());
	
	double length;
	_pLine->getDistAtPoint(_pLine->endPoint(), length);
	
	acutPrintf(_T("The length and other params: %f, %d, %d  ...\n"), length, ((int) length)/granularity, granularity);
	for (int i = 1; i< ((int) length)/granularity; i++)
	{
		
		AcGePoint3d newPoint;
		_pLine->getPointAtDist(i*granularity, newPoint);
		arrayPoints.append(newPoint); 
	}

	arrayPoints.append(_pLine->endPoint());

	acutPrintf(_T("Built the points using LineFrameBuilder  ...\n"));


}

void LineFrameBuilder::getFramePoints(AcArray<AcGePoint3d> &)
{
	acutPrintf(_T("Getting the points using LineFrameBuilder  ...\n"));
	
}

void LineFrameBuilder::printFramePoints()
{
	acutPrintf(_T("Printing the points using LineFrameBuilder  ...\n"));
	
}