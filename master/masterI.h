#ifndef __MASTER_I_H__
#define __MASTER_I_H__

#include <string>
#include <set>
#include <map>

#include "flecs.h"


class MasterI : public FleCS::Master
{
public:
    virtual void Join(
			const std::string& endpoint,
			std::vector<std::string>& existingServers,
			const Ice::Current&);

private:
	std::map<std::string, FleCS::ServerPrx*> _servers;

	IceUtil::Mutex _lock;
};


#endif