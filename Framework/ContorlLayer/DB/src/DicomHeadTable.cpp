#include "pch.h"
#include "..\include\DicomHeadTable.h"


DicomHeadTable::DicomHeadTable()
{
}

DicomHeadTable::~DicomHeadTable()
{
}

_String DicomHeadTable::GetTaleName()
{
	return "DicomHeadTable";
}

NTSTATUS DicomHeadTable::CreateTable()
{
	TableColum __colum;
	__colum.put("id", "INTEGER", false, true, "", true, false);
	//__colum.put("DisplayName", "CHAR(255)", true, true);
	__colum.put("patientId", "INT", true, true);
	__colum.put("patientName", "CHAR(100)", true);
	__colum.put("studyInstanceUID", "CHAR(255)");
	__colum.put("studyID", "CHAR(255)");
	__colum.put("seriesNO", "FLOAT");
	__colum.put("seriesInstanceUID", "CHAR(255)");
	__colum.put("imageNO", "CHAR(255)");
	__colum.put("patientSex", "CHAR(24)");
	__colum.put("patientBirthDate", "CHAR(255)");
	__colum.put("seriesDescription", "CHAR(255)");
	__colum.put("institution", "CHAR(255)");
	__colum.put("kvp", "INT");
	__colum.put("electricCurrent", "INT");
	__colum.put("InstanceCreationDate", "CHAR(255)");
	__colum.put("InstanceCreationTime", "CHAR(255)");
	__colum.put("InstanceCreatorUID", "CHAR(255)");
	__colum.put("Sapcing", "CHAR(255)");
	__colum.put("ImageSize", "CHAR(255)");
	__colum.put("patientPosition", "CHAR(255)");
	__colum.put("imagePosition", "CHAR(255)");
	__colum.put("imageOrientation", "CHAR(255)");
	__colum.put("origin", "CHAR(255)");
	__colum.put("maxValue", "INT");
	__colum.put("minValue", "INT");
	__colum.put("Width", "INT");
	__colum.put("Level", "INT");

	NTSTATUS status = create_table2(GetTaleName(), __colum);

	return status;
}

NTSTATUS 
DicomHeadTable::Instert(DciomObject __head)
{
	ContentValue __values;
	FillingFirstPart(__values, __head);
	FillingMainlyPart(__values, __head);

	NTSTATUS status = insert2(GetTaleName(), __values);
	return status;
}

NTSTATUS DicomHeadTable::InstertBasicHead(DciomObject __head)
{
	ContentValue __values;
	FillingFirstPart(__values, __head);
	NTSTATUS status = insert2(GetTaleName(), __values);

	return status;
}

NTSTATUS DicomHeadTable::InstertMainlyHead(DciomObject __head)
{
	ContentValue __values;
	FillingMainlyPart(__values, __head);
	NTSTATUS status = insert2(GetTaleName(), __values);

	return status;
}

NTSTATUS DicomHeadTable::UpdateMainlyHead(DciomObject __head)
{
	
	ContentCaluse __cdt;
	__cdt.equal(
		"patientId",
		__head.patientId
	).And().equal(
		"patientName",
		__head.patientName
	);
	ContentValue __values;
	FillingMainlyPart(__values, __head);
	NTSTATUS status = update2(GetTaleName(), __values, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateSapcing(
	DOUBLE dx, DOUBLE dy, DOUBLE dz, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << dx << ", " << dy << ", " << dz << "]";
	ContentValue __value;
	__value.put("Sapcing", __msg.str());

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS
DicomHeadTable::UpdateSapcing(
	DOUBLE dx, DOUBLE dy, DOUBLE dz, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << dx << ", " << dy << ", " << dz << "]";
	ContentValue __value;
	__value.put("Sapcing", __msg.str());
	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateSapcing(DOUBLE __spacing[3], ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << __spacing[0] << ", " 
		<< __spacing[1] << ", " 
		<< __spacing[2] << "]";
	ContentValue __value;
	__value.put("Sapcing", __msg.str());

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS DicomHeadTable::UpdateSapcing(DOUBLE  __spacing[3], _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << __spacing[0] << ", "
		<< __spacing[1] << ", "
		<< __spacing[2] << "]";

	ContentValue __value;
	__value.put("Sapcing", __msg.str());

	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateImageSize(
	UINT nx, UINT ny, UINT nz, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << nx << ", " << ny << ", " << nz << "]";
	ContentValue __value;
	__value.put("ImageSize", __msg.str());

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS DicomHeadTable::UpdateImageSize(UINT nx, UINT ny, UINT nz, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << nx << ", " << ny << ", " << nz << "]";
	ContentValue __value;
	__value.put("ImageSize", __msg.str());

	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS DicomHeadTable::UpdateImageSize(UINT __i_size[3], ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << __i_size[0] << ", "
		<< __i_size[1] << ", "
		<< __i_size[2] << "]";
	ContentValue __value;
	__value.put("ImageSize", __msg.str());

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS DicomHeadTable::UpdateImageSize(UINT __i_size[3], _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << __i_size[0] << ", "
		<< __i_size[1] << ", "
		<< __i_size[2] << "]";
	ContentValue __value;
	__value.put("ImageSize", __msg.str());

	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS
DicomHeadTable::UpdatePosition(
	DOUBLE x, DOUBLE y, DOUBLE z, _String __cloum, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << x << ", " << y << ", " << z << "]";
	ContentValue __value;
	__value.put(__cloum, __msg.str());

	NTSTATUS status = update2("DicomHeadTable", __value, __cdt);
	return status;
}

NTSTATUS
DicomHeadTable::UpdatePosition(
	DOUBLE x, DOUBLE y, DOUBLE z,
	_String __cloum, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << x << ", " << y << ", " << z << "]";
	ContentValue __value;
	__value.put(__cloum, __msg.str());
	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdatePosition(
	Point3f __pos, _String __cloum, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[" << __pos.x << ", " << __pos.y << ", " << __pos.z << "]";
	ContentValue __value;
	__value.put(__cloum, __msg.str());

	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS
DicomHeadTable::UpdatePosition(
	Point3f __pos, _String __cloum, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[" << __pos.x << ", " << __pos.y << ", " << __pos.z << "]";
	ContentValue __value;
	__value.put(__cloum, __msg.str());
	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateimageOrientation(
	DOUBLE rotate[], UINT size, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[";
	for(UINT i = 0; i < size; i++)
	{
		__msg << rotate[i];
		if(i < size - 1)
		{
			__msg << ", ";
		}
		else
		{
			__msg << "]";
		}
	}
	ContentValue __value;
	__value.put("imageOrientation", __msg.str());
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS
DicomHeadTable::UpdateimageOrientation(
	DOUBLE rotate[], UINT size, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[";
	for(UINT i = 0; i < size; i++)
	{
		__msg << rotate[i];
		if(i < size - 1)
		{
			__msg << ", ";
		}
		else
		{
			__msg << "]";
		}
	}
	ContentValue __value;
	__value.put("imageOrientation", __msg.str());
	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateimageOrientation(
	SerialDouble rotate, ContentCaluse __cdt)
{
	_StrStm_ __msg;
	__msg << "[";
	auto ns = rotate.size();
	for(size_t i = 0; i < ns; i++)
	{
		__msg << rotate[i];
		if(i < ns - 1)
		{
			__msg << ", ";
		}
		else
		{
			__msg << "]";
		}
	}

	ContentValue __value;
	__value.put("imageOrientation", __msg.str());
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS 
DicomHeadTable::UpdateimageOrientation(SerialDouble rotate, _String __pid)
{
	_StrStm_ __msg;
	__msg << "[";
	auto ns = rotate.size();
	for(size_t i = 0; i < ns; i++)
	{
		__msg << rotate[i];
		if(i < ns - 1)
		{
			__msg << ", ";
		}
		else
		{
			__msg << "]";
		}
	}

	ContentValue __value;
	__value.put("imageOrientation", __msg.str());
	ContentCaluse __cdt;
	__cdt.equal("patientId", __pid);
	NTSTATUS status = update2(GetTaleName(), __value, __cdt);
	return status;
}

NTSTATUS DicomHeadTable::DeleteAllRecord()
{
	return deleting2(GetTaleName(), ContentCaluse());
}

NTSTATUS DicomHeadTable::DeleteRecord(ContentCaluse __cdt)
{
	return deleting2(GetTaleName(), __cdt);
}

NTSTATUS DicomHeadTable::DeleteOneRecordSerchById(INT id)
{
	ContentCaluse __caluse;
	__caluse.equal("id", id);	

	return deleting2(GetTaleName(), __caluse);
}

NTSTATUS DicomHeadTable::DeleteRecordSerchByName(_String __name)
{
	ContentCaluse __caluse;
	__caluse.equal("patientName", __name);

	return deleting2(GetTaleName(), __caluse);
}

void
DicomHeadTable::FillingFirstPart(
	ContentValue &__values, DciomObject __head)
{
	__values.put("patientId", __head.patientId);
	__values.put("patientName", __head.patientName);
	__values.put("studyInstanceUID", __head.studyInstanceUID);
	__values.put("studyID", __head.studyID);
	__values.put("seriesNO", __head.seriesNO);
	__values.put("seriesInstanceUID", __head.seriesInstanceUID);
	__values.put("imageNO", __head.imageNO);
	__values.put("patientSex", __head.patientSex);
	__values.put("patientBirthDate", __head.patientBirthDate);
	__values.put("seriesDescription", __head.seriesDescription);
	__values.put("institution", __head.institution);
	__values.put("kvp", __head.kvp);
	__values.put("electricCurrent", __head.electricCurrent);
	__values.put("InstanceCreationDate", __head.InstanceCreationDate);
	__values.put("InstanceCreationTime", __head.InstanceCreationTime);
	__values.put("InstanceCreatorUID", __head.InstanceCreatorUID);
	__values.put("patientPosition", __head.patientPosition);
	__values.put("maxValue", __head.maxValue);
	__values.put("minValue", __head.minValue);
	__values.put("Width", __head.W);
	__values.put("Level", __head.L);

}

void 
DicomHeadTable::FillingMainlyPart(
	ContentValue &__values, DciomObject __head)
{
	_StrStm_ __msg[5];
	__msg[0] << "[" << __head.dx << ", " << __head.dy << ", " << __head.dy << "]";
	__msg[1] << "[" << __head.nx << ", " << __head.ny << ", " << __head.ny << "]";
	__msg[2] << "[" << __head.imagePosition.x << ", "
		<< __head.imagePosition.y << ", "
		<< __head.imagePosition.z << "]";
	__msg[4] << "[" << __head.origin[0] << ", "
		<< __head.origin[1] << ", "
		<< __head.origin[2] << "]";

	__msg[3] << "[";
	for(size_t i = 0; i < __head.imageOrientation.size(); i++)
	{
		__msg[3] << __head.imageOrientation[i];
		if(i < __head.imageOrientation.size() - 1)
		{
			__msg[3] << ", ";
		}
		else
		{
			__msg[3] << "]";
		}
	}
	__values.put("Sapcing", __msg[0].str());
	__values.put("ImageSize", __msg[1].str());
	__values.put("imagePosition", __msg[2].str());
	__values.put("imageOrientation", __msg[3].str());
	__values.put("origin", __msg[4].str());
}
