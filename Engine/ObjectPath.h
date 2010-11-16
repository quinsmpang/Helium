//----------------------------------------------------------------------------------------------------------------------
// ObjectPath.h
//
// Copyright (C) 2010 WhiteMoon Dreams, Inc.
// All Rights Reserved
//----------------------------------------------------------------------------------------------------------------------

#pragma once
#ifndef LUNAR_ENGINE_OBJECT_PATH_H
#define LUNAR_ENGINE_OBJECT_PATH_H

#include "Engine/Engine.h"

#include "Platform/ReadWriteLock.h"
#include "Foundation/Name.h"

/// @defgroup objectpathdelims Object Path Delimiter Characters
//@{

/// Package delimiter character.
#define L_PACKAGE_PATH_CHAR TXT( '/' )
/// Object delimiter character.
#define L_OBJECT_PATH_CHAR TXT( ':' )
/// Object instance index delimiter character.
#define L_INSTANCE_PATH_CHAR TXT( '*' )

/// Package delimiter character string.
#define L_PACKAGE_PATH_CHAR_STRING TXT( "/" )
/// Object delimiter character string.
#define L_OBJECT_PATH_CHAR_STRING TXT( ":" )
/// Object instance index delimiter character.
#define L_INSTANCE_PATH_CHAR_STRING TXT( "*" )

//@}

namespace Lunar
{
    /// Hashed object path name for fast lookups and comparisons.
    class LUNAR_ENGINE_API ObjectPath
    {
    public:
        /// Number of object path hash table buckets (prime numbers are recommended).
        static const size_t TABLE_BUCKET_COUNT = 37;
        /// Object path stack memory heap block size.
        static const size_t STACK_HEAP_BLOCK_SIZE = sizeof( tchar_t ) * 8192;

        /// @name Construction/Destruction
        //@{
        inline ObjectPath();
        inline ObjectPath( ENullName );
        //@}

        /// @name Path Access
        //@{
        bool Set( const tchar_t* pString );
        bool Set( const String& rString );
        bool Set( Name name, bool bPackage, ObjectPath parentPath, uint32_t instanceIndex = Invalid< uint32_t >() );

        bool Join( ObjectPath rootPath, ObjectPath subPath );
        bool Join( ObjectPath rootPath, const tchar_t* pSubPath );
        bool Join( const tchar_t* pRootPath, ObjectPath subPath );
        bool Join( const tchar_t* pRootPath, const tchar_t* pSubPath );

        inline Name GetName() const;
        inline uint32_t GetInstanceIndex() const;
        inline bool IsPackage() const;
        inline ObjectPath GetParent() const;

        void ToString( String& rString ) const;
        inline String ToString() const;

        void ToFilePathString( String& rString ) const;
        inline String ToFilePathString() const;

        inline bool IsEmpty() const;
        void Clear();

        inline size_t ComputeHash() const;
        //@}

        /// @name Overloaded Operators
        //@{
        inline bool operator==( ObjectPath path ) const;
        inline bool operator!=( ObjectPath path ) const;
        //@}

        /// @name Static Initialization
        //@{
        static void Shutdown();
        //@}

        /// @name File Support
        //@{
        static void ConvertStringToFilePath( String& rFilePath, const String& rPackagePath );
        //@}

    private:
        /// Object path entry.
        struct Entry
        {
            /// Parent entry.
            Entry* pParent;
            /// Object name.
            Name name;
            /// Object instance index.
            uint32_t instanceIndex;
            /// True if the object is a package.
            bool bPackage;
        };

        /// Object path hash table bucket.
        class TableBucket
        {
        public:
            /// @name Access
            //@{
            Entry* Find( const Entry& rEntry, size_t& rEntryCount );
            Entry* Add( const Entry& rEntry, size_t previousEntryCount );
            //@}

        private:
            /// Array of entry pointers.
            DynArray< Entry* > m_entries;
            /// Read-write lock for synchronizing access.
            ReadWriteLock m_lock;
        };

        /// Object path entry.
        Entry* m_pEntry;

        /// Object path hash table.
        static TableBucket* sm_pTable;
        /// Stack-based memory heap for object path entry allocations.
        static StackMemoryHeap<>* sm_pEntryMemoryHeap;

        /// @name Private Utility Functions
        //@{
        void Set( const Name* pNames, const uint32_t* pInstanceIndices, size_t nameCount, size_t packageCount );
        //@}

        /// @name Static Utility Functions
        //@{
        static bool Parse(
            const tchar_t* pString, StackMemoryHeap<>& rStackHeap, Name*& rpNames, uint32_t*& rpInstanceIndices,
            size_t& rNameCount, size_t& rPackageCount );

        static Entry* Add( const Entry& rEntry );

        static void EntryToString( const Entry& rEntry, String& rString );
        static void EntryToFilePathString( const Entry& rEntry, String& rString );

        static size_t ComputeEntryStringHash( const Entry& rEntry );
        static bool EntryContentsMatch( const Entry& rEntry0, const Entry& rEntry1 );
        //@}
    };
}

namespace Helium
{
    /// Default ObjectPath hash.
    template<>
    class LUNAR_ENGINE_API Hash< ObjectPath >
    {
    public:
        inline size_t operator()( const ObjectPath& rKey ) const;
    };
}

#include "Engine/ObjectPath.inl"

#endif  // LUNAR_ENGINE_OBJECT_PATH_H
