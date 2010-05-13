#pragma once
#include "FramePointsBuilder.h"
#include "dbents.h"

class LineFrameBuilder : public FramePointsBuilder
{

	public:
		LineFrameBuilder();

		virtual void buildFramePoints(AcArray<AcGePoint3d>&, AcDbObjectPointer<AcDbEntity>&, int);
		virtual void getFramePoints(AcArray<AcGePoint3d> &);
		virtual void printFramePoints();
		~LineFrameBuilder();
	
	private:
		AcDbLine * _pLine;

};