#include "pch.h"
#include "FrameworkErrorCode.h"
#include "..\include\LoadImageHead.h"
#include "TraceLogExporter.h"

template<class _Type>
DcmtkLoadImage<_Type>::DcmtkLoadImage()
{
	__ldimg_status__ = SUCCESSED;
	__ldimg_err_msg__ = _StrStm_();
}
template<class _Type>
DcmtkLoadImage<_Type>::~DcmtkLoadImage()
{
}
template<class _Type>
void DcmtkLoadImage<_Type>::LoadFile(CPCHAR __img_name)
{
	__clear_var();
	PRINT_DBG("LoadFile : %s", __img_name);
	OFCondition __result = __file_fmt__.loadFile(__img_name);
	PRINT_DBG("__result = %d", __result.bad());
	if(OFTrue == __result.bad())
	{
		__ldimg_status__ = READ_IMAGE_FALIED;
		__ldimg_err_msg__ << __result.text() << ": reading file: " << __img_name << OFendl;
	}
}

template<class _Type>
void DcmtkLoadImage<_Type>::ParseFileFormat()
{	
	__clear_var();
	__p_data__ = __file_fmt__.getDataset();
}

template<class _Type>
void DcmtkLoadImage<_Type>::FillingDicomObj()
{
	__value__.nFlag = 1;
	__value__.patientId = __find_and_get_string(DCM_PatientID).c_str();
	__value__.patientName = __find_and_get_string(DCM_PatientName).c_str();
	__value__.studyInstanceUID = __find_and_get_string(DCM_StudyInstanceUID).c_str();
	__value__.studyID = __find_and_get_string(DCM_StudyID).c_str();
	__value__.seriesNO = atoi(__find_and_get_string(DCM_SeriesNumber).c_str());
	__value__.seriesInstanceUID = __find_and_get_string(DCM_SeriesInstanceUID).c_str();
	__value__.imageNO = atoi(__find_and_get_string(DCM_ReferenceImageNumber).c_str());
	__value__.patientSex = __find_and_get_string(DCM_PatientSex).c_str();
	__value__.patientBirthDate = __find_and_get_string(DCM_PatientBirthDate).c_str();
	__value__.seriesDescription = __find_and_get_string(DCM_SeriesDescription).c_str();
	__value__.institution = __find_and_get_string(DCM_InstitutionName).c_str();
	__value__.patientPosition = __find_and_get_string(DCM_PatientPosition).c_str();
	__value__.InstanceCreatorUID = __find_and_get_string(DCM_InstanceCreatorUID).c_str();
	__value__.InstanceCreationDate = __find_and_get_string(DCM_InstanceCreationDate).c_str();
	__value__.InstanceCreationTime = __find_and_get_string(DCM_InstanceCreationTime).c_str();

	__value__.kvp = atoi(__find_and_get_string(DCM_KVP).c_str());
	__value__.electricCurrent = atoi(__find_and_get_string(DCM_XRayTubeCurrent).c_str());
	__value__.W =atoi(__find_and_get_string(DCM_WindowWidth).c_str());
	__value__.L =atoi(__find_and_get_string(DCM_WindowCenter).c_str());

	PRINT_DBG("__value__.patientId = %s", __value__.patientId);
	PRINT_DBG("__value__.patientName = %s", __value__.patientName);
	PRINT_DBG("__value__.studyInstanceUID = %s",__value__.studyInstanceUID);
	PRINT_DBG("__value__.studyID = %s", __value__.studyID);
	PRINT_DBG("__value__.seriesNO = %d", __value__.seriesNO);
	PRINT_DBG("__value__.seriesInstanceUID = %", __value__.seriesInstanceUID);
	PRINT_DBG("__value__.imageNO = %d", __value__.imageNO);
	PRINT_DBG("__value__.patientSex = %s", __value__.patientSex);
	PRINT_DBG("__value__.patientBirthDate = %s", __value__.patientBirthDate);
	PRINT_DBG("__value__.seriesDescription = %s", __value__.seriesDescription);
	PRINT_DBG("__value__.institution = %s", __value__.institution);
	PRINT_DBG("__value__.patientPosition = %s", __value__.patientPosition);
	PRINT_DBG("__value__.InstanceCreatorUID = %s", __value__.InstanceCreatorUID);
	PRINT_DBG("__value__.InstanceCreationDate = %s", __value__.InstanceCreationDate);
	PRINT_DBG("__value__.InstanceCreationTime = %s", __value__.InstanceCreationTime);
	PRINT_DBG("__value__.kvp = %d", __value__.kvp);
	PRINT_DBG("__value__.electricCurrent = %d", __value__.electricCurrent);
	PRINT_DBG("__value__.W = %d", __value__.W);
	PRINT_DBG("__value__.L = %d", __value__.L);
}

template<class _Type>
DciomObject DcmtkLoadImage<_Type>::GetData()
{
	return __value__;
}

template<class _Type>
NTSTATUS DcmtkLoadImage<_Type>::GetStatus()
{
	return __ldimg_status__;
}

template<class _Type>
_String DcmtkLoadImage<_Type>::GetErrorMessage()
{
	return __ldimg_err_msg__.str();
}

template<class _Type>
std::shared_ptr<_Type>
DcmtkLoadImage<_Type>::ReadDicomData(CPCHAR __img_name, ULONG& __cbBuf)
{
	__clear_var();
	LoadFile(__img_name);
	STATUS_SUCCESS(__ldimg_status__);

	ParseFileFormat();

	DcmElement* __element = nullptr;
	__p_data__->findAndGetElement(DCM_PixelData, __element);

	if(true == __element->isEmpty())
	{
		__ldimg_status__ = READ_IMAGE_FALIED;
		__ldimg_err_msg__ << "Image load success, but can not got image data";
		return nullptr;
	}
	__cbBuf = __element->getLength();

	std::shared_ptr<_Type> result((_Type*)__element->getValue());
	return result;
	
}

template<class _Type>
std::shared_ptr<_Type> 
DcmtkLoadImage<_Type>::ReadDicomData(
	CPCHAR __img_name, ULONG & __cbBuf, INT __bitNoPerSample)
{
	DicomImage* __img = new DicomImage(__img_name);
	__cbBuf = __img->getOutputDataSize();
	if(__img == nullptr)
	{
		__ldimg_status__ = READ_IMAGE_FALIED;
		__ldimg_err_msg__ << "image read failed:: image is null";
		return nullptr;
	}
	if(0 == __img->isMonochrome())
	{
		__ldimg_status__ = READ_IMAGE_FALIED;
		__ldimg_err_msg__ << "image read failed:: image is monochrome";
		return nullptr;
	}
	if(__img->getStatus() != EIS_Normal)
	{
		__ldimg_status__ = READ_IMAGE_FALIED;
		__ldimg_err_msg__ << "image read failed:: image status is not EIS_Normal";
		return nullptr;
	}

	std::shared_ptr<_Type> result(
		(_Type*)__img->getOutputData(__bitNoPerSample)
	);

	return result;
}

template<class _Type>
std::shared_ptr<_Type>
DcmtkLoadImage<_Type>::ReadDicomData2(CPCHAR __img_name, ULONG& _cbBuf,
							  NTSTATUS _status, _StrStm_ _err_msg)
{
	DicomImage* __img = new DicomImage(__img_name);
	_cbBuf = __img->getOutputDataSize();

	if(__img == nullptr)
	{
		_status = READ_IMAGE_FALIED;
		_err_msg << "image read failed:: image is null";
		return nullptr;
	}
	if(0 == __img->isMonochrome())
	{
		_status = READ_IMAGE_FALIED;
		_err_msg << "image read failed:: image is monochrome";
		return nullptr;
	}
	if(__img->getStatus() != EIS_Normal)
	{
		_status = READ_IMAGE_FALIED;
		_err_msg << "image read failed:: image status is not EIS_Normal";
		return nullptr;
	}
	std::shared_ptr<_Type> result((_Type*)__img->getOutputData(16));
	
	return result;
}

template<class _Type>
OFString DcmtkLoadImage<_Type>::__find_and_get_string(const DcmTagKey& _key)
{
	OFString __str;
	__p_data__->findAndGetOFString(_key, __str);
	return __str;
}

template<class _Type>
Uint32 DcmtkLoadImage<_Type>::__find_and_get_uint(const DcmTagKey & _key)
{
	Uint32 __ret;
	__p_data__->findAndGetUint32(_key, __ret);
	return __ret;
}

template<class _Type>
void DcmtkLoadImage<_Type>::__clear_var()
{
	__ldimg_status__ = SUCCESSED;
	__ldimg_err_msg__ = _StrStm_();
}

DWORD WINAPI LoadImageProc(void * p)
{
	load_image* __ptr = (load_image*)p;
	DcmtkLoadImage<void> __dcmtk;
	__ptr->status = SUCCESSED;
	__ptr->err_msg = _StrStm_();
	__dcmtk.LoadFile(__ptr->path);

	if(__dcmtk.GetStatus() != SUCCESSED)
	{
		__ptr->status = __dcmtk.GetStatus();
		__ptr->err_msg << __dcmtk.GetErrorMessage();
		return 0;
	}
	__dcmtk.ParseFileFormat();
	__dcmtk.FillingDicomObj();

	__ptr->result = __dcmtk.GetData();

	return 0;
}
