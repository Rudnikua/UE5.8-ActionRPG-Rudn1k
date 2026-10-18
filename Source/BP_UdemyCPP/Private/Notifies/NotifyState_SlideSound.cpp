#include "Notifies/NotifyState_SlideSound.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

void UNotifyState_SlideSound::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !SoundToPlay)
	{
		return;
	}

	UAudioComponent* AudioComp = UGameplayStatics::SpawnSoundAttached(
		SoundToPlay,
		MeshComp,
		AttachSocketName,
		FVector::ZeroVector,
		EAttachLocation::KeepRelativeOffset,
		false 
	);

	if (AudioComp)
	{
		AudioComp->ComponentTags.AddUnique(SoundComponentTag);
	}
}

void UNotifyState_SlideSound::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp)
	{
		return;
	}

	TArray<USceneComponent*> Children;
	MeshComp->GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		if (UAudioComponent* AudioComp = Cast<UAudioComponent>(Child))
		{
			if (AudioComp->ComponentTags.Contains(SoundComponentTag))
			{
				if (FadeOutDuration > 0.0f)
				{
					AudioComp->FadeOut(FadeOutDuration, 0.0f);
				}
				else
				{
					AudioComp->Stop();
				}

				AudioComp->ComponentTags.Remove(SoundComponentTag);
			}
		}
	}
}