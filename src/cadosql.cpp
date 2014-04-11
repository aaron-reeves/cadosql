/*
cadosql.cpp
-----------
Begin: 2007/01/19
Last revision: $Date: 2011-10-25 05:13:58 $ $Author: areeves $
Version number: $Revision: 1.5 $
Project: cadosql.dll
Website: http://www.aaronreeves.com/cadosql
Author: Aaron Reeves <aaron@aaronreeves.com>
----------------------------------------------------
Copyright (C) 2007 by Aaron Reeves

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
Public License as published by the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/

/*
  Define DLL_EXPORTS before including sqldll.h.  That way,
  LIBSPEC will be properly defined for exporting the DLL functions.
*/
#define DLL_EXPORTS

#include <cadosql.h>

#include <string.h>

#include "antolliniADO/AdoX.h"
#include "antolliniADO/ado2.h"


//-----------------------------------------------------------------------------
// AdoDatabase
//-----------------------------------------------------------------------------
  LIBSPEC TAdoDatabase adoDatabase_new( void ) {
    return new CADODatabase();
  }


  LIBSPEC void adoDatabase_free( TAdoDatabase adoDatabase ) {
    if( NULL != adoDatabase )
      delete (CADODatabase*)adoDatabase;
  }


  LIBSPEC bool adoDatabase_Execute( TAdoDatabase adoDatabase, const char* str ) {
    return( TRUE == ((CADODatabase*)adoDatabase)->Execute( str ) );
  }


  LIBSPEC void adoDatabase_SetConnectionString( TAdoDatabase adoDatabase, const char* str ) {
    ((CADODatabase*)adoDatabase)->SetConnectionString( str );
  }


  LIBSPEC long adoDatabase_GetRecordsAffected( TAdoDatabase adoDatabase ) {
    return ((CADODatabase*)adoDatabase)->GetRecordsAffected();
  }


  LIBSPEC void adoDatabase_SetConnectionModeShareDenyNone( TAdoDatabase adoDatabase ) {
    ((CADODatabase*)adoDatabase)->SetConnectionMode( CADODatabase::connectModeShareDenyNone );
  }


  LIBSPEC bool adoDatabase_Open( TAdoDatabase adoDatabase ) {
    return( TRUE == ((CADODatabase*)adoDatabase)->Open() );
  }


  LIBSPEC bool adoDatabase_IsOpen( TAdoDatabase adoDatabase ) {
    return( TRUE == ((CADODatabase*)adoDatabase)->IsOpen() );
  }


  LIBSPEC void adoDatabase_Close( TAdoDatabase adoDatabase ) {
    ((CADODatabase*)adoDatabase)->Close();
  }


  LIBSPEC void adoDatabase_LastError( TAdoDatabase adoDatabase, char* lastError ) {
    CString error = ((CADODatabase*)adoDatabase)->GetLastErrorString(); 

    strcpy( lastError, error.GetBuffer( error.GetLength() + 1 ) );
  }
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// AdoRecordset
//-----------------------------------------------------------------------------
  LIBSPEC TAdoRecordset adoRecordset_new( TAdoDatabase db ) {
    return new CADORecordset( (CADODatabase*)db );
  }


  LIBSPEC void adoRecordset_free( TAdoRecordset adoRecordset ) {
    if( NULL != adoRecordset )
      delete (CADORecordset*)adoRecordset;
  }


  LIBSPEC bool adoRecordset_Execute( TAdoRecordset adoRecordset, TAdoCommand cmd ) {
    return( TRUE == ((CADORecordset*)adoRecordset)->Execute( (CADOCommand*)cmd ) );
  }


  LIBSPEC long adoRecordset_GetFieldCount( TAdoRecordset adoRecordset ) {
    return ((CADORecordset*)adoRecordset)->GetFieldCount();
  }


  LIBSPEC bool adoRecordset_GetFieldInfo( TAdoRecordset adoRecordset, int i, SAdoFieldInfo* fld ) {
    CADOFieldInfo fi;
    bool result;

    result = ( TRUE == ((CADORecordset*)adoRecordset)->GetFieldInfo( i, &fi ) );

    if( result ) {
      strcpy( fld->m_strName, fi.m_strName );
      fld->m_nType = fi.m_nType;
      fld->m_lSize = fi.m_lSize;
      fld->m_lDefinedSize = fi.m_lDefinedSize;
      fld->m_lAttributes = fi.m_lAttributes;
      fld->m_nOrdinalPosition = fi.m_nOrdinalPosition;
      fld->m_bRequired = ( TRUE == fi.m_bRequired );
      fld->m_bAllowZeroLength = ( TRUE == fi.m_bAllowZeroLength );
      fld->m_lCollatingOrder = fi.m_lCollatingOrder;
    }

    return result;
  }


  LIBSPEC long adoRecordset_GetRecordCount( TAdoRecordset adoRecordset ) {
    return ((CADORecordset*)adoRecordset)->GetRecordCount();
  }


  LIBSPEC bool adoRecordset_IsEof( TAdoRecordset adoRecordset ) {
    return( TRUE == ((CADORecordset*)adoRecordset)->IsEOF() );
  }


  LIBSPEC bool adoRecordset_IsFieldNull( TAdoRecordset adoRecordset, int i ) {
    return( TRUE == ((CADORecordset*)adoRecordset)->IsFieldNull( i ) );
  }


  LIBSPEC bool adoRecordset_GetFieldValue( TAdoRecordset adoRecordset, int i, char* str ) {
    CString s;
    bool result;
    CADOFieldInfo fi;

    result = ( TRUE == ((CADORecordset*)adoRecordset)->GetFieldValue( i, s ) );

    if( result ) {
      // Is the field boolean?
      ((CADORecordset*)adoRecordset)->GetFieldInfo( i, &fi );

      if( CADORecordset::typeBoolean == fi.m_nType ) {
        // If so, change "T" to 1 and "F" to 0.
        if( 0 == strcmp( s, "T" ) )
          strcpy( str, "1" );
        else
          strcpy( str, "0" );
      }
      else // If not, just return the unaltered value.
        strcpy( str, s.GetBuffer( s.GetLength() + 1 ) );
    }
    else
      strcpy( str, "\0" );

    return result;
  }


  LIBSPEC void adoRecordset_MoveNext( TAdoRecordset adoRecordset ) {
    ((CADORecordset*)adoRecordset)->MoveNext();
  }


  LIBSPEC bool adoRecordset_IsOpen( TAdoRecordset adoRecordset ) {
    return( TRUE == ((CADORecordset*)adoRecordset)->IsOpen() );
  }


  LIBSPEC void adoRecordset_Close( TAdoRecordset adoRecordset ) {
    ((CADORecordset*)adoRecordset)->Close();
  }


  LIBSPEC bool adoRecordset_Open( TAdoRecordset adoRecordset ) {
    return( TRUE == ((CADORecordset*)adoRecordset)->Open() );
  }


  LIBSPEC char* adoRecordset_GetFieldType( int nType ) {
    char* val;

    switch( nType ) {
      case CADORecordset::typeEmpty: val = "CHECK_Empty" ; break;
      case CADORecordset::typeTinyInt: val = "CHECK_TinyInt"; break;
      case CADORecordset::typeSmallInt: val = "Short"; break;
      case CADORecordset::typeInteger: val = "Long"; break;
      case CADORecordset::typeBigInt: val = "CHECK_BigInt"; break;
      case CADORecordset::typeUnsignedTinyInt: val = "Byte"; break;
      case CADORecordset::typeUnsignedSmallInt: val = "CHECK_UnsignedSmallInt"; break;
      case CADORecordset::typeUnsignedInt: val = "CHECK_UnsignedInt"; break;
      case CADORecordset::typeUnsignedBigInt: val = "CHECK_UnsignedBigInt"; break;
      case CADORecordset::typeSingle: val = "Single"; break;
      case CADORecordset::typeDouble: val = "Double"; break;
      case CADORecordset::typeCurrency: val = "Currency"; break;
      case CADORecordset::typeDecimal: val = "CHECK_Decimal"; break;
      case CADORecordset::typeNumeric: val = "Decimal"; break;
      case CADORecordset::typeBoolean: val = "Bit"; break;
      case CADORecordset::typeError: val = "CHECK_Error"; break;
      case CADORecordset::typeUserDefined: val = "CHECK_UserDefined"; break;
      case CADORecordset::typeVariant: val = "CHECK_Variant"; break;
      case CADORecordset::typeIDispatch: val = "CHECK_IDispatch"; break;
      case CADORecordset::typeIUnknown: val = "CHECK_IUnknown"; break;
      case CADORecordset::typeGUID: val = "CHECK_GUID"; break;
      case CADORecordset::typeDate: val = "Datetime"; break;
      case CADORecordset::typeDBDate: val = "CHECK_DBDate"; break;
      case CADORecordset::typeDBTime: val = "CHECK_DBTime"; break;
      case CADORecordset::typeDBTimeStamp: val = "CHECK_DBTimeStamp"; break;
      case CADORecordset::typeBSTR: val = "CHECK_BSTR"; break;
      case CADORecordset::typeChar: val = "CHECK_Char"; break;
      case CADORecordset::typeVarChar: val = "CHECK_VarChar"; break;
      case CADORecordset::typeLongVarChar: val = "CHECK_LongVarChar"; break;
      case CADORecordset::typeWChar: val = "Char"; break;
      case CADORecordset::typeVarWChar: val = "Text"; break;
      case CADORecordset::typeLongVarWChar: val = "Longtext"; break;
      case CADORecordset::typeBinary: val = "CHECK_Binary"; break;
      case CADORecordset::typeVarBinary: val = "CHECK_VarBinary"; break;
      case CADORecordset::typeLongVarBinary: val = "Longbinary"; break;
      case CADORecordset::typeChapter: val = "CHECK_Chapter"; break;
      case CADORecordset::typeFileTime: val = "CHECK_FileTime"; break;
      case CADORecordset::typePropVariant: val = "CHECK_PropVariant"; break;
      case CADORecordset::typeVarNumeric: val = "CHECK_VarNumeric"; break;
      // case CADORecordset::typeArray: val = "CHECK_Array"; break; // same as variant, apparently
      default: val = "TYPE UNKNOWN"; break;
    }

    return val;
  }


  LIBSPEC bool adoRecordset_ForeignKeys( TAdoRecordset adoRecordset ) {
    return ( TRUE == ((CADORecordset*)adoRecordset)->OpenSchema( CADORecordset::schemaForeignKeys ) );
  }

  LIBSPEC bool adoRecordset_PrimaryKeys( TAdoRecordset adoRecordset ) {
    return ( TRUE == ((CADORecordset*)adoRecordset)->OpenSchema( CADORecordset::schemaPrimaryKeys ) );
  }

  LIBSPEC bool adoRecordset_Indices( TAdoRecordset adoRecordset ) {
    return ( TRUE == ((CADORecordset*)adoRecordset)->OpenSchema( CADORecordset::schemaIndexes ) );
  }

  LIBSPEC void adoRecordset_LastError( TAdoRecordset adoRecordset, char* lastError ) {
    CString error = ((CADORecordset*)adoRecordset)->GetLastErrorString(); 

    strcpy( lastError, error.GetBuffer( error.GetLength() + 1 ) );
  }
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// AdoCommand
//-----------------------------------------------------------------------------
  LIBSPEC TAdoCommand adoCommand_new( TAdoDatabase adoDatabase, const char* query ) {
    return new CADOCommand( (CADODatabase*)adoDatabase, query, CADOCommand::typeCmdText );
  }


  LIBSPEC void adoCommand_free( TAdoCommand adoCommand ) {
    if( NULL != adoCommand )
      delete (CADOCommand*)adoCommand;
  }
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// AdoxCatalog
//-----------------------------------------------------------------------------
  LIBSPEC TAdoxCatalog adoxCatalog_new( void ) {
    return new CADOXCatalog();
  }


  LIBSPEC void adoxCatalog_free( TAdoxCatalog adoxCatalog ) {
    if( NULL != adoxCatalog )
      delete (CADOXCatalog*)adoxCatalog;
  }


  LIBSPEC bool adoxCatalog_CreateDatabase( TAdoxCatalog adoxCatalog, const char* connectionStr ) {
    return ((CADOXCatalog*)adoxCatalog)->CreateDatabase( connectionStr );
  }


  LIBSPEC bool adoxCatalog_Open( TAdoxCatalog adoxCatalog, const char* connectionStr ) {
    return ((CADOXCatalog*)adoxCatalog)->Open( connectionStr );
  }


  LIBSPEC bool adoxCatalog_IsOpen( TAdoxCatalog adoxCatalog ) {
    return ((CADOXCatalog*)adoxCatalog)->IsOpen();
  }


  LIBSPEC bool adoxCatalog_Close( TAdoxCatalog adoxCatalog ) {
    return ((CADOXCatalog*)adoxCatalog)->Close();
  }


  LIBSPEC long adoxCatalog_GetTableCount( TAdoxCatalog adoxCatalog ) {
    return ((CADOXCatalog*)adoxCatalog)->GetTableCount();
  }


  LIBSPEC void adoxCatalog_GetTableName( TAdoxCatalog adoxCatalog, long nTableIndex, char* tableName ) {
    CString s;

    ((CADOXCatalog*)adoxCatalog)->GetTableName( nTableIndex, s );
    strcpy( tableName, s.GetBuffer( s.GetLength() + 1 ) );
  }
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// AdoxTable
//-----------------------------------------------------------------------------
  LIBSPEC TAdoxTable adoxTable_new( TAdoxCatalog adoxCatalog ) {
    return new CADOXTable( (CADOXCatalog*)adoxCatalog );
  }


  LIBSPEC void adoxTable_free( TAdoxTable adoxTable ) {
    if( NULL != adoxTable )
      delete (TAdoxTable*)adoxTable;
  }


  LIBSPEC bool adoxTable_Open( TAdoxTable adoxTable, const char* tableName ) {
    return ((CADOXTable*)adoxTable)->Open( tableName );
  }


  LIBSPEC bool adoxTable_IsAutoincrement( TAdoxTable adoxTable, const char* fieldName ) {
    return ((CADOXTable*)adoxTable)->m_pTable->Columns->GetItem( fieldName )->Properties->GetItem( "Autoincrement" )->Value;
  }


  LIBSPEC void adoxTable_GetDescription( TAdoxTable adoxTable, const char* fieldName, char* descr ) {
    strcpy( descr, ((char *)(_bstr_t) ( ((CADOXTable*)adoxTable)->m_pTable->Columns->GetItem( fieldName )->Properties->GetItem( "Description" )->Value ) ) );
  }
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Testing functions
//-----------------------------------------------------------------------------
  LIBSPEC int test_add( int a, int b ) {
    return a + b;
  }
//-----------------------------------------------------------------------------
