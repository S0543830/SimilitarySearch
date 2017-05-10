/***********************************************************************************************************************
*
* Copyright (c) 2016 by Tech Soft 3D, LLC.
* The information contained herein is confidential and proprietary to Tech Soft 3D, LLC., and considered a trade secret
* as defined under civil and criminal statutes. Tech Soft 3D shall pursue its civil and criminal remedies in the event
* of unauthorized use or misappropriation of its trade secrets. Use of this information by anyone other than authorized 
* employees of Tech Soft 3D, LLC. is granted only under a written non-disclosure agreement, expressly prescribing the 
* scope and manner of such use.
*
***********************************************************************************************************************/

/*!
\file
\brief      Header of <b>GOLD license for A3DLIBS</b>. 
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

/*!
\mainpage A3DLIBS V2.3 Gold option

*/



#ifndef __A3DSDKLICENSE_H__
#define __A3DSDKLICENSE_H__


/*!
\defgroup a3d_license_module License module
\brief Methods and structures dedicated to setting the license
\ingroup a3d_base_module
*/

/*!
\brief Function pointer
\ingroup a3d_license_module
\param [in] pcKey References the key to be set.
*/
typedef A3DInt32 (*PFA3DLicFunction)(const char *pcKey);


/*!
\brief Sets the license for the current instance of the library based on the two keys
\ingroup a3d_license_module
\param [in] pFunc The function pointer to the license-setting sub-function.
\param [in] pcCustomerKey	The customer key.
\param [in] pcVariableKey	The variable key.
*/
A3D_API (A3DInt32, A3DLicPutLicense,(const PFA3DLicFunction pFunc,
						 const A3DUTF8Char* pcCustomerKey,
						 const A3DUTF8Char* pcVariableKey));


/*!
\brief Sets the license for the current instance
\ingroup a3d_license_module
\param [in] pcKey The license to be set.
*/
A3D_API (A3DInt32, A3DLicPutLicenseFile,( const A3DUTF8Char *pcKey));

#endif	/*	__A3DSDKLICENSE_H__ */
