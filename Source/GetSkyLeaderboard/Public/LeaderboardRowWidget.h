// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LeaderboardRowWidget.generated.h"

class UTextBlock;

UCLASS()
class GETSKYLEADERBOARD_API ULeaderboardRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetData(const FString& Name, const FString& Score, bool bIsCurrentPlayer) const;

private:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ScoreBlock;

	UPROPERTY(EditAnywhere)
	FSlateColor CurrentPlayerColor;
};
