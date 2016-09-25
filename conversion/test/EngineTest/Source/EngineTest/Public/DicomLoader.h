// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DicomLoader.generated.h"

/**
 * 
 */
UCLASS()
class ENGINETEST_API UDicomLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
    /* ... */
	UFUNCTION( BlueprintCallable, Category = "DicomLoader" )
    static UTexture2D* LoadDemo( int& OutSlicesX, int& NSlices );
    
    /* ... */
    UFUNCTION( BlueprintCallable, Category = "DicomLoader" )
    static UTexture2D* Load( const FString InPath, int& OutSlicesX, int& NSlices );
	
};
