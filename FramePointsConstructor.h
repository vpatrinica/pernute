#include "FramePointsBuilder.h"

class FramePointsConstructor
{
	public:
		FramePointsConstructor();
		~FramePointsConstructor();
		FramePointsConstructor(AcDbObjectIdArray*);
		void setBuilder(FramePointsBuilder*);
		Acad::ErrorStatus constructFramePoints(int);
		void getFramePoints(AcArray<AcGePoint3d>*);
		void printConstructedPoints();
		void setSetIds(AcDbObjectIdArray*);
		void getConstructedPointsAsArray();
		void getLinearArrayFramePoints(AcArray<AcGePoint3d>&, AcArray<int>&);
		int getNumberOfPoints();
	private:

		FramePointsBuilder* _builder;
	    AcDbObjectIdArray* _obArrayId;
		AcArray<AcGePoint3d>* _pointArray;
		int _lengthPointArray;
};