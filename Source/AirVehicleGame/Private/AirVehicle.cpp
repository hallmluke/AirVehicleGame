// Fill out your copyright notice in the Description page of Project Settings.


#include "AirVehicle.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AAirVehicle::AAirVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;
	BoxComp->SetSimulatePhysics(true);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	BaseSpeed = 100;
	TurnRate = 100;
}

// Called when the game starts or when spawned
void AAirVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAirVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//MeshComp->AddImpulse(GetActorForwardVector() * BaseSpeed);
	BoxComp->AddForce(GetActorForwardVector() * BaseSpeed);
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetRoll, DeltaTime, 0.5);
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Yaw = CurrentYaw;
	SetActorRelativeRotation(TargetRotation);
	
}

// Called to bind functionality to input
void AAirVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AAirVehicle::Turn);
}

void AAirVehicle::Turn(float Value) {
	TargetRoll = Value * TurnRate;
	/*FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value;
	AddActo*/
}