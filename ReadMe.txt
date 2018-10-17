因工作需要，VingCard门锁提供的dll文件，java调用后无法正常的发门卡，故采用C++封装一层
其中C++里实现了Socket连接与VingCard的Socket服务端。
然后再用java调用自己封装的该VingCardXMS.dll来调用实现正常的发房卡操作。


========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : VingCardXMS
========================================================================


AppWizard has created this VingCardXMS DLL for you.  This DLL not only
demonstrates the basics of using the Microsoft Foundation classes but
is also a starting point for writing your DLL.

This file contains a summary of what you will find in each of the files that
make up your VingCardXMS DLL.

VingCardXMS.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

VingCardXMS.h
	This is the main header file for the DLL.  It declares the
	CVingCardXMSApp class.

VingCardXMS.cpp
	This is the main DLL source file.  It contains the class CVingCardXMSApp.


VingCardXMS.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

VingCardXMS.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\VingCardXMS.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.

VingCardXMS.def
    This file contains information about the DLL that must be
    provided to run with Microsoft Windows.  It defines parameters
    such as the name and description of the DLL.  It also exports
	functions from the DLL.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named VingCardXMS.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
