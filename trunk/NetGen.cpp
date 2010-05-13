

/*DHVJX-4BKHH-KT7P7-46JVK-TKV4Y
*/


#include "NetGen.h"


ACRX_DXF_DEFINE_MEMBERS(NetGen, AcDbEntity, AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 0, NetGen, AcGiMesh Sample)


Acad::ErrorStatus NetGen::subTransformBy(const AcGeMatrix3d &xfm)
{
    return Acad::eOk;
}

Acad::ErrorStatus NetGen::outputNet()
{
	return Acad::eOk;

}

NetGen::~NetGen()
{
	delete _inputReader;
	delete _fpConstructor;
	delete _ipConstructor;
}

NetGen::NetGen()
{
	std::cout<<"Constructor called\n";
	_inputReader = new InputReader();
	_fpConstructor = new FramePointsConstructor();
	_ipConstructor = new InteriorPointsConstructor();
}

Adesk::Boolean
NetGen::subWorldDraw(AcGiWorldDraw* pW)
{
	NetGen::outputNet();
	return Adesk::kTrue;
}


void NetGen::readInput()
{
	
	CResbufPtr pFilter (acutBuildList(RTDXF0,ACRX_T("POINT,LINE,LWPOLYLINE,SPLINE"),NULL));
	
	
	acutPrintf(_T("Creating a reference to the new InputReader in readInput()..."));
	
	AcDbObjectIdArray inputObjectsArray;



	_inputReader->readInputSelectionSet(pFilter);
	_inputReader->getAsArray(inputObjectsArray);
	
	int i = 0;
	
	while (i<inputObjectsArray.length())
	{
		acutPrintf(_T("Can access the object %d\n"), i);
		i++;
	}
	acutPrintf(_T("Proceeding to the builder pattern, constructing poins..\n"));
	
	processInput(inputObjectsArray);
	

		
	return;
}

Acad::ErrorStatus NetGen::processInput(AcDbObjectIdArray& ssIds)
{
	acutPrintf(_T("processInput() called ...\n"));
	
	acutPrintf(_T("Registering a constructor of points ...\n"));

	_fpConstructor->setSetIds(&ssIds);
	
	acutPrintf(_T("Starting the construction of the points ...\n"));
	
	_fpConstructor->constructFramePoints(50); 
	//TODO: check loop consistency -- DONE
	//determinat centrul de greutate
	//de construit primele linii
	//radial de construit celelalte linii laterale

	//_fpConstructor->printConstructedPoints();
	AcArray<AcGePoint3d> _linArrayFrame;// = new AcArray<AcGePoint3d> [_fpConstructor->getNumberOfPoints()];
	AcArray<int> _linArrayFrameLengths;
	_fpConstructor->getLinearArrayFramePoints(_linArrayFrame, _linArrayFrameLengths);
	
	_ipConstructor->setContour(&_linArrayFrame);
	
	//_ipConstructor->constructInteriorPoints();
	_ipConstructor->makePolyhedron();
	//_ipConstructor->printInteriorPoints(2);
	//_ipConstructor->ForceDirectedAlgorithm();
	//_ipConstructor->printInteriorPoints(3);
	//_ipConstructor->printFirstInteriorPoints(3, true);
	//_ipConstructor->printInteriorPoints(3, true);
	//_ipConstructor->ForceDirectedAlgorithm2();
	//_ipConstructor->printFirstInteriorPoints(4, true);
	//_ipConstructor->printInteriorPoints(4, true);
	//_ipConstructor->PrintContourPoints();
	//_ipConstructor->printInteriorPoints2();
	acutPrintf(_T("Stopping program...\n"));
	return Acad::eOk;
}



