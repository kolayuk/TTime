/*
 ============================================================================
 Name		: TopInfo.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CTopInfo implementation (window over all apps)
 ============================================================================
 */

#include "TopInfo.h"
#include <const.h>
#include <eikenv.h>
#include <aknutils.h>
#include <aknsutils.h>
CTopInfo::CTopInfo()
	{
	}

CTopInfo::~CTopInfo()
	{
	delete iText;
	iFont=NULL;
	delete iMaskGc;
	delete iMask;
	delete iBitGc;
	delete iBitmap;
	iSprite->Close();
	iWinGroup->Close();
	}

CTopInfo* CTopInfo::NewLC(TPoint aPos,TSize aSize)
	{
	CTopInfo* self = new (ELeave) CTopInfo();
	CleanupStack::PushL(self);
	self->ConstructL(aPos,aSize);
	return self;
	}

CTopInfo* CTopInfo::NewL(TPoint aPos,TSize aSize)
	{
	CTopInfo* self = CTopInfo::NewLC(aPos,aSize);
	CleanupStack::Pop(); // self;
	return self;
	}

void CTopInfo::ConstructL(TPoint aPos,TSize aSize)
	{
	
	MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	AknsUtils::GetCachedColor(skin,iColor,KAknsIIDQsnTextColors,EAknsCIQsnTextColorsCG6 );
	iTransparency=0;
	TTypefaceSupport iTypefaceSupport;
	TBuf<KMaxTypefaceNameLength> fontName;
	fontName.FillZ(KMaxTypefaceNameLength);
	CEikonEnv::Static()->ScreenDevice()->TypefaceSupport(iTypefaceSupport, 0);
	fontName = iTypefaceSupport.iTypeface.iName;
	
	TFontSpec FontSpec(fontName, aSize.iHeight);	
	FontSpec.iTypeface.SetIsProportional(ETrue);
	CEikonEnv::Static()->ScreenDevice()->GetNearestFontInPixels(iFont,FontSpec);
	
	//iFont=CEikonEnv::Static()->NormalFont();
	isVisible=EFalse;
	
	TBuf<15> temp;
	temp.Fill('P',15);
	iSize=TSize(iFont->TextWidthInPixels(temp),iFont->HeightInPixels());
	iPos=aPos;
	
	iBitmap=new(ELeave) CFbsBitmap();
	iMask=new (ELeave) CFbsBitmap();
		
	iBitmap->Create(iSize,EColor16M);
	iMask->Create(iSize,EColor16M);
		
	CFbsBitmapDevice* BitDevice=CFbsBitmapDevice::NewL(iBitmap);
	CFbsBitmapDevice* MaskDevice=CFbsBitmapDevice::NewL(iMask);
		
	BitDevice->CreateContext(iBitGc);
	MaskDevice->CreateContext(iMaskGc);
		
	iBitGc->UseFont(iFont);
	iMaskGc->UseFont(iFont);
	
	iWinGroup=new (ELeave) RWindowGroup(CEikonEnv::Static()->WsSession());
	iWinGroup->Construct((TUint32)iWinGroup);
	iWinGroup->EnableReceiptOfFocus(EFalse);
	iWinGroup->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
		
	iSprite= new (ELeave) RWsSprite(CEikonEnv::Static()->WsSession());
	iSprite->Construct(*iWinGroup,iPos,0);
	iMember.iBitmap=NULL;
	iMember.iMaskBitmap=NULL;
	iMember.iOffset=TPoint(0,0);
	iMember.iInterval=TTimeIntervalMicroSeconds32(0);
	iMember.iInvertMask=ETrue; // black - not transparadent, white - transparadent
	iSprite->AppendMember(iMember);
	iSprite->SetPosition(iPos);
	iSprite->Activate();
	CEikonEnv::Static()->WsSession().Flush();
	iText=HBufC::New(1024);
	Hide();
	Draw();
	}
void CTopInfo::Show()
	{
	isVisible=ETrue;
	iMember.iBitmap=iBitmap;
	iMember.iMaskBitmap=iMask;
	iSprite->UpdateMember(0,iMember);
	iSprite->SetPosition(iPos);
	CEikonEnv::Static()->WsSession().Flush();
	}

void CTopInfo::Hide()
	{
	isVisible=EFalse;
	iMember.iBitmap=NULL;
	iMember.iMaskBitmap=NULL;
	iSprite->SetPosition(iPos);
	iSprite->UpdateMember(0,iMember);
	CEikonEnv::Static()->WsSession().Flush();
	}
void CTopInfo::Draw()
	{	
	iBitGc->SetBrushColor(iColor);
	iBitGc->SetBrushStyle(CFbsBitGc::ESolidBrush);
	iBitGc->SetPenColor(iColor);
	iBitGc->DrawRect(TRect(-1,-1,iSize.iWidth+1,iSize.iHeight+1));
	iBitGc->SetBrushColor(iColor);
	iBitGc->SetBrushStyle(CFbsBitGc::ENullBrush);
	iBitGc->SetPenColor(iColor);
	iBitGc->UseFont(iFont);
	iBitGc->DrawText(*iText,TRect(0,0,iFont->TextWidthInPixels(*iText),iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);
		
	TRgb TransColor(iTransparency,iTransparency,iTransparency);
	iMaskGc->SetBrushColor(KRgbWhite);
	iMaskGc->SetBrushStyle(CFbsBitGc::ESolidBrush);
	iMaskGc->SetPenColor(KRgbWhite);
	iMaskGc->DrawRect(TRect(-1,-1,iSize.iWidth+1,iSize.iHeight+1));
	iMaskGc->SetPenColor(TransColor);
	iMaskGc->SetBrushColor(TransColor);
	iMaskGc->SetBrushStyle(CFbsBitGc::ENullBrush);
	iMaskGc->UseFont(iFont);
	iMaskGc->DrawText(*iText,TRect(0,0,iFont->TextWidthInPixels(*iText),iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);
	CEikonEnv::Static()->InfoMsg(iText->Des());
	if (isVisible)
		{
		iMember.iBitmap=iBitmap;
		iMember.iMaskBitmap=iMask;
		}
	
	iSprite->UpdateMember(0,iMember);
	iSprite->SetPosition(iPos);
	CEikonEnv::Static()->WsSession().Flush();
	}
void CTopInfo::Update(TDes& aText)
	{
	iText->Des().Copy(aText);
	Draw();
	}
void CTopInfo::SetColor(TRgb aColor)
	{
	iColor=TRgb(aColor.Red(),aColor.Green(),aColor.Blue());
	iTransparency=aColor.Alpha();
	Draw();
	}
