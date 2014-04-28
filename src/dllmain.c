/*
dllmain.c
---------
Begin: 2007/01/19
Last revision: $Date: 2011-10-25 05:13:58 $ $Author: areeves $
Version number: $Revision: 1.3 $
Project: cadosql.dll
Website: http://www.aaronreeves.com/cadosql
Author: Aaron Reeves <development@reevesdigital.com>
----------------------------------------------------
Copyright (C) 2007 by Aaron Reeves

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/


#include <windows.h>

BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
