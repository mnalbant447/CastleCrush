// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ammunition.h"
#include "Camera/CameraComponent.h"
#include "Slingshot.generated.h"

UCLASS()
class ASlingshot : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASlingshot();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	float ForceConstant = 1000.0f;

	UPROPERTY(VisibleAnywhere)
	bool bHasAmmo = false;

	UPROPERTY(VisibleAnywhere, Category = Slingshot)
	AAmmunition* ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Slingshot)
	UCameraComponent* Camera;

	// Third person camera location and rotation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	FVector CameraThirdPersonLocation = FVector(1000.0f, 1900.0f, 0.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	FRotator CameraThirdPersonRotation = FRotator(0.0f, -90.0f, 0.0f);

	// First person camera location and rotation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	FVector CameraFirstPersonLocation = FVector(-370.0f, 0.0f, 100.0f);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	FRotator CameraFirstPersonRotation = FRotator(-20.0f, 0.0f, 0.0f);

	const FRotator CameraFirstPersonRotationCopy = CameraFirstPersonRotation;
	const FRotator CameraThirdPersonRotationCopy = CameraThirdPersonRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SlingshotMesh)
	UStaticMeshComponent* SlingshotMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Slingshot)
	bool bCameraAngle = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	float CameraPitchMultiplier = 1.20f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	float CameraYawMultiplier = 1.20f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	float MaxPitchAngle = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Slingshot)
	float MaxYawAngle = 25.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Slingshot)
	float InitialCameraRotationYaw = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Slingshot)
	float InitialCameraRotationPitch = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AcceptAmmunition(AAmmunition ammo);

	void FireAmmunition(AAmmunition ammo);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	float InputPitch = 0.0f;
	float InputYaw = 0.0f;
	bool CameraRotationFirstPersonChecked = false;
	bool CameraRotationThirdPersonChecked = true;

	void ChangeCamera()
	{
		bCameraAngle = !bCameraAngle;
	}

	void CameraPitch(float pitchValue )
	{
		InputPitch =  pitchValue;
	}

	void  CameraYaw(float yawValue)
	{
		InputYaw = yawValue;
	}

	void RotateCameraPitch(FRotator& CameraRotation)
	{
		
		if (CameraRotation.Pitch <= (InitialCameraRotationPitch + MaxPitchAngle) 
			&& CameraRotation.Pitch >= (InitialCameraRotationPitch -MaxPitchAngle))
		{
			CameraRotation += FRotator(CameraPitchMultiplier * InputPitch, 0.0f, 0.0f);
		}
		else if(CameraRotation.Pitch > (InitialCameraRotationPitch + MaxPitchAngle) 
				&& InputPitch < 0.0f)
		{
			CameraRotation += FRotator(CameraPitchMultiplier * InputPitch, 0.0f, 0.0f);
		} 
		else if (CameraRotation.Pitch < (InitialCameraRotationPitch - MaxPitchAngle) 
				&& InputPitch > 0.0f)
		{
			CameraRotation += FRotator(CameraPitchMultiplier * InputPitch, 0.0f, 0.0f);
		}
		
		


	}

	void RotateCameraYaw(FRotator& CameraRotation)
	{

		if (CameraRotation.Yaw <= (InitialCameraRotationYaw + MaxYawAngle)
			&& CameraRotation.Yaw >= (InitialCameraRotationYaw - MaxYawAngle))
		{
			CameraRotation += FRotator(0.0f, CameraYawMultiplier * InputYaw, 0.0f);
		}
		else if (CameraRotation.Yaw > (InitialCameraRotationYaw + MaxYawAngle)
			&& InputYaw < 0.0f)
		{
			CameraRotation += FRotator(0.0f, CameraYawMultiplier * InputYaw, 0.0f);

		}
		else if (CameraRotation.Yaw < (InitialCameraRotationYaw - MaxYawAngle)
			&& InputYaw > 0.0f)
		{
			CameraRotation += FRotator(0.0f, CameraYawMultiplier * InputYaw, 0.0f);
		}


		//UE_LOG(LogTemp, Warning, TEXT("Camera inital yaw value is: %f"), InitialCameraRotationYaw);

		UE_LOG(LogTemp, Warning, TEXT("Camera yaw value is: %f"), CameraRotation.Yaw);
	}
};
