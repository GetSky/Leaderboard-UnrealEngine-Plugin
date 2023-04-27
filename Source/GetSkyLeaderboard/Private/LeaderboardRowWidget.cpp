// Fill out your copyright notice in the Description page of Project Settings.

#include "LeaderboardRowWidget.h"

#include "Components/TextBlock.h"

void ULeaderboardRowWidget::SetData(const FString& Name, const FString& Score, bool bIsCurrentPlayer) const
{
	NameBlock->SetText(FText::FromString(Name));
	ScoreBlock->SetText(FText::FromString(Score));

	if (bIsCurrentPlayer == false) return;

	NameBlock->SetColorAndOpacity(CurrentPlayerColor);
	ScoreBlock->SetColorAndOpacity(CurrentPlayerColor);
}
