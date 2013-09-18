/*
========================================================================
 Name        : TTimeAppUi.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2011

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <TTime.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "TTimeAppUi.h"
#include "TTime.hrh"
#include "MainView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <const.h>
#include <bautils.h>
#include <aknglobalmsgquery.h>
/**
 * Construct the CTTimeAppUi instance
 */ 
CTTimeAppUi::CTTimeAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CTTimeAppUi::~CTTimeAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

// [[[ begin generated function: do not modify
void CTTimeAppUi::InitializeContainersL()
	{
	iMainView = CMainView::NewL();
	AddViewL( iMainView );
	SetDefaultViewL( *iMainView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CTTimeAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CTTimeAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CTTimeAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CTTimeAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CTTimeAppUi::ConstructL()
	{
	ReadSettings();
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	Update();
	iTimer=CPeriodic::NewL(CActive::EPriorityHigh);
	iTimer->Start(1000000,1000000,TCallBack(Tick,this));
	HideApplicationFromFSW(ETrue);
	//HideInBackground();
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	}


void CTTimeAppUi::ReadSettings()
	{
	TInt err=KErrNone;
	iSettings.Reset();
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingPath)) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
		TBuf<255> val;
		RFile filesave;
		TBuf<10> t;
		TFileText ft;
		TUint32 IntVal;
		filesave.Open(CEikonEnv::Static()->FsSession(), KSettingPath, EFileRead);
		ft.Set(filesave);
		while (ft.Read(val)==KErrNone)
			{
			TLex conv(val);
			conv.Val(IntVal,EDecimal);
			iSettings.Append(IntVal);
			}
		filesave.Close();
		}
	else
		{
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(KSettingPath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{
			CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());
			}
		iSettings.Append(KPosX);
		iSettings.Append(KPosY);
		iSettings.Append(KWidth);
		iSettings.Append(KHeight);
		iSettings.Append(KRed);
		iSettings.Append(KGreen);
		iSettings.Append(KBlue);
		iSettings.Append(KTransparency);
		WriteSettings();
		}
	}
void CTTimeAppUi::WriteSettings()
	{
		RFs iFS=CEikonEnv::Static()->FsSession();
		RFile filesave;
		TInt err1=filesave.Replace(iFS, KSettingPath, EFileWrite);
		TFileText ft;
		ft.Set(filesave);
		TBuf<255> temp;
		for (TInt i=0;i<iSettings.Count();i++)
			{
			temp.Num(iSettings[i],EDecimal);
			ft.Write(temp);
			}
		filesave.Close();
	}
void CTTimeAppUi::Update()
	{
	if (iInfo){delete iInfo;}
	iInfo=CTopInfo::NewL(TPoint(iSettings[0],iSettings[1]),TSize(iSettings[2],iSettings[3]));
	iInfo->SetColor(TRgb(iSettings[4],iSettings[5],iSettings[6],iSettings[7]));
	iInfo->Show();
	}
TInt CTTimeAppUi::Tick(TAny* aObj)
	{
	TTime time; time.HomeTime();
	TBuf<255> t;
	time.FormatL(t,_L("%H:%T:%S"));
	((CTTimeAppUi*)aObj)->iInfo->Update(t);
	return 1;
	}
TBool CTTimeAppUi::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;		
	}
