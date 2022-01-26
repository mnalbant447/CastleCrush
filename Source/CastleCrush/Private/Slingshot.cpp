// Fill out your copyright notice in the Description page of Project Settings.


#include "Slingshot.h"
#include "GameFramework/PlayerInput.h"
#include "Components/InputComponent.h"

// Sets default values
ASlingshot::ASlingshot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	SetRootComponent(RootComponent);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	
	SlingshotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlingshotBaseMesh"));
	SlingshotMesh->SetupAttachment(GetRootComponent());


	

}

// Called when the game starts or when spawned
void ASlingshot::BeginPlay()
{
	Super::BeginPlay();
	
	Camera->SetRelativeLocationAndRotation(CameraThirdPersonLocation, CameraThirdPersonRotation);
	
	InitialCameraRotationYaw = CameraThirdPersonRotation.Yaw;
	InitialCameraRotationPitch = CameraThirdPersonRotation.Pitch;

}

// Called every frame
void ASlingshot::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	if (bCameraAngle == true)
	{
		Camera->SetRelativeLocationAndRotation(CameraThirdPersonLocation, CameraThirdPersonRotation);
		RotateCameraPitch(CameraThirdPersonRotation);
		RotateCameraYaw(CameraThirdPersonRotation);
		
		if (CameraRotationThirdPersonChecked == false)
		{
			InitialCameraRotationYaw = CameraThirdPersonRotationCopy.Yaw;
			InitialCameraRotationPitch = CameraThirdPersonRotationCopy.Pitch;
			
			CameraRotationThirdPersonChecked = true;
		}

		CameraRotationFirstPersonChecked = false;
	}
	else 
	{

		Camera->SetRelativeLocationAndRotation(CameraFirstPersonLocation, CameraFirstPersonRotation);
		RotateCameraYaw(CameraFirstPersonRotation);
		RotateCameraPitch(CameraFirstPersonRotation);
		if (CameraRotationFirstPersonChecked == false)
		{
			InitialCameraRotationYaw = CameraFirstPersonRotationCopy.Yaw;
			InitialCameraRotationPitch = CameraFirstPersonRotationCopy.Pitch;

			CameraRotationFirstPersonChecked  =  true;
		}
		
		CameraRotationThirdPersonChecked = false;
	}

}
/*
Establish the default pawn input bindings for the slingshot.
*/
static void InitializeDefaultPawnInputBindings()
{
	static bool bindingsAdded = false;

	if (bindingsAdded == false)
	{
		bindingsAdded = true;

		UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("SlingShot_ChangeCamera", EKeys::C));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(("Slingshot_CameraPitch"), EKeys::MouseY, 1.0f));
		UPlayerInput::AddEngineDefinedAxisMapping(FInputAxisKeyMapping(("Slingshot_CameraYaw"), EKeys::MouseX, 1.0f));

	}

}

// Called to bind functionality to input
void ASlingshot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent != nullptr);
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InitializeDefaultPawnInputBindings();

	PlayerInputComponent->BindAction("SlingShot_ChangeCamera", EInputEvent::IE_Pressed, this, &ASlingshot::ChangeCamera);
	PlayerInputComponent->BindAxis("Slingshot_CameraPitch", this, &ASlingshot::CameraPitch);
	PlayerInputComponent->BindAxis("Slingshot_CameraYaw", this, &ASlingshot::CameraYaw);
}

// Function for attaching an ammuniton to the slingshot.
void AcceptAmmunition(AAmmunition ammo)
{

}

// Function for firing the ammunition from the slingshot.
// Take player input, calculate a vector from initial location and final location, fire the ammuniton based on the length of...
// the vector and a force constant.

void FireAmmunition(AAmmunition ammo)
{

}

