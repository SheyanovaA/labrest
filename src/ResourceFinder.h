/*
 * ResourceFinder.h
 *
 *  Created on: Jan 13, 2016
 *      Author: alina
 */

#ifndef RESOURCEFINDER_H_
#define RESOURCEFINDER_H_


#include "LabrestDB.h"
#include "LabrestAPI.h"

namespace LabrestAPI {

class ResourceFinder {
public:

	ResourceFinder();

	virtual ~ResourceFinder();

	::LabrestAPI::ResourceList findFreeResources(int resourceTypeId);

	::LabrestAPI::Resource findBestFreeResource(int resourceTypeId);

	::LabrestAPI::SequenceVariants findFreeResources(::LabrestAPI::IntList resourceTypeIds);

	::LabrestAPI::ResourceList findBestFreeResources(::LabrestAPI::IntList resourceTypeIds);

};

} /* namespace LabrestAPI */

extern LabrestAPI::ResourceFinder * resFinder;

#endif /* RESOURCEFINDER_H_ */
