// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MySnakeActor.h"
#include "MyPawnCamera.generated.h"

UCLASS()
class SNAKE_API AMyPawnCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnCamera();
	AMySnakeActor mySnakeActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//корневой компонент
	UPROPERTY(EditAnywhere) class UBoxComponent* MyRootComponent;
	
	//штатив для камеры
	UPROPERTY(EditAnywhere) class USpringArmComponent*  CameraSpring;

	//камера персонажа
	UPROPERTY(EditAnywhere) class UCameraComponent* MyCamera;
	

};
