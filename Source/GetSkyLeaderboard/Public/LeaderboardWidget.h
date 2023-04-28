// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "LeaderboardWidget.generated.h"

class ULeaderboardRowWidget;
class UTextBlock;
class UVerticalBox;

UCLASS()
class GETSKYLEADERBOARD_API ULeaderboardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SendScore(const FString& Level, const FString& Username, const int32 Score);

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<ULeaderboardRowWidget> LeaderboardRowWidgetClass;

	void GetAnUpToDateLeaderboard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);
	void RenderLeaderboard(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);

private:
	FString URLConnect;
	FString RequestLevel;
	int32 PlayerPositionInLeaderboard = -1;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* HeaderBlock = nullptr;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* RowsBox = nullptr;
};
