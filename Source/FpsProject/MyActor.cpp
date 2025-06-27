// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("I_AM_MESH1"));
	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("I_AM_MESH2"));

	RootComponent = Mesh1;
	Mesh2->SetupAttachment(RootComponent);

	Mesh2->SetRelativeLocation(FVector(0, 0, 300.f));
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshFinder(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (StaticMeshFinder.Succeeded())
	{
		Mesh2->SetStaticMesh(StaticMeshFinder.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

