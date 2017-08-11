// Fill out your copyright notice in the Description page of Project Settings.

#include "Snake.h"
#include "MyDethActor.h"


// Sets default values
AMyDethActor::AMyDethActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyDethActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyDethActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

