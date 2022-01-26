// Fill out your copyright notice in the Description page of Project Settings.


#include "SlingshotBase.h"

// Sets default values
ASlingshotBase::ASlingshotBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SlingshotBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlingshotBaseMesh"));

	SetRootComponent(SlingshotBaseMesh);

	SlingshotBaseMesh->SetSimulatePhysics(true);
	

}

// Called when the game starts or when spawned
void ASlingshotBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlingshotBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

