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

	temp = findFreeResources(resourceTypeId);

	if (temp.size() > 0) {

	result = (*(++(temp.begin())));

	int minUseCount = dbPtr->getUsingCount(result.id);

	::std::cout << "ResourceFinder::findBestFreeResource() : " << temp.size() << ", " <<  ::std::endl;

	for (::LabrestAPI::ResourceList::iterator it = temp.begin(); it != temp.end(); ++it) {

		int tempCount = dbPtr->getUsingCount(it->id);

		//::std::cout << "ResourceFinder::findBestFreeResource() : " << it->id << ", " << tempCount  << ::std::endl;

		if (tempCount < minUseCount) {

			result = *it;

			minUseCount = tempCount;
		}
	}
	}
	else {

		result.id = -1;

	}

	::std::cout << "ResourceFinder::findBestFreeResource() : result_id = " << result.id  << ::std::endl;

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

	::LabrestAPI::ResourceList result;

	::std::cout << "ResourceFinder::findBestFreeResources() called" << ::std::endl;

	::LabrestAPI::SequenceVariants alterVars= findFreeResources(resourceTypeIds);

	::std::vector<LabrestAPI::IntList> tempVars;

	::LabrestAPI::IntList tempList;

	tempVars.push_back(tempList);

	for(::LabrestAPI::SequenceVariants::iterator it = alterVars.begin(); it != alterVars.end(); ++it)
	{
		if (it->size() != 0)
		{
			int tmpSize = tempVars.size();

			::std::cout << "size = " << tmpSize << ::std::endl;

			int copiesCount = it->size()-1;

			::std::cout << "size = " << copiesCount << ::std::endl;

			while (copiesCount>0)
			{
				for(int i=0; i< tmpSize; i++)
				{
					::LabrestAPI::IntList base = tempVars[i];

					tempVars.push_back(base);
				}
				copiesCount--;
			}

			::LabrestAPI::ResourceList::iterator itres = it->begin();

			int counter = 0;

			for(::std::vector<IntList>::iterator ti = tempVars.begin() ; ti!= tempVars.end(); ++ti)
			{
				if (itres == it->end())
				{
					itres = it->begin();

					++itres;

					counter = 0;
				}
				ti->push_back(itres->id);

				counter++;

				if (counter == tmpSize) {

					counter = 0;

					++itres;
				}
			}
		}
		else
		{
			for(::std::vector<IntList>::iterator ti = tempVars.begin() ; ti!= tempVars.end(); ++ti)
			{
				ti->push_back(-1);
			}
		}
	}

	tempList.clear();

	tempList = tempVars[0];

	int bestCount = dbPtr->getConnectionsCount(tempList);

	::std::cout << "bestCount = " << bestCount << ::std::endl;

	for(::std::vector<LabrestAPI::IntList>::iterator ti = tempVars.begin() ; ti!= tempVars.end(); ++ti)
	{
		int tmpCount = dbPtr->getConnectionsCount(*ti);

		if(tmpCount > 0)
		{
			::std::cout << "currentCount = " << tmpCount << ::std::endl;
		}
		if (bestCount < tmpCount)
		{
			::std::cout << "current better then best" << ::std::endl;
			tempList = (*ti);

			bestCount = tmpCount;
		}
	}
	::std::cout << "result_ids:"  << ::std::endl;
	for(::LabrestAPI::IntList::iterator it = tempList.begin(); it != tempList.end(); ++it)
	{
		::std::cout <<  *it << ",";

		::LabrestAPI::Resource res;
		if (*it == -1)
		{
			res.id = -1;
		}
		else
		{
			res = dbPtr->getResource(*it);
		}
		result.push_back(res);
	}

	::std::cout << "\nResourceFinder::findBestFreeResources() done" << ::std::endl;

	return result;
}

