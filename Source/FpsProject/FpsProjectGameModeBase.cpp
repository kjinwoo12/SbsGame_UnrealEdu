// Fill out your copyright notice in the Description page of Project Settings.


#include "FpsProjectGameModeBase.h"

void AFpsProjectGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello world! AFpsProjectGameModeBase"));
}