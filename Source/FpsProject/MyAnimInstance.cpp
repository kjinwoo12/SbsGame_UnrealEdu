// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::PlayAttackMontage()
{
	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyAnimInstance::PlayAttackMontage - AttackMontage is invalid"));
		return;
	}

	if (Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp, Log, TEXT("MyAnimInstance::PlayAttackMontage - AttackMontage is already playing"));
		return;
	}

	Montage_Play(AttackMontage);
}

void UMyAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UMyAnimInstance::AnimNotify_AttackHitCheck()
{
	UE_LOG(LogTemp, Log, TEXT("UMyAnimInstance::AnimNotify_AttackHitCheck"));

	OnAttackHitCheckDelegate.Broadcast();
}

void UMyAnimInstance::AnimNotify_NextAttackCheck()
{
	UE_LOG(LogTemp, Log, TEXT("UMyAnimInstance::AnimNotify_AttackHitCheck"));

	OnNextAttackCheckDelegate.Broadcast();
}

FName UMyAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}