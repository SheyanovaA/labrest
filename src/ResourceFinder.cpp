/*
 * ResourceFinder.cpp
 *
 *  Created on: Jan 13, 2016
 *      Author: alina
 */

#include "ResourceFinder.h"

LabrestAPI::ResourceFinder::ResourceFinder() {
	// TODO Auto-generated constructor stub

}

LabrestAPI::ResourceFinder::~ResourceFinder() {
	// TODO Auto-generated destructor stub
}

::LabrestAPI::ResourceList
 LabrestAPI::ResourceFinder::findFreeResources(int resourceTypeId) {

	::std::cout << "ResourceFinder::findFreeResources() called" << ::std::endl;

	::LabrestAPI::ResourceList result, temp;

	temp = dbPtr->getResources(resourceTypeId);

	for (::LabrestAPI::ResourceList::iterator it = temp.begin(); it != temp.end(); ++it) {

		if (dbPtr->ResourceIsNotLock(it->id)) {
			result.push_back(*it);
		}
	}

	return result;
}

::LabrestAPI::Resource
 LabrestAPI::ResourceFinder::findBestFreeResource(int resourceTypeId) {

	::std::cout << "ResourceFinder::findBestFreeResource() called" << ::std::endl;

	::LabrestAPI::ResourceList temp;

	::LabrestAPI::Resource result;

	int minUseCount = -1;

	temp = dbPtr->getResources(resourceTypeId);

	for (::LabrestAPI::ResourceList::iterator it = temp.begin(); it != temp.end(); ++it) {

		int tempCount = dbPtr->getUsingCount(it->id);

		if (tempCount < minUseCount) {

			result = *it;
		}
	}

	return result;

}

::LabrestAPI::SequenceVariants
 LabrestAPI::ResourceFinder::findFreeResources(::LabrestAPI::IntList resourceTypeIds) {

	::LabrestAPI::SequenceVariants result;

	for (::LabrestAPI::IntList::iterator it = resourceTypeIds.begin(); it != resourceTypeIds.end(); ++it)
	{
	    result.push_back(findFreeResources(*it));
	};
	return result;
}

::LabrestAPI::ResourceList
 LabrestAPI::ResourceFinder::findBestFreeResources(::LabrestAPI::IntList resourceTypeIds) {

	return ::LabrestAPI::ResourceList();
}
