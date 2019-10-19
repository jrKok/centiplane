/*
 * this class manages groups and instances
 * it will use 2 instances of jsonInstance, one for the current group, one for the selected instance
 * some functions will be dependant on an instance being selected :
 *  edit/modify
 *  lauch
 *  delete
 * mainGroup and mainGroup/default cannot be deleted
 * mainGroup and mainGroup/default recieve special treatment
 *
 * All names for groups or instances must be different
 *
 * this class does not do the actual editing of an instance
 * actual editing is done in the weditinstance/editinstance classes
 */

#include "instance.h"

instance::instance():
    jsonGroup(nullptr),
    jsonInstance(nullptr),
    hasSelectedInstance(false)
{

}

instance::~instance(){
    delete jsonGroup;
    delete jsonInstance;
}

