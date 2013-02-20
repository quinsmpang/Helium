//----------------------------------------------------------------------------------------------------------------------
// SliceDefinition.h
//
// Copyright (C) 2010 WhiteMoon Dreams, Inc.
// All Rights Reserved
//----------------------------------------------------------------------------------------------------------------------

#pragma once
#ifndef HELIUM_FRAMEWORK_SLICE_H
#define HELIUM_FRAMEWORK_SLICE_H

#include "Framework/Framework.h"

#include "Engine/Package.h"
#include "Engine/GameObject.h"

#include "MathSimd/Quat.h"
#include "MathSimd/Vector3.h"
#include "Framework/EntityDefinition.h"
#include "Framework/Entity.h"

#include "Framework/World.h"

namespace Helium
{
    class EntityDefinition;

    class World;
    typedef Helium::WeakPtr< World > WorldWPtr;
    typedef Helium::WeakPtr< const World > ConstWorldWPtr;
    
    class SliceDefinition;
    typedef Helium::StrongPtr< SliceDefinition > SliceDefinitionPtr;
    typedef Helium::StrongPtr< const SliceDefinition > ConstSliceDefinitionPtr;

    class Slice;
    typedef Helium::StrongPtr< Slice > SlicePtr;
    typedef Helium::StrongPtr< const Slice > ConstSlicePtr;

    class Entity;
    typedef Helium::StrongPtr< Entity > EntityPtr;
    typedef Helium::StrongPtr< const Entity > ConstEntityPtr;

    class Slice : public Reflect::Object
    {
    public:
        REFLECT_DECLARE_OBJECT(Helium::Slice, Reflect::Object);
        Slice();
        ~Slice();

        void Initialize(Helium::SliceDefinition *pSliceDefinition);

        /// @name EntityDefinition Creation
        //@{
        virtual Helium::Entity* CreateEntity(EntityDefinition *pEntityDefinition);
        virtual bool DestroyEntity( EntityDefinition* pEntity );
        //@}

        /// @name EntityDefinition Access
        //@{
        inline size_t GetEntityCount() const;
        inline Entity* GetEntity( size_t index ) const;
        //@}

        /// @name World Registration
        //@{
        inline World *GetWorld();
        inline const World *GetWorld() const;
        inline size_t GetWorldIndex() const;
        void SetWorldInfo( World* pWorld, size_t worldIndex );
        void SetWorldIndex( size_t worldIndex );
        void ClearWorldInfo();
        //@}

        Helium::SliceDefinition *GetSliceDefinition() const { return m_spSliceDefinition; }

    private:
        Helium::SliceDefinitionPtr m_spSliceDefinition;

        /// Entities.
        DynamicArray< EntityPtr > m_entities;

        /// Slice world.
        WorldWPtr m_spWorld;
        /// Runtime index for the slice within its world.
        size_t m_worldIndex;
    };
}

#include "Framework/Slice.inl"

#endif  // HELIUM_FRAMEWORK_SLICE_H