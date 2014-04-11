/*
cadosql.h
---------
Begin: 2007/01/19
Last revision: $Date: 2011-10-25 05:13:58 $ $Author: areeves $
Version number: $Revision: 1.5 $
Project: cadosql.dll
Website: http://www.aaronreeves.com/cadosql
Author: Aaron Reeves <aaron@aaronreeves.com>
----------------------------------------------------
Copyright (C) 2007 - 2014 Aaron Reeves

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/

#ifndef _ADOSQL_H_
#define _ADOSQL_H_

#ifdef __cplusplus
  extern "C" {
#endif

#if defined(DLL_EXPORTS)
  #define LIBSPEC __declspec( dllexport )
#elif defined(DLL_IMPORTS)
  #define LIBSPEC __declspec( dllimport )
#else
  #define LIBSPEC
#endif

typedef void* TAdoDatabase;
typedef void* TAdoRecordset;
typedef void* TAdoCommand;
typedef void* TAdoxCatalog;
typedef void* TAdoxTable;

struct SAdoFieldInfo {
  char m_strName[64];  // FIX ME: what is the maximum allowed by MySQL and Access for a field name?
  short m_nType;
  long m_lSize;
  long m_lDefinedSize;
  long m_lAttributes;
  short m_nOrdinalPosition;
  bool m_bRequired;
  bool m_bAllowZeroLength;
  long m_lCollatingOrder;
};

LIBSPEC TAdoDatabase adoDatabase_new( void );
LIBSPEC void adoDatabase_free( TAdoDatabase adoDatabase );

LIBSPEC bool adoDatabase_Execute( TAdoDatabase adoDatabase, const char* str );
LIBSPEC void adoDatabase_SetConnectionString( TAdoDatabase adoDatabase, const char* str );
LIBSPEC long adoDatabase_GetRecordsAffected( TAdoDatabase adoDatabase );
LIBSPEC void adoDatabase_SetConnectionModeShareDenyNone( TAdoDatabase adoDatabase );
LIBSPEC bool adoDatabase_Open( TAdoDatabase adoDatabase );
LIBSPEC bool adoDatabase_IsOpen( TAdoDatabase adoDatabase );
LIBSPEC void adoDatabase_Close( TAdoDatabase adoDatabase );
LIBSPEC void adoDatabase_LastError( TAdoDatabase adoDatabase, char* lastError );


LIBSPEC TAdoRecordset adoRecordset_new( TAdoDatabase db );
LIBSPEC void adoRecordset_free( TAdoRecordset adoRecordset );

LIBSPEC bool adoRecordset_Execute( TAdoRecordset adoRecordset, TAdoCommand cmd );
LIBSPEC long adoRecordset_GetFieldCount( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_GetFieldInfo( TAdoRecordset adoRecordset, int i, SAdoFieldInfo* fld );
LIBSPEC long adoRecordset_GetRecordCount( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_IsEof( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_IsFieldNull( TAdoRecordset adoRecordset, int i );
LIBSPEC bool adoRecordset_GetFieldValue( TAdoRecordset adoRecordset, int i, char* str );
LIBSPEC void adoRecordset_MoveNext( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_IsOpen( TAdoRecordset adoRecordset );
LIBSPEC void adoRecordset_Close( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_Open( TAdoRecordset adoRecordset );
LIBSPEC char* adoRecordset_GetFieldType( int nType );

// FIXME: The next time this section is revisited, consider replacing these functions with
// something like adoRecordset_SchemaFeature, with a request for the appropriate member 
// of the cadoSchemaType enum (from ado2.h)
LIBSPEC bool adoRecordset_PrimaryKeys( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_ForeignKeys( TAdoRecordset adoRecordset );
LIBSPEC bool adoRecordset_Indices( TAdoRecordset adoRecordset );

LIBSPEC void adoRecordset_LastError( TAdoRecordset adoRecordset, char* lastError );

LIBSPEC TAdoCommand adoCommand_new( TAdoDatabase adoDatabase, const char* query );
LIBSPEC void adoCommand_free( TAdoCommand adoCommand );

LIBSPEC TAdoxCatalog adoxCatalog_new( void );
LIBSPEC void adoxCatalog_free( TAdoxCatalog adoxCatalog );

LIBSPEC bool adoxCatalog_CreateDatabase( TAdoxCatalog adoxCatalog, const char* connectionStr );
LIBSPEC bool adoxCatalog_Open( TAdoxCatalog adoxCatalog, const char* connectionStr );
LIBSPEC bool adoxCatalog_IsOpen( TAdoxCatalog adoxCatalog );
LIBSPEC bool adoxCatalog_Close( TAdoxCatalog adoxCatalog );
LIBSPEC long adoxCatalog_GetTableCount( TAdoxCatalog adoxCatalog );
LIBSPEC void adoxCatalog_GetTableName( TAdoxCatalog adoxCatalog, long nTableIndex, char* tableName );



LIBSPEC TAdoxTable adoxTable_new( TAdoxCatalog adoxCatalog );
LIBSPEC void adoxTable_free( TAdoxTable adoxTable );

LIBSPEC bool adoxTable_Open( TAdoxTable adoxTable, const char* tableName );
LIBSPEC bool adoxTable_IsAutoincrement( TAdoxTable adoxTable, const char* fieldName );
LIBSPEC void adoxTable_GetDescription( TAdoxTable adoxTable, const char* fieldName, char* descr );


LIBSPEC int test_add( int a, int b );


#ifdef __cplusplus
  }
#endif

#endif // _ADOSQL_H_

