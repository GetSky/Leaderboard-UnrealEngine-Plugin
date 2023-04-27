// Fill out your copyright notice in the Description page of Project Settings.

#include "LeaderboardWidget.h"

#include "HttpModule.h"
#include "LeaderboardRowWidget.h"
#include "PluginSettings.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

DECLARE_LOG_CATEGORY_CLASS(LogLeaderboardWidget, All, All);

void ULeaderboardWidget::ShowLeaderboard(const FString& Level, const int32 Score)
{
	RequestLevel = Level;
	PlayerPositionInLeaderboard = -1;

	const auto RequestObj = MakeShared<FJsonObject>();
	RequestObj->SetStringField("level", Level);
	RequestObj->SetNumberField("score", Score);

	FString RequestBody;
	const auto Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	const FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(URLConnect);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->OnProcessRequestComplete().BindUObject(this, &ULeaderboardWidget::GetAnUpToDateList);
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void ULeaderboardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	URLConnect = "http://" + GetDefault<UPluginSettings>()->URI + ":" + GetDefault<UPluginSettings>()->Port + "/score";
}

void ULeaderboardWidget::GetAnUpToDateList(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess == false)
	{
		RequestLevel = "";
		return;
	}

	PlayerPositionInLeaderboard = FCString::Atoi(*Response->GetContentAsString());

	const FHttpRequestRef HTTPRequest = FHttpModule::Get().CreateRequest();
	HTTPRequest->OnProcessRequestComplete().BindUObject(this, &ULeaderboardWidget::OnResponseReceived);
	HTTPRequest->SetURL(URLConnect + "/" + RequestLevel);
	HTTPRequest->SetVerb("GET");
	HTTPRequest->ProcessRequest();
}

void ULeaderboardWidget::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
{
	if (bSuccess == false)
	{
		RequestLevel = "";
		PlayerPositionInLeaderboard = -1;
		return;
	}

	UE_LOG(LogLeaderboardWidget, Display, TEXT("username: %s"), *Response->GetContentAsString());

	TSharedPtr<FJsonValue> JsonValue;
	const auto JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(JsonReader, JsonValue);

	RowsBox->ClearChildren();

	for (const auto Player : JsonValue->AsArray())
	{
		ULeaderboardRowWidget* Row = CreateWidget<ULeaderboardRowWidget>(this, LeaderboardRowWidgetClass);
		Row->SetData(
			Player->AsObject()->GetStringField("username"),
			Player->AsObject()->GetStringField("score"),
			PlayerPositionInLeaderboard == Player->AsObject()->GetNumberField("id")
		);
		RowsBox->AddChildToVerticalBox(Row);
	}

	HeaderBlock->SetVisibility(ESlateVisibility::Visible);
}
