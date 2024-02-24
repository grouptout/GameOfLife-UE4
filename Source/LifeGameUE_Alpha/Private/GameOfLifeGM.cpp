// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifeGM.h"

void AGameOfLifeGM::BeginPlay()
{
	Super::BeginPlay();
	Board = GetWorld()->SpawnActorDeferred<ABoard>(BoardClass, FTransform::Identity);
	if (IsValid(Board))
	{
		Board->FinishSpawning(FTransform::Identity);
	}
}
