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

	//������������ ������ ����
	int32 SnakeSize = 15;

	//������ ���� ��� ���� ����
	float StopSnake = 45.f;

	//��� ���������
	USphereComponent* MyRootComponent;
	
	//������ ������� ������ ���� ����
	TArray<UStaticMeshComponent *> SnakeBody;
	
	//���-�� ��������� ������ ������
	UPROPERTY(EditAnywhere) int32 VisibleBodyChank = 3;

	void setVisibleChank();
	void CreateBody();

	//����������� ��������
	UPROPERTY(EditAnywhere) FVector2D DerectionMoveSnake;

	float StepDeley = 0.5f;
	
	float StepSnake = 45.f;

	//����� ��� ����� �������� 
	float BuferTime = 0;

	void MoveSnake();
};
