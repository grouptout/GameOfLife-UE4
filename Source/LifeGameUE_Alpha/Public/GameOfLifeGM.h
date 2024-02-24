// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Board.h"
#include "GameFramework/GameModeBase.h"
#include "GameOfLifeGM.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LIFEGAMEUE_ALPHA_API AGameOfLifeGM : public AGameModeBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABoard> BoardClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ABoard* Board;
	
public:
	virtual void BeginPlay() override;
};
