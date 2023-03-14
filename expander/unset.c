#include "../global.h"

//without options, unset() first tries to unset a var,
//if it fails it then tries to unset a function
//  Returns success unless an invalid option
//is given or a NAME is read-only
