// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineTest.h"
#include "DicomLoader.h"

#include <iostream>
#include <fstream>


UTexture2D* UDicomLoader::LoadDemo( int& OutSlicesX, int& NSlices ) {
    FString demoPath = FString( TEXT( "/" ) );
    return UDicomLoader::Load( demoPath, OutSlicesX, NSlices );
}

UTexture2D* UDicomLoader::Load( const FString InPath, int& OutSlicesX, int& NSlices ) {
    
    // TODO
    return NULL;
    
}