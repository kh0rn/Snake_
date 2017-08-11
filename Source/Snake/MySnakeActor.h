// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MySnakeActor.generated.h"

UCLASS()
class SNAKE_API AMySnakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySnakeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Максимальная дляина змеи
	int32 SnakeSize = 15;

	//ширина шага для тела змеи
	float StopSnake = 45.f;

	//рут компонент
	USphereComponent* MyRootComponent;
	
	//массив который хранит тело змеи
	TArray<UStaticMeshComponent *> SnakeBody;
	
	//кол-во выводимых частей змейки
	UPROPERTY(EditAnywhere) int32 VisibleBodyChank = 3;

	void setVisibleChank();
	void CreateBody();

	//направление движения
	UPROPERTY(EditAnywhere) FVector2D DerectionMoveSnake;

	float StepDeley = 0.5f;
	
	float StepSnake = 45.f;

	//буфер для время задержки 
	float BuferTime = 0;

	void MoveSnake();
};
