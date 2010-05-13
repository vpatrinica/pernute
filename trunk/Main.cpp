#pragma once
#include "NetGen.h"
#include "dbobjptr.h"


static void
initNetGen()
{
	Acad::ErrorStatus es;
    AcDbBlockTable   *pBlockTable;
    es = acdbHostApplicationServices()->workingDatabase()
        ->getSymbolTable(pBlockTable, AcDb::kForRead);
    if (es != Acad::eOk)
        return;

    AcDbBlockTableRecord *pBlock;
    es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBlock,
        AcDb::kForWrite);
    if (es != Acad::eOk)
        return;

	es = pBlock->close();
    
	if (es != Acad::eOk)
        acrx_abort(_T("\nUnable to close block table record"));

    es = pBlockTable->close();
    if (es != Acad::eOk) 
        acrx_abort(_T("\nUnable to close block table"));

	NetGen* myApp = new NetGen();
	acutPrintf(_T("Starting the program... courtesy of initNetGen()..."));
	myApp->readInput();
    //insert custom code;
    //acdbFail((const ACHAR *)"Failed to find the last index of start\n");
    
	delete myApp;
	
	
  

}



static void initNetGenApp()
{
    NetGen::rxInit();
    acrxBuildClassHierarchy();

    acedRegCmds->addCommand(_T("ACGI_NETGEN"),
                            _T("ASDKNETGEN"),
							_T("NETGEN"),
                            ACRX_CMD_TRANSPARENT,
                            initNetGen);
}


extern "C" AcRx::AppRetCode
acrxEntryPoint(AcRx::AppMsgCode msg, void* appId) 
{
    switch (msg) {
	case AcRx::kInitAppMsg:
        acrxDynamicLinker->unlockApplication(appId);
		acrxDynamicLinker->registerAppMDIAware(appId);
        initNetGenApp();
	    break;
	case AcRx::kUnloadAppMsg:
	    acedRegCmds->removeGroup(_T("ACGI_NETGEN"));
            deleteAcRxClass(NetGen::desc());
    }
    return AcRx::kRetOK;
}

