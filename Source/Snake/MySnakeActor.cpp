// Fill out your copyright notice in the Description page of Project Settings.

#include "Snake.h"
#include "MySnakeActor.h"


// Sets default values
AMySnakeActor::AMySnakeActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRootComponent = CreateDefaultSubobject<USphereComponent>("MyRoot");

	RootComponent = MyRootComponent;

	//����� ������ 
	FVector pos = GetActorLocation();

	//��������� �������������� ������ 
	MyRootComponent->SetRelativeLocation(pos);

	//������� ���� ����
	CreateBody();

	setVisibleChank();
}

// Called when the game starts or when spawned
void AMySnakeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMySnakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	setVisibleChank();

	BuferTime += DeltaTime;

	if (BuferTime > StepDeley)
	{
		MoveSnake();
		BuferTime = 0;
	}
}

void AMySnakeActor::setVisibleChank()
{
	for (int32 IndexShow = 0; IndexShow < SnakeBody.Num(); IndexShow++)
	{
		if(IndexShow < VisibleBodyChank)
		{
			SnakeBody[IndexShow]->SetVisibility(true, true);
		}
		else
		{
			SnakeBody[IndexShow]->SetVisibility(false, true);
		}
	}
}

void AMySnakeActor::CreateBody()
{
	class UStaticMesh* SnakeChankMesh;
	SnakeChankMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Sphere")).Object;

	//�������� ��� ���� ����  
	class UMaterialInstance * bodyColor;
	bodyColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/InstMaterial/M_Tech_Hex_Tile_Inst.M_Tech_Hex_Tile_Inst'")).Get();

	//�������� ��� ������ ����
	class UMaterialInstance * HeadColor;
	HeadColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/InstMaterial/M_Tech_Hex_Tile_Pulse_Inst.M_Tech_Hex_Tile_Pulse_Inst'")).Get();

	FName NameChank;
	FString TheString;

	//�������� ��������� ���������� ��� ���� ����
	FVector NextPoint = GetActorLocation();

	for (int32 i = 0; i < SnakeSize; i++)
	{
		TheString = "Chanks" + FString::FromInt(i);
		NameChank = FName(*TheString);

		//������� ����� ������ 
		class UStaticMeshComponent * BodyChank = CreateDefaultSubobject<UStaticMeshComponent>(NameChank);
		//������ ������ ����� �������� ����
		BodyChank->SetStaticMesh(SnakeChankMesh);
		
		//��������� ��������� ����� ����
		BodyChank->SetRelativeLocation(NextPoint);

		SnakeBody.Add(BodyChank);
	
		NextPoint.X -= StopSnake;
		
		//��������� ����� ���� � ��� ����������
		BodyChank->AttachTo(MyRootComponent);
		
		//������ ���� ����
		BodyChank->SetMaterial(0, bodyColor);
		 
		if (i == 0)
		{
			BodyChank->SetMaterial(0, HeadColor);
		}
		else
		{
			BodyChank->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

}

void AMySnakeActor::MoveSnake()
{
	//�-��� ����������� �������� ������ 
	if ((DerectionMoveSnake.X != 0) || (DerectionMoveSnake.Y != 0))
	{
		for (int chank = SnakeBody.Num() - 1; chank > 0; chank--)
		{
			FVector v = SnakeBody[chank]->RelativeLocation;
			//������ ������ ������� ��� ������
			SnakeBody[chank]->SetRelativeLocation(v);
		}
		//�������� ���������� ������
		FVector startPoint = SnakeBody[0]->RelativeLocation;
		if (DerectionMoveSnake.X > 0) startPoint.X -= StepSnake;
		if (DerectionMoveSnake.X < 0) startPoint.X += StepSnake;


		if (DerectionMoveSnake.Y > 0) startPoint.Y += StepSnake;
		if (DerectionMoveSnake.Y < 0) startPoint.Y -= StepSnake;

		///������������� ������� ��� ������
		SnakeBody[0]->SetRelativeLocation(startPoint);
	}
}

