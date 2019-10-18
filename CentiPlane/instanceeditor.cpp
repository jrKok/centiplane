/*
 * This class is the logic for the edit instance window
 *  It receives
 *    the edited scenerypack.ini, stores it via the centifilemanager
 *    the desired copy of x plane
 *    the command line options
 *    the desired location of custom scenery (if it needs to be replaced)
 *    the desired location of aircrafts (if it needs to be replaced)
 *  Aircrafts and custom scenery are default except if altered : default is a non symlink or the symlink location defined as default
 * Another class manages the scenerypackes editor.
 * Can also alter the list of known custom scenery locations, custom aicraft locations, check any new names
 *
 */
#include "instanceeditor.h"

InstanceEditor::InstanceEditor()
{

}
