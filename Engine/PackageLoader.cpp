//----------------------------------------------------------------------------------------------------------------------
// PackageLoader.cpp
//
// Copyright (C) 2010 WhiteMoon Dreams, Inc.
// All Rights Reserved
//----------------------------------------------------------------------------------------------------------------------

#include "EnginePch.h"
#include "Engine/PackageLoader.h"

namespace Lunar
{
    /// Destructor.
    PackageLoader::~PackageLoader()
    {
    }

    /// @fn size_t PackageLoader::BeginLoadObject( ObjectPath path )
    /// Begin asynchronous preloading of an object's properties from the cache.
    ///
    /// Note: Do NOT call this multiple times for the same object (access to this function should actually be abstracted
    /// by the ObjectLoader interface).
    ///
    /// @param[in] path  Path of the object to attempt to load.
    ///
    /// @return  Load request ID.
    ///
    /// @see TryFinishLoadObject()

    /// @fn bool TryFinishLoadObject( size_t requestId, ObjectPtr& rspObject, DynArray< ObjectLoader::LinkEntry >& rLinkTable )
    /// Test for and finalize an asynchronous object preload request in a non-blocking fashion.
    ///
    /// @param[in]  requestId   ID of the preload request returned by BeginLoadObject() (NOT the object index).
    /// @param[out] rspObject   Smart pointer to the object if preloading has completed (linking still needs to occur).
    /// @param[out] rLinkTable  Array to fill with the object link table.
    ///
    /// @return  True if the preload has finished, false if not.
    ///
    /// @see BeginLoadObject()

    /// @fn size_t PackageLoader::GetObjectCount() const
    /// Get the number of objects in the associated package file.
    ///
    /// @return  Object count.
    ///
    /// @see GetObjectPath(), GetObjectType(), GetObject()

    /// @fn ObjectPath PackageLoader::GetObjectPath( size_t index ) const
    /// Get the path name of the object with the given index.
    ///
    /// @param[in] index  Object index.
    ///
    /// @return  Object path.
    ///
    /// @see GetObjectType(), GetObject(), GetObjectCount()

    /// @fn bool PackageLoader::IsSourcePackageFile() const
    /// Get whether this loader loads objects from a source package (instead of a cache).
    ///
    /// @return  True if this loader loads from a source package file, false if not.
    ///
    /// @see GetFileTimestamp()

    /// @fn int64_t PackageLoader::GetFileTimestamp() const
    /// Get the timestamp of the source package file.
    ///
    /// Note that this only returns a valid timestamp for source package loaders and not loaders that load from a cache.
    ///
    /// @return  Source package file timestamp.
    ///
    /// @see IsSourcePackageFile()
}
