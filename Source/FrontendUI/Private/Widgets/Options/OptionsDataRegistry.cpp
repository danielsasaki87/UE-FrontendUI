// Daniel E. I. Sasaki All Rights Reserved


#include "Widgets/Options/OptionsDataRegistry.h"
#include "Widgets/Options/DataObjects/ListDataObject_Collection.h"

void UOptionsDataRegistry::InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer)
{
	InitGameplayCollectionTab();
	InitAudioCollectionTab();
	InitVideoCollectionTab();
	InitControlCollectionTab();
}

UListDataObject_Collection* UOptionsDataRegistry::CreateTabCollection(FName DataID, FText DisplayName)
{
	UListDataObject_Collection* NewTab = NewObject<UListDataObject_Collection>(this);
	NewTab->SetDataID(DataID);
	NewTab->SetDataDisplayName(DisplayName);
    
	return NewTab;
}

void UOptionsDataRegistry::InitGameplayCollectionTab()
{
	RegisteredOptionsTabCollections.Add(
CreateTabCollection(FName("GameplayTabCollection"), FText::FromString("Gameplay"))
	);
}

void UOptionsDataRegistry::InitAudioCollectionTab()
{
	RegisteredOptionsTabCollections.Add(
	CreateTabCollection(FName("AudioTabCollection"), FText::FromString("Audio"))
	);
}

void UOptionsDataRegistry::InitVideoCollectionTab()
{
	RegisteredOptionsTabCollections.Add(
	CreateTabCollection(FName("VideoTabCollection"), FText::FromString("Video"))
	);
}

void UOptionsDataRegistry::InitControlCollectionTab()
{
	RegisteredOptionsTabCollections.Add(
	CreateTabCollection(FName("ControlTabCollection"), FText::FromString("Control"))
	);
}
