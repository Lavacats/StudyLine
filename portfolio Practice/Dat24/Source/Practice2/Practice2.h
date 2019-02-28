// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Practice2, Log, All);

#define AB_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
// 로그 정보 함수(FUNCTION)과 라인정보(LINE)을 출력합니다.

#define ABLOG_S(Verbosity) UE_LOG(Practice2,Verbosity,TEXT("%s"),*AB_LOG_CALLINFO)
// 함수와 라인정보(AB_LOG_CALLINFO)와 같은 파일정보를 Verbosity(Warning과 같은 출력레벨)을 받아 출력합니다

#define ABLOG(Verbosity,Format,...)UE_LOG(Practice2,Verbosity,TEXT("%s %s"),*AB_LOG_CALLINFO,*FString::Printf(Format,##__VA_ARGS__))
// Verbosty(Warning과 같은 출력레벨)과 출력 포맷을 받아 입력받은 카탈로그 정보와 입력받은 정보를 출력합니다.

#define ABCHECK(Expr,...){if(!(Expr)){ABLOG(Error,TEXT("ASSERTION : %s"),TEXT("'"#Expr"'")); return __VA_ARGS__;}}
// ABCHECK 조건 Expr이 아닌경우 로그가 뜬다
