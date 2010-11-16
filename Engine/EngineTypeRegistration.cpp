//----------------------------------------------------------------------------------------------------------------------
// EngineTypeRegistration.cpp
//
// Copyright (C) 2010 WhiteMoon Dreams, Inc.
// All Rights Reserved
//----------------------------------------------------------------------------------------------------------------------

// !!! AUTOGENERATED FILE - DO NOT EDIT !!!

#include "EnginePch.h"
#include "Platform/Assert.h"
#include "Engine/Package.h"

#include "Engine/Package.h"
#include "Engine/Type.h"
#include "Engine/Resource.h"

static Lunar::StrongPtr< Lunar::Package > spEngineTypePackage;

LUNAR_ENGINE_API Lunar::Package* GetEngineTypePackage()
{
    Lunar::Package* pPackage = spEngineTypePackage;
    if( !pPackage )
    {
        HELIUM_VERIFY( Lunar::Object::InitStaticType() );

        Lunar::Object* pTypesPackageObject = Lunar::Object::FindChildOf( NULL, Lunar::Name( TXT( "Types" ) ) );
        HELIUM_ASSERT( pTypesPackageObject );
        HELIUM_ASSERT( pTypesPackageObject->IsPackage() );

        Lunar::Object* pPackageObject = Lunar::Object::FindChildOf(
            pTypesPackageObject,
            Lunar::Name( TXT( "Engine" ) ) );
        HELIUM_ASSERT( pPackageObject );
        HELIUM_ASSERT( pPackageObject->IsPackage() );

        pPackage = Lunar::StaticCast< Lunar::Package >( pPackageObject );
        spEngineTypePackage = pPackage;
    }

    return pPackage;
}

LUNAR_ENGINE_API void ReleaseEngineTypePackage()
{
    spEngineTypePackage = NULL;
}

LUNAR_ENGINE_API void RegisterEngineTypes()
{
    HELIUM_VERIFY( GetEngineTypePackage() );

    HELIUM_VERIFY( Lunar::Package::InitStaticType() );
    HELIUM_VERIFY( Lunar::Resource::InitStaticType() );
    HELIUM_VERIFY( Lunar::Type::InitStaticType() );
}

LUNAR_ENGINE_API void UnregisterEngineTypes()
{
    Lunar::Package::ReleaseStaticType();
    Lunar::Resource::ReleaseStaticType();
    Lunar::Type::ReleaseStaticType();

    ReleaseEngineTypePackage();
}
