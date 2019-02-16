#pragma once
#ifndef __DICOMHEADTABLE_H
#define __DICOMHEADTABLE_H
#include "SqliteDataBase.h"
#include "BasicDicomObject.hxx"

class DicomHeadTable : public SqliteObject
{
public:
	DicomHeadTable();
	~DicomHeadTable();

	_String GetTaleName();
	NTSTATUS CreateTable();
	NTSTATUS Instert(DciomObject);
	NTSTATUS InstertBasicHead(DciomObject);
	NTSTATUS InstertMainlyHead(DciomObject);
	NTSTATUS UpdateMainlyHead(DciomObject);
	// dx, dy, dz , caluse
	NTSTATUS UpdateSapcing(DOUBLE, DOUBLE, DOUBLE, ContentCaluse);
	// dx, dy, dz , patient id
	NTSTATUS UpdateSapcing(DOUBLE, DOUBLE, DOUBLE, _String);
	//spacing , caluse
	NTSTATUS UpdateSapcing(DOUBLE[3], ContentCaluse);
	//spacing , patient id
	NTSTATUS UpdateSapcing(DOUBLE[3], _String);

	// nx, ny, nz , caluse
	NTSTATUS UpdateImageSize(UINT, UINT, UINT, ContentCaluse);
	// nx, ny, nz , patient id
	NTSTATUS UpdateImageSize(UINT, UINT, UINT, _String);
	//image size , caluse
	NTSTATUS UpdateImageSize(UINT[3], ContentCaluse);
	//image size , patient id
	NTSTATUS UpdateImageSize(UINT[3], _String);

	///
	/// below can update image position and origin
	///
	// x, y, z , cloum name, caluse
	NTSTATUS UpdatePosition(DOUBLE, DOUBLE, DOUBLE, _String, ContentCaluse);
	// x, y, z ,cloum name,  patient id
	NTSTATUS UpdatePosition(DOUBLE, DOUBLE, DOUBLE, _String, _String);
	//position , caluse
	NTSTATUS UpdatePosition(Point3f, _String, ContentCaluse);
	//position , patient id
	NTSTATUS UpdatePosition(Point3f, _String, _String);
	/// end 
	// Orientation array, caluse
	NTSTATUS UpdateimageOrientation(DOUBLE[], UINT, ContentCaluse);
	// Orientation array,  patient id
	NTSTATUS UpdateimageOrientation(DOUBLE[], UINT, _String);
	//Orientation vector , caluse
	NTSTATUS UpdateimageOrientation(SerialDouble, ContentCaluse);
	//Orientation vector , patient id
	NTSTATUS UpdateimageOrientation(SerialDouble, _String);

	NTSTATUS DeleteAllRecord();
	NTSTATUS DeleteRecord(ContentCaluse);
	NTSTATUS DeleteOneRecordSerchById(INT);
	NTSTATUS DeleteRecordSerchByName(_String);

private:
	void FillingFirstPart(ContentValue&, DciomObject);
	void FillingMainlyPart(ContentValue&, DciomObject);
};


#endif // !__DICOMHEADTABLE_H
