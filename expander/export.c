#include "../global.h"

//export [-fn] [name[=value] ...] or export -p
// NO FLAGS, NO OTIOINS, only export, export name, export name=value,
//ALSO a b c=6 d=
//SHOULD GIVE INSIDE THE ENV:
//***
//**
//*
//a
//b
//c="6"
//d=""
//
//BUT"c (space) =6" should prompt "export: '=6: not a valid identifier"
//
