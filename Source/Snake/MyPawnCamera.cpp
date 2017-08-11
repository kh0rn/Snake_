// Fill out your copyright notice in the Description page of Project Settings.

#include "Snake.h"
#include "MyPawnCamera.h"


// Sets default values
AMyPawnCamera::AMyPawnCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//запомним коренвой эелемент для камеры
	MyRootComponent = CreateDefaultSubobject<UBoxComponent>("RootModel");
	//добавим блок пешке
	RootComponent = MyRootComponent;

	//создадим штатив для камеры
	CameraSpring = CreateDefaultSubobject<USpringArmComponent>("Spring");
	//указываем позицию штатива 
	CameraSpring->SetRelativeLocation(FVector(0, 0, 0));
	//присоеденияем к рут компоненту камеру
	CameraSpring->AttachTo(MyRootComponent);

	//создаем камеру
	MyCamera = CreateDefaultSubobject<UCameraComponent>("camera");
	//присоеденить камеру к штативу
	MyCamera->AttachTo(CameraSpring, USpringArmComponent::SocketName);

	//поворот штатива
	CameraSpring->SetRelativeRotation(FRotator(-90.f, 0, 0));
	//устанавлиема длину штатива
	CameraSpring->TargetArmLength = 1700.f;
	//отключаем коллизию
	CameraSpring->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void AMyPawnCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawnCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

