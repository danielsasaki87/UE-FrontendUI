// Daniel E. I. Sasaki All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OptionsDataRegistry.generated.h"

class UListDataObject_Collection;
/**
 * Used to store all the choices of each tab in the Options Screen
 */
UCLASS()
class FRONTENDUI_API UOptionsDataRegistry : public UObject
{
	GENERATED_BODY()
	
public:
	// Gets called by options screen right after the object UOptionsDataRegistry is created
	void InitOptionsDataRegistry(ULocalPlayer* InOwningLocalPlayer);

	const TArray<UListDataObject_Collection*>& GetRegisteredOptionsTabCollections() const
	{
		return RegisteredOptionsTabCollections;
	}
	
private:
	void InitGameplayCollectionTab();
	void InitAudioCollectionTab();
	void InitVideoCollectionTab();
	void InitControlCollectionTab();
	
	UPROPERTY(Transient)
	TArray<UListDataObject_Collection*> RegisteredOptionsTabCollections;
	
	// Helper to stamp out a new collection
	UListDataObject_Collection* CreateTabCollection(FName DataID, FText DisplayName);
};
