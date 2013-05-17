/* 
 * File:   UserCommand.h
 * Author: alina
 *
 * Created on May 13, 2013, 11:36 AM
 */

#ifndef USERCOMMAND_H
#define	USERCOMMAND_H

#include <iostream>
#include <vector>

#include "LabrestAPI.h"

class base_command 
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session) = 0;
protected:
    void rightParameters(::std::vector<std::string> &parameters, int count);
};

class add_user_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class delete_user_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class all_users_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};


class exit_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class help_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_user_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};


class base_change_user_command 
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session) = 0;
};

class change_us_password : public base_change_user_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};


class base_change_resource_command 
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session) = 0;
};

class change_res_name : public base_change_resource_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_res_descr : public base_change_resource_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_res_typeId : public base_change_resource_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_res_parentId : public base_change_resource_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class add_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class delete_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class lock_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class unlock_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class all_resource_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};


class base_change_restype_command 
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session) = 0;
};

class change_restype_name : public base_change_restype_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_restype_descr : public base_change_restype_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_restype_parentId : public base_change_restype_command
{
public:
    virtual void run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class change_restype_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class add_restype_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class delete_restype_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};

class all_restype_command : public base_command
{
public:
    virtual bool run(::std::vector<std::string> parameters, ::LabrestAPI::SessionPrx session);
};


#endif	/* USERCOMMAND_H */

