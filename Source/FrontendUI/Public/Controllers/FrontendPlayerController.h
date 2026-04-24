// Daniel E. I. Sasaki All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FrontendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API AFrontendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//~ Begin APlayerController
	virtual void OnPossess(APawn* aPawn) override;
	//~ End APlayerController
};
