#include "Characters/MainAnimInstance.h"
#include "Characters/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MainCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	if (MainCharacter)
	{
		MainCharacterMovement = MainCharacter->GetCharacterMovement();
	}
}

void UMainAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (MainCharacterMovement)
	{
		Velocity = MainCharacterMovement->Velocity;

		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);

		float threshold = 3.0f; // Define a threshold for movement
		ShouldMove = UKismetMathLibrary::NotEqual_VectorVector(MainCharacterMovement->GetCurrentAcceleration(), FVector::ZeroVector, .0f) && GroundSpeed > threshold;

		IsFalling = MainCharacterMovement->IsFalling();

		CharacterState = MainCharacter->GetCharacterState();
	}
}

