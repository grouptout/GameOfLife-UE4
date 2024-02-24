// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"

ABoard::ABoard()
{
	PrimaryActorTick.bCanEverTick = true;
	TileMap = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("Map"));
}

void ABoard::BeginPlay()
{
	Super::BeginPlay();
	TileMap->MakeTileMapEditable();
}

void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoard::UpdateCells()
{
	CellsToCheck.Empty();
	
	for (const auto& Cell : AliveCells)
	{
		for (int x = -1; x <= 1; ++x)
		{
			for (int y = -1; y <= 1; ++y)
			{
				CellsToCheck.Add(Cell + FIntPoint(x, y));
			}
		}
	}

	for (const auto& Cell : CellsToCheck)
	{
		const auto Neighbours = CountNeighbours(Cell);
		const auto bIsAlive = IsAlive(Cell);

		if (!bIsAlive && Neighbours == 3) // Pending to alive
		{
			AliveCells.Add(Cell);
		}
		else if (bIsAlive && (Neighbours < 2 || Neighbours > 3)) // pending to dead
		{
			AliveCells.Remove(Cell);
		}
	}
	
	ApplyNewStates();
}

int32 ABoard::CountNeighbours(const FIntPoint& Cell)
{
	int32 Res = 0;
	
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			if (x != 0 || y != 0)
			{
				const FIntPoint Neighbour = FIntPoint(Cell + FIntPoint(x, y));
				if (IsAlive(Neighbour))
				{
					++Res;
				}
			}
		}
	}
	return Res;
}

bool ABoard::IsAlive(const FIntPoint& Cell)
{
	return TileMap->GetTile(Cell.X, Cell.Y, 0).TileSet != nullptr;
}

void ABoard::ApplyNewStates()
{
	int32 Width;
	int32 Height;
	int32 xLayers;
	TileMap->GetMapSize(Width, Height, xLayers);
	
	for (const auto& Cell : CellsToCheck)
	{
		UpdateTileStateToMap(Cell, AliveCells.Contains(Cell));
	}
}

