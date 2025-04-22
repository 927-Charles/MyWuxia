// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MyWuxiaGameModeBase.h"
#include "TopDownCharacter.h"
#include "CombatPlayerController.h"

#include "UObject/ConstructorHelpers.h"


AMyWuxiaGameModeBase::AMyWuxiaGameModeBase() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/MyTopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr) {
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		// 后备方案：使用C++类（需确保存在）
		DefaultPawnClass = ATopDownCharacter::StaticClass();
	}
	PlayerControllerClass = ACombatPlayerController::StaticClass(); // 自定义PlayerController


}