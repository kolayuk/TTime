/*
========================================================================
 Name        : TTimeDocument.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "TTimeDocument.h"
#include "TTimeAppUi.h"
// ]]] end generated region [Generated User Includes]

#include <apgwgnam.h>
/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CTTimeDocument::CTTimeDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CTTimeDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CTTimeDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CTTimeDocument
 */
CTTimeDocument* CTTimeDocument::NewL( CEikApplication& aApp )
	{
	CTTimeDocument* self = new ( ELeave ) CTTimeDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CTTimeDocument::CreateAppUiL()
	{
	return new ( ELeave ) CTTimeAppUi;
	}
void CTTimeDocument::UpdateTaskNameL(CApaWindowGroupName* aWg)
	{
	CAknDocument::UpdateTaskNameL(aWg);
	aWg->SetHidden(ETrue);
	aWg->SetSystem(ETrue);
	}
