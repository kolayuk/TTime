/*
========================================================================
 Name        : MainView.cpp
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
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <TTime.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "TTime.hrh"
#include "MainView.h"
#include "Main.hrh"
#include "Main.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <aknquerydialog.h>
#include <TTimeAppUi.h>
#include <apgcli.h>
/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CMainView::CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CMainView::~CMainView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iMain;
	iMain = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewL()
	{
	CMainView* self = CMainView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CMainView
 */
CMainView* CMainView::NewLC()
	{
	CMainView* self = new ( ELeave ) CMainView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CMainView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_MAIN_MAIN_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CMainView::Id() const
	{
	return TUid::Uid( EMainViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CMainView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EMainViewControlPaneRightId:
			commandHandled = RightSoft( aCommand );
			break;
		case EMainView_MenuItemCommand:
			commandHandled = Edit( aCommand );
			break;
		case EMainView_MenuItem1Command:
			commandHandled = Other( aCommand );
			break;
		case EMainView_MenuItem2Command:
			commandHandled = About( aCommand );
			break;
		case EMainView_MenuItem3Command:
			commandHandled = Exit( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EMainViewControlPaneRightId )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CMainView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
				
	
	if ( iMain == NULL )
		{
		iMain = CreateContainerL();
		iMain->SetMopParent( this );
		AppUi()->AddToStackL( *this, iMain );
		} 
	// ]]] end generated region [Generated Contents]
	Init();
	}

/**
 */
void CMainView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iMain != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iMain );
		delete iMain;
		iMain = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CMainView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CMainView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_MAIN_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CMainView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CMain::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CMain
 */
CMain* CMainView::CreateContainerL()
	{
	return CMain::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::RightSoft( TInt aCommand )
	{
	CEikonEnv::Static()->RootWin().SetOrdinalPosition(-4);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Edit( TInt aCommand )
	{
	HandleLBSelect(iMain->ListBox()->CurrentItemIndex());
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Other( TInt aCommand )
	{
	TBuf<255> url(_L("http://store.ovi.com/content/98029"));
	OpenBrowser(url);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::About( TInt aCommand )
	{
	TBuf<1024> header;
	CEikonEnv::Static()->ReadResource(header,R_ABOUT_HEADER);
	TBuf<1024> txt;
	CEikonEnv::Static()->ReadResource(txt,R_ABOUT_TEXT);
	txt.Append(_L("WMR R321502538916\nWMZ Z208634876649\nWMU U221598315212\nWME E234802202031\nYandex-Money: 41001686491180"));
	((CTTimeAppUi*)AppUi())->GlobalMsgQuery(txt,header);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CMainView::Exit( TInt aCommand )
	{
	AppUi()->Exit();
	return ETrue;
	}
void CMainView::HandleLBSelect(TInt aIndex)
	{
	TBuf<255> title(GetTitle(aIndex));
	TBuf<255> subtitle;
	TInt val=((CTTimeAppUi*)AppUi())->iSettings[aIndex];
	if (!NumberQuery(title,val)){return;}
	((CTTimeAppUi*)AppUi())->iSettings[aIndex]=val;
	subtitle.Num(val);
	((CTTimeAppUi*)AppUi())->WriteSettings();
	((CTTimeAppUi*)AppUi())->Update();
	ChangeItemSubtitle(aIndex,subtitle);
	}

TPtrC CMainView::GetTitle(TInt aIndex)
	{
	TBuf<255> prev = iMain->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t';
	prev.Copy(prev.Right(prev.Length()-1));
	TInt pos = prev.Find(_L("\t"));
	return prev.Left(pos);
	}
void CMainView::ChangeItemSubtitle(TInt aIndex,TDes16& aText)
	{
	TBuf<512> buf;
	TBuf<255> t; t.Copy(GetTitle(aIndex));
	iMain->CreateListBoxItemL(buf,t,aText);
	CDesCArray* itemArray = static_cast<CDesCArray*> (iMain->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(aIndex);
	itemArray->InsertL(aIndex,buf);
	iMain->ListBox()->DrawNow();
	}
TInt CMainView::NumberQuery(TDes& aText,TInt& aNumber)
{
	CAknNumberQueryDialog* Dialog = CAknNumberQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_NUMBER_QUERY);
	Dialog->SetPromptL(aText);
	return Dialog->RunLD();	
}
void CMainView::Init()
	{
	TBuf<255> val; 
	for (TInt i=0;i<((CTTimeAppUi*)AppUi())->iSettings.Count();i++)
		{
		val.Num(((CTTimeAppUi*)AppUi())->iSettings[i]);
		ChangeItemSubtitle(i,val);
		}
	}

#ifndef __WINS__
	const TInt KBrowserUid = 0x10008D39;
#else
	const TInt KBrowserUid = 0x1020724D;
#endif

	void CMainView::OpenBrowser(const TDesC& aUrl)
	{
		TUid id(TUid::Uid(KBrowserUid));
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task = taskList.FindApp(id);

		if (task.Exists())
		{
			HBufC8* param8 = HBufC8::NewLC(100);
			param8->Des().Append(aUrl);
			// Uid is not used
			task.SendMessage(TUid::Uid(0), *param8);
			CleanupStack::PopAndDestroy();
		}
		else
		{
			RApaLsSession appArcSession;
			// connect to AppArc server
			User::LeaveIfError(appArcSession.Connect());
			TThreadId id;
			TInt ret = appArcSession.StartDocument(aUrl, TUid::Uid(KBrowserUid), id);
			appArcSession.Close();
		}
	}
