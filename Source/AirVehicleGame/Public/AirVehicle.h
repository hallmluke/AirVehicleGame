// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AirVehicle.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;

UCLASS()
class AIRVEHICLEGAME_API AAirVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAirVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ground Movement")
	float BaseSpeed;

	void Turn(float Value);

	float TargetRoll;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ground Movement")
	float TurnRate;

	float CurrentYaw;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
