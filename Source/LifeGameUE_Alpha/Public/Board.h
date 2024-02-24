// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "Board.generated.h"

UCLASS(BlueprintType)
class LIFEGAMEUE_ALPHA_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoard();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperTileMapComponent* TileMap;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float RefreshRate = 0.5;

private:
	TSet<FIntPoint> CellsToCheck;
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<FIntPoint> AliveCells;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateCells();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTileStateToMap(const FIntPoint& Coord, const bool Alive);

private:
	int32 CountNeighbours(const FIntPoint& Cell);
	bool IsAlive(const FIntPoint& Cell);
	void ApplyNewStates();
};
