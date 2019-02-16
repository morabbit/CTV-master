#pragma once
#ifndef __FRAMEWORKERRORCODE_H
#define __FRAMEWORKERRORCODE_H

/**< Error code usage */

#define SUCCESSED                              0
/**< @all
  * operator success */


#define STATUS_FAILED                         -1
  /**< @all
	* operator failed */

//
//  MYSQL Error Code
//
#define MYSQL_DB_NAME_IS_NULL                 0x00010000
/**< @MysqlDataBase 
  * initialize mysql falied */

#define INITIALIZE_MYSQL_FAILED               0x00010001
/**< @MysqlDataBase 
  * initialize mysql falied */

#define CONNECT_MYSQL_SERVER_FAILED           0x00010002
/**< @MysqlDataBase 
  * connect mysql server falied */

#define CLOSED_MYSQL_SERVER_FAILED           0x00010003
/**< @MysqlDataBase 
  * close mysql server falied */

#define MYSQL_RESULT_NULL                    0x00010003
/**< @MysqlDataBase
* mysql result is NULL */

#define EXCUTE_MYSQL_FAILED                  0x00010004
/**< @MysqlDataBase
* excute sql is falied */

#define SQL_STATEMENT_SYNTAX_ERROR           0x00010005
/**< @MysqlDataBase
* mysql statement syntax error */

#define DATABASE_NAME_NULL                   0x00010006
/**< @MysqlDataBase
* Server address is null  */

#define DB_CONNECTION_POOL_FULL              0x00010007
/**< @MysqlDataBase
* database connection pool is full  */

#define MYSQL_UPDATE_NO_CLAUSE               0x00010008
/**< @MysqlDataBase
* no caulse set  */

//
//  sqlite Error Code
//
#define OPEN_SQLITE_DB_FAILED                0x00020000
/**< @SqliteDataBase
* open sqlite database failed  */

#define OPEN_SQLITE_DB_EXCEPTION             0x00020001
/**< @SqliteDataBase
* open sqlite database exception  */

#define SQLITE_FILE_NAME_IS_NULL             0x00020002
/**< @SqliteDataBase
* sqlite data base file name is null  */

#define SQLITE_CLOSED_FAILED                 0x00020003
/**< @SqliteDataBase
* sqlite database closed failed  */

#define SQLITE_CLOSED_EXCEPTION              0x00020004
/**< @SqliteDataBase
* sqlite database closed exception  */

#define SQLITE_FREE_RESULT_FALIED            0x00020005
/**< @SqliteDataBase
* sqlite database free result exception  */

#define SQLITE_EXCUTE_FALIED                 0x00020006
/**< @SqliteDataBase
* sqlite excute failed  */

#define SQLITE_EXCUTE_EXCEPTION              0x00020006
/**< @SqliteDataBase
* sqlite excute exception  */

//
// ImageImportExport error code
//

#define FILE_PATH_NOT_EXIST                  0x00030000
/**< @ImageImportExport					     
* the spcrify path do not exist  */		     
										     
#define READ_IMAGE_FALIED                    0x00030001
/**< @ImageImportExport					     
* read body data image failed  */		     
										     
#define IMPORT_BUFFER_TO_IMAGE_FAILED        0x00030002
/**< @ImageImportExport					     
* this buffer can not import to image   */   
										     
#define IMAGE_EXTENT_IS_NOT_MATCHED          0x00030003
/**< @ImageImportExport
* image entent name is incorrect as
* 2d should be : ".mhd", ".dcm", ".tif",
*    ".tiff", ".png" , ".bmp", "jpeg";
* but 3D image should be ".mhd", ".nii",
*    ".tif", ".tiff", ".nii.gz" */

#define ERROR_TO_GET_ELEMENT                 0x00030004
/**< @ImageImportExport
* read body data image failed  */

#define WRITE_IMAGE_FALIED                   0x00030005
/**< @ImageImportExport
*  write image failed  */

#define RGB_3D_NOT_SUPPORT                   0x00030006
/**< @ImageImportExport
*  RGB not support for 3d  */

#define ITK_2_VTK_FAILED                     0x00030007
/**< @ImageImportExport
*  itk transform to vtk data failed  */

#define VTK_2_ITK_FAILED                     0x00030008
/**< @ImageImportExport
*  vtk transform to itk data failed  */

#define VTK_CAST_IMAGE_FAILED                0x00030009
/**< @ImageImportExport
*  vtk transform to vtk cast image  data failed  */

#define IMAGE_DIMENSION_NOT_MATCH            0x0003000A
/**< @ImageImportExport
*  images dimension not match  */

#define GET_DICOM_PIXEL_SEQUENCE_FALIED      0x0003000B
/**< @ImageImportExport
* get dicom pixel sequence failed  */

#define COORDINATE_AXIS_NOMBER_ERROR         0x0003000C
/**< @FastReading
* cordinate axis number error  */

#define IMAGE_DATA_NULL                      0x0003000D
/**< @FastReading
* image data is null  */


#define ANOTHER_POINT_NOT_SET                0x00040000
/**< @MathematicalGeometry
* need 2 points , but both of then did
* not set , call those function will error */

#define ONLY_SUPPORT_TWO_POINTS              0x00040001
/**< @MathematicalGeometry
* here only support 2 points , the input
* index was out of points index */

#define FRAMEWORK_STATUS_FAIL                0x00050000
/**< @Tools
* excute segment failed */


#define IMAGE_NOT_EXIST                      0x00060001
/**< @findImagePoints
  * file path is incrrect or image not exist */

#define READ_IMAGE_ERROR                     0x00060002
/**< @findImagePoints
  * read image erroe , or image is
  * not formated as png or jpeg*/

#define INVALID_KERNEL_SIZE                  0x00060003
/**< @findImagePoints
  * Invalid sobel kernel size */

#define SOBEL_ERROR                          0x00060004
/**< @findImagePoints
  * sobel error happened and got an exception */

#define CANNY_GAUSS_ERROR                    0x00060005
/**< @findImagePoints
  * canny or gauss error happened
  * and got an exception */

#define GARY_IMAGE_IS_NULL                   0x00060006
/**< @findImagePoints
  * gary image is null */

#define INVALID_THRESHOLD_TYPE               0x00060007
/**< @findImagePoints
  * Threshold  type is invalid */

#define IMAGE_NOT_THRESHOLD                  0x00060008
/**< @findImagePoints
  * image not a gary image  */

#define FIND_CONTOURS_EXCEPTION              0x00060009
/**< @findImagePoints
  * findContours get an exception  */

#define THRESHOLD_ERROR                      0x0006000A
/**< @findImagePoints
  * Threshold  error and got an excetion */

#define POINT_OUT_OF_FRAME                   0x0006000B
/**< @PointFilterProcessing
  * point out of frame */

#define CANOT_RECOGNIZE_POINTS               0x0006000C
/**< @PointFilterProcessing
  * can not recognize points from image */

#define RESULT_BUFFER_ERROR                  0x0006000D
/**< @PointFilterProcessing
  * out put buffer fromat error,the 
  * pointer's pointer is null, at least 
  * input a pointer and the pointer 
  * point a null */

#define RADIUS_BUFFER_ERROR                  0x0006000E
/**< @PointFilterProcessing
  * out put radius buffer fromat 
  * error,the pointer's pointer is null , 
  * at least input a pointer and the 
  * pointer point a null */


#define POINTS_NUMBER_NULL                   0x00070001
/**< @OrderingProcessing
  * input points number is 0 */

#define POINTS_NUM_TOO_SMALL                 0x00070002
/**< @OrderingProcessing
  * input points number is too
  * small(point too less) */

#define BUFFER_DISMATCHED_WITTH_NUM          0x00070003
/**< @OrderingProcessing
  * input points number is too large
  * but points buffer is too small */

#define KMEANS_FALIED                        0x00070004
/**< @OrderingProcessing
  * input points are dissymmetry . 
  * those 2 parts are gap too match
  * with their points*/

#define GROUP_POINTS_TOO_LESS                0x00070005
/**< @OrderingProcessing
  * one gropu's points is too less 
  * to calculate center */

#define CLUSTER_POINTS_TOO_LESS              0x00070006
/**< @OrderingProcessing
  * cluster points is too less to 
  * calculate min distance */

#define CLUSTER_2_SCALE_IS_ZERO              0x00070007
/**< @OrderingProcessing
  * cluster 2 scale is 0 */

#define ORDERED_POINTS_SIZE_ZERO             0x00070008
/**< @OrderingProcessing
  * ordered point size is 0 */


#define CLEAR_POINTS_SIZE_ZERO               0x00080001
/**< @CLearPointsProcessing
  * input clear points size is 0 */

#define READ_CLEAR_IMAGE_ERROR               0x00080002
/**< @CLearPointsProcessing
  * read image erroe , or image is not 
  * formated as png or jpeg*/

#define POINTS_DISMATCHED_WITTH_NUM          0x00080003
/**< @CLearPointsProcessing
  * input points number is too large
  * but points buffer is too small */

#define INPAINT_IMAGE_FAILED                 0x00080004
/**< @CLearPointsProcessing
  * inpaint image error , Input 8-bit, 
  * 16-bit unsigned or 32-bit float
  * 1-channel or 8-bit 3-channel image, mask
  * 8-bit 1-channel image. Non-zero pixels 
  * indicate the area that needs to be
  * inpainted.*/

#define OUTPUT_IMAGE_BUFFER_SIZE_ZERO        0x00080005
/**< @CLearPointsProcessing
  * out put image buffer size is 0 */

#define OUT_BUFFER_DISMATCH_WITH_SIZE        0x00080006
/**< @CLearPointsProcessing
  * out put image buffer dismatch with buffer */

#define CALIBRATION_POINTS_SIZE_0            0x00090001
/**< @CameraExternalCalibrationProcessing
  * input Camera External Calibration 
  * points size is 0 */

#define BUFFER_2D_TOO_SAMLE                  0x00040002
/**< @CameraExternalCalibrationProcessing
  * 2D points buffer not matched with 
  * points number , buffer is too samle */

#define BUFFER_3D_TOO_SAMLE                  0x00090003
/**< @CameraExternalCalibrationProcessing
  * 3D points buffer not matched with 
  * points number , buffer is too samle */

#define INNERMATRIX_BUFFER_TOO_SMALL         0x00040004
/**< @CameraExternalCalibrationProcessing
  * input camera Internal matrix buffer is 
  * too small */

#define DIST_DOEFFS_BUFFER_TOO_SMALL         0x00090005
/**< @CameraExternalCalibrationProcessing
  * input camera distortion coefficient buffer is 
  * too small */

#define SOLVE_PNP_FALIED                     0x00040006
/**< @CameraExternalCalibrationProcessing
  * SolvePnP error, as the interal arguments 
  * and points has error parameter */

#define ROTATION_VECTOR_INCLUDE_NAN          0x00090007
/**< @CameraExternalCalibrationProcessing
  * Output rotation vector's (rvec) 
  * element has NAN */

#define TRANSLATION_VECTOR_INCLUDE_NAN       0x00090008
/**< @CameraExternalCalibrationProcessing
  * Output translation vector's (tvec)
  * element has NAN */

#define ROTATION_MATRIX_INCLUDE_NAN          0x00090009
/**< @CameraExternalCalibrationProcessing
  * Output rotation Matrix's (RxMatrix)
  * element has NAN */

#define MATRIX_REDIRECT_FAILED               0x0009000A
/**< @CameraExternalCalibrationProcessing
  * input to Mat_<double>(4,4) failed
  * with those input, need to check input
  * parameter is correct or not */

#define OUTER_MATRIX_INCLUDE_NAN             0x0009000B
/**< @CameraExternalCalibrationProcessing
  * Output Matrix's (exMatrix)
  * element has NAN */

#define PROJECT_POINTS_FAILED                0x0009000C
/**< @CameraExternalCalibrationProcessing
   * projectPoints error with those input */

#endif // !__FRAMEWORKERRORCODE_H
