#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SlideSound.generated.h"

class USoundBase;

UCLASS()
class BP_UDEMYCPP_API UNotifyState_SlideSound : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Sound")
	TObjectPtr<USoundBase> SoundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Sound")
	FName AttachSocketName = FName("root");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Sound", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float FadeOutDuration = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide Sound")
	FName SoundComponentTag = FName("ActiveSlideSound");
};