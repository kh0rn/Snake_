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

	//место актера 
	FVector pos = GetActorLocation();

	//указываем местоположение актеру 
	MyRootComponent->SetRelativeLocation(pos);

	//создаем тело змеи
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

	//материал для тела змеи  
	class UMaterialInstance * bodyColor;
	bodyColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/InstMaterial/M_Tech_Hex_Tile_Inst.M_Tech_Hex_Tile_Inst'")).Get();

	//материал для головы змеи
	class UMaterialInstance * HeadColor;
	HeadColor = ConstructorHelpers::FObjectFinderOptional<UMaterialInstance>(TEXT("MaterialInstanceConstant'/Game/SnakeContent/InstMaterial/M_Tech_Hex_Tile_Pulse_Inst.M_Tech_Hex_Tile_Pulse_Inst'")).Get();

	FName NameChank;
	FString TheString;

	//получаем начальные координаты для тела змеи
	FVector NextPoint = GetActorLocation();

	for (int32 i = 0; i < SnakeSize; i++)
	{
		TheString = "Chanks" + FString::FromInt(i);
		NameChank = FName(*TheString);

		//создаем часть змейки 
		class UStaticMeshComponent * BodyChank = CreateDefaultSubobject<UStaticMeshComponent>(NameChank);
		//задаем модель сферы компонту змеи
		BodyChank->SetStaticMesh(SnakeChankMesh);
		
		//назначаем положение части тела
		BodyChank->SetRelativeLocation(NextPoint);

		SnakeBody.Add(BodyChank);
	
		NextPoint.X -= StopSnake;
		
		//добавляем часть тела к рут компоненте
		BodyChank->AttachTo(MyRootComponent);
		
		//задаем сцен телу
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
	//ф-ция поисывающая движение змейки 
	if ((DerectionMoveSnake.X != 0) || (DerectionMoveSnake.Y != 0))
	{
		for (int chank = SnakeBody.Num() - 1; chank > 0; chank--)
		{
			FVector v = SnakeBody[chank]->RelativeLocation;
			//задаем новыую позицию для хвоста
			SnakeBody[chank]->SetRelativeLocation(v);
		}
		//получаем координаты головы
		FVector startPoint = SnakeBody[0]->RelativeLocation;
		if (DerectionMoveSnake.X > 0) startPoint.X -= StepSnake;
		if (DerectionMoveSnake.X < 0) startPoint.X += StepSnake;


		if (DerectionMoveSnake.Y > 0) startPoint.Y += StepSnake;
		if (DerectionMoveSnake.Y < 0) startPoint.Y -= StepSnake;

		///устанавливаем позицию для головы
		SnakeBody[0]->SetRelativeLocation(startPoint);
	}
}

