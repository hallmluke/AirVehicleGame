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
	TurnRate = 1;
	BrakingTurnRateMultiplier = 3;
	TopSpeed = 300;
}

// Called when the game starts or when spawned
void AAirVehicle::BeginPlay()
{
	Super::BeginPlay();
	DefaultTurnRate = TurnRate;
}

void AAirVehicle::ClampSpeed()
{
	FVector CurrentVelocity = BoxComp->GetPhysicsLinearVelocity();
	FVector MaxVelocity = CurrentVelocity.GetClampedToMaxSize(TopSpeed);
	BoxComp->SetPhysicsLinearVelocity(MaxVelocity);
}

void AAirVehicle::StartBrake()
{
	bIsBraking = true;
}

void AAirVehicle::EndBrake()
{
	bIsBraking = false;
}

// Called every frame
void AAirVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//MeshComp->AddImpulse(GetActorForwardVector() * BaseSpeed);
	if (!bIsBraking) {
		BoxComp->AddForce(GetActorForwardVector() * BaseSpeed);
	}
	CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetRoll, DeltaTime, 10.0f);
	FRotator TargetRotation = GetActorRotation();
	TargetRotation.Yaw = CurrentYaw;
	SetActorRelativeRotation(TargetRotation);
	ClampSpeed();


	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Current Yaw: %f"), CurrentYaw));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Actor Rotation: %f"), GetActorRotation().Yaw));
	
}

// Called to bind functionality to input
void AAirVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &AAirVehicle::Turn);
	PlayerInputComponent->BindAction("Action1", IE_Pressed, this, &AAirVehicle::StartBrake);
	PlayerInputComponent->BindAction("Action1", IE_Released, this, &AAirVehicle::EndBrake);
}

void AAirVehicle::Turn(float Value) {
	float AppliedTurnRate;
	if (bIsBraking) {
		AppliedTurnRate = DefaultTurnRate * BrakingTurnRateMultiplier;
	}
	else {
		AppliedTurnRate = DefaultTurnRate;
	}
	TargetRoll += Value * AppliedTurnRate;
	/*FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value;
	AddActo*/
}