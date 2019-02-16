#pragma once
#ifndef __LOADIMAGEHEAD_H
#define __LOADIMAGEHEAD_H
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"
#include "FrameWorkType.h"
#include "DicomValueObject.hxx"

template<class _Type>
class DcmtkLoadImage
{
public:
	DcmtkLoadImage();
	~DcmtkLoadImage();

	void LoadFile(CPCHAR __img_name);
	void ParseFileFormat();
	void FillingDicomObj();

	DciomObject GetData();
	NTSTATUS GetStatus();
	_String GetErrorMessage();
	
	std::shared_ptr<_Type>
		ReadDicomData(
			CPCHAR __img_name,
			ULONG& __cbBuf
		);

	std::shared_ptr<_Type>
		ReadDicomData(
			CPCHAR __img_name,
			ULONG& __cbBuf,
			INT __bitNoPerSample
		);

	static 
		std::shared_ptr<_Type>
		ReadDicomData2(
			CPCHAR __img_name,
			ULONG& __cbBuf,
			NTSTATUS _status = SUCCESSED,
			_StrStm_ _err_msg = _StrStm_()
		);

private:
	void __clear_var();
	OFString  __find_and_get_string(const DcmTagKey& _key);
	Uint32  __find_and_get_uint(const DcmTagKey& _key);

private:
	NTSTATUS __ldimg_status__;
	_StrStm_ __ldimg_err_msg__;
	DcmFileFormat __file_fmt__;
	DciomObject   __value__;
	DcmDataset * __p_data__;
};

typedef struct __LoadImageParam
{
	CPCHAR path;
	NTSTATUS status;
	_StrStm_ err_msg;
	DciomObject result;
}load_image;

DWORD WINAPI  LoadImageProc(void* p);

#endif // !__LOADIMAGEHEAD_H
