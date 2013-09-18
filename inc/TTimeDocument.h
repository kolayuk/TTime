/*
========================================================================
 Name        : TTimeDocument.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
#ifndef TTIMEDOCUMENT_H
#define TTIMEDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CTTimeDocument TTimeDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CTTimeDocument : public CAknDocument
	{
public: 
	// constructor
	static CTTimeDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CTTimeDocument( CEikApplication& aApp );
	void ConstructL();
	void UpdateTaskNameL(CApaWindowGroupName* aWg);
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // TTIMEDOCUMENT_H
