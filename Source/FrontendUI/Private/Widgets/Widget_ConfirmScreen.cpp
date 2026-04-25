// Daniel E. I. Sasaki All Rights Reserved


#include "Widgets/Widget_ConfirmScreen.h"
#include "CommonTextBlock.h"
#include "Components/DynamicEntryBox.h"
#include "Widgets/Components/FrontendCommonButtonBase.h"
#include "ICommonInputModule.h"

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateBaseInfoObject(const FText& InTitle, const FText& InMsg)
{
	UConfirmScreenInfoObject* InfoObject = NewObject<UConfirmScreenInfoObject>();
	InfoObject->ScreenTitle = InTitle;
	InfoObject->ScreenMessage = InMsg;
	return InfoObject;
}

FConfirmScreenButtonInfo UConfirmScreenInfoObject::CreateButton(
	EConfirmScreenButtonType ButtonType, 
	const FText& ButtonText)
{
	FConfirmScreenButtonInfo NewButton;
	NewButton.ConfirmScreenButtonType = ButtonType;
	NewButton.ButtonTextToDisplay = ButtonText;
	return NewButton;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOKScreen(const FText& InScreenTitle, const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InfoObject = CreateBaseInfoObject(InScreenTitle, InScreenMsg);
	
	InfoObject->AvailableScreenButtons.Add(
	CreateButton(EConfirmScreenButtonType::Closed, FText::FromString("Ok"))
	);
	
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateYesNoScreen(const FText& InScreenTitle,
	const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InfoObject = CreateBaseInfoObject(InScreenTitle, InScreenMsg);
	
	InfoObject->AvailableScreenButtons.Add(
	CreateButton(EConfirmScreenButtonType::Confirmed, FText::FromString("Yes"))
	);
	
	InfoObject->AvailableScreenButtons.Add(
	CreateButton(EConfirmScreenButtonType::Cancelled, FText::FromString("No"))
	);
	
	return InfoObject;
}

UConfirmScreenInfoObject* UConfirmScreenInfoObject::CreateOkCancelScreen(const FText& InScreenTitle,
	const FText& InScreenMsg)
{
	UConfirmScreenInfoObject* InfoObject = CreateBaseInfoObject(InScreenTitle, InScreenMsg);
	
	InfoObject->AvailableScreenButtons.Add(
	CreateButton(EConfirmScreenButtonType::Confirmed, FText::FromString("Ok"))
	);
	
	InfoObject->AvailableScreenButtons.Add(
	CreateButton(EConfirmScreenButtonType::Cancelled, FText::FromString("Cancel"))
	);
	
	return InfoObject;
}

void UWidget_ConfirmScreen::InitConfirmScreen(
	UConfirmScreenInfoObject* InScreenInfoObject,
	TFunction<void(EConfirmScreenButtonType)> ClickedButonCallback)
{
	check(InScreenInfoObject && CommonTextBlock_Title && CommonTextBlock_Message && DynamicEntryBox_Buttons);
	
	CommonTextBlock_Title->SetText(InScreenInfoObject->ScreenTitle);
	CommonTextBlock_Message->SetText(InScreenInfoObject->ScreenMessage);
	
	// Checking if the entry box has old button created previously
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		/**
		 *	Clearing the old buttons the entry box has. The widget type for the entry box 
		 *	is specified in the child widget blueprint.
		 */
		DynamicEntryBox_Buttons->Reset<UFrontendCommonButtonBase>(
			[](UFrontendCommonButtonBase& ExistingButton)
			{
				ExistingButton.OnClicked().Clear();
			}	
		);
	}
	
	check(!InScreenInfoObject->AvailableScreenButtons.IsEmpty());
	
	for (const FConfirmScreenButtonInfo& AvailableButtonInfo : InScreenInfoObject->AvailableScreenButtons)
	{
		FDataTableRowHandle InputActionRowHandle;
		
		switch (AvailableButtonInfo.ConfirmScreenButtonType)
		{
		case EConfirmScreenButtonType::Cancelled:
		case EConfirmScreenButtonType::Closed:
			InputActionRowHandle = ICommonInputModule::GetSettings().GetDefaultBackAction();
			break;
			
		default:
			break;
		}
		
		UFrontendCommonButtonBase* AddedButton = DynamicEntryBox_Buttons->CreateEntry<UFrontendCommonButtonBase>();
		AddedButton->SetButtonText(AvailableButtonInfo.ButtonTextToDisplay);
		AddedButton->SetTriggeringInputAction(InputActionRowHandle);
		AddedButton->OnClicked().AddLambda(
			[ClickedButonCallback, AvailableButtonInfo, this]()
			{
				ClickedButonCallback(AvailableButtonInfo.ConfirmScreenButtonType);
				
				DeactivateWidget();
			}
		);
	}
	
	if (DynamicEntryBox_Buttons->GetNumEntries() != 0)
	{
		DynamicEntryBox_Buttons->GetAllEntries().Last()->SetFocus();
	}
}