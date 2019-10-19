/*
 * this json contains :
 *  a tag if it is a group of instances or an instance
 *   if it is a group it contains :
 *    an ordered list of instances in the form of a tree, completed by a place holder tag,x,y
 *     (the instances being a record of a dirname, a name, a category, x, y)
 *   if it is an instance it contains :
 *      XP location to use (variable contains Dir name or main)
 *      custom scenery to use (variable stores Dir name or main)
 *      aircraft directory to use (variable stores Dir name or main)
 *      special options yet to be defined
 *      the edited scenerypack.ini, stores it via the centifilemanager  (variable : main/)
 *      the command line options
 *      the plugins to be used
 */
#include "jsoninstance.h"

JsonInstance::JsonInstance():
    isGroup(true)
{

}

void JsonInstance::ReadInstanceData(){}
void JsonInstance::WriteInstanceData(){}
