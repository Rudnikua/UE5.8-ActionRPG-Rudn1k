#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

class UInputMappingContext;
class UInputAction;
class UAnimMontage;

class AItem;
class ASoul;
class ATreasure;

class UMainOverlay;

UCLASS()
class BP_UDEMYCPP_API AMainCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()
public:
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(class ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;
protected:
	virtual void BeginPlay() override;

	/* Callbacks for input */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();
	virtual void Attack() override;
	void Dodge();

	/* Combat */
	void EquipWeapon(AWeapon* Weapon);
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Arm();
	void PlayEquipMontage(const FName& SectionName);
	virtual void Die_Implementation() override;
	bool HasEnoughStamina();
	bool IsOccupied();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MainContext;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EKeyAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DodgeAction;

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();
private:
	bool IsUnoccuppied();
	void InitializeMainOverlay();
	void SetHUDHealth();

	/* Character Components */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* ViewCamera;
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY()
	UMainOverlay* MainOverlay;
public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState()  const { return ActionState; }
};
