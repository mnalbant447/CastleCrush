// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Slingshot.h"
#include "SlingshotBase.generated.h"

UCLASS()
class ASlingshotBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlingshotBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SlingshotBase)
	UStaticMeshComponent* SlingshotBaseMesh;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
