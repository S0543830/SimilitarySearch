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
\brief      Header file for mathematical Operators.
\author     Tech Soft 3D
\version    9.1
\date       March 2016
\par		Copyright (c) 2016 by Tech Soft 3D, LLC. All rights reserved.
*/

#ifndef __A3DPRCMATH_H__
#define __A3DPRCMATH_H__

/*!
\defgroup a3d_maths Mathematical Module
\ingroup a3d_entitiesdata_module
*/

#ifndef __A3D_MATHFN_POLYNOM__
/*!
\defgroup A3D_mathfn1d_polynom Polynomial Function
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct1DPolynom.
*/
/*!
\brief Polynomial structure
\ingroup A3D_mathfn1d_polynom
\version 2.0

The array of coefficients is defined from least value to greatest value.
The following equation shows the result of this function for a third-degree polynomial (\ref m_uiSize is 3),
where \b t is the parameter and \b x the result:

<b><center>x = m_pdCoeffs[0] + m_pdCoeffs[1] * t + m_pdCoeffs[2] * t*t</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSize;			/*!< Size of next array. */
	A3DDouble* m_pdCoeffs;		/*!< Vector of coefficients. */
} A3DMathFct1DPolynomData;

/*!
\brief Populates the \ref A3DMathFct1DPolynomData structure
\ingroup A3D_mathfn1d_polynom
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DPolynomGet,(	const A3DMathFct1DPolynom* pMathFn,
															A3DMathFct1DPolynomData* pData));

/*!
\brief Creates ab \ref A3DMathFct1DPolynom from an \ref A3DMathFct1DPolynomData structure
\ingroup A3D_mathfn1d_polynom
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_MATH_INCONSISTENT_DATA \
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DPolynomCreate,(	const A3DMathFct1DPolynomData* pData,
																A3DMathFct1DPolynom** ppMathFn));

#endif	/*	__A3D_MATHFN_POLYNOM__ */

#ifndef __A3D_MATHFN_TRIGO__
/*!
\defgroup A3D_mathfn1d_trigo Trigonometric Function
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct1DTrigonometric.
*/
/*!
\brief Trigonometric structure
\ingroup A3D_mathfn1d_trigo
\version 2.0

The following equation shows the result of a trigonometric function, where \b t is the parameter and \b x is the result:

<b><center>x = m_dDCOffset + m_dAmplitude*cos((t*m_dFreq)-m_dPhase)</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dAmplitude;		/*!< Amplitude. */
	A3DDouble m_dPhase;			/*!< Phase. */
	A3DDouble m_dFreq;			/*!< Frequency. */
	A3DDouble m_dDCOffset;		/*!< DCOffset. */
} A3DMathFct1DTrigonometricData;

/*!
\brief Populates the \ref A3DMathFct1DTrigonometricData structure
\ingroup A3D_mathfn1d_trigo
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DTrigonometricGet,(	const A3DMathFct1DTrigonometric* pMathFn,
																	A3DMathFct1DTrigonometricData* pData));

/*!
\brief Creates an \ref A3DMathFct1DTrigonometric from an \ref A3DMathFct1DTrigonometricData structure
\ingroup A3D_mathfn1d_trigo
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DTrigonometricCreate,(	const A3DMathFct1DTrigonometricData* pData,
																		A3DMathFct1DTrigonometric** ppMathFn));

#endif	/*	__A3D_MATHFN_TRIGO__ */


#ifndef __A3D_MATHFN_FRACTION__
/*!
\defgroup A3D_mathfn1d_fraction Fraction Function
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct1DFraction.
*/
/*!
\brief Fraction structure
\ingroup A3D_mathfn1d_fraction
\version 2.0

The following equation shows the result of a fraction function, where \b t is the parameter and \b x is the result:

<b><center>x = m_pP(t) / m_pQ(t)</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMathFct1D* m_pP;			/*!< Numerator term of fraction. */
	A3DMathFct1D* m_pQ;			/*!< Denominator term of fraction. */
} A3DMathFct1DFractionData;

/*!
\brief Populates the \ref A3DMathFct1DFractionData structure
\ingroup A3D_mathfn1d_fraction
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DFractionGet,(const A3DMathFct1DFraction* pMathFn,
															A3DMathFct1DFractionData* pData));

/*!
\brief Creates an \ref A3DMathFct1DFraction from an \ref A3DMathFct1DFractionData structure
\ingroup A3D_mathfn1d_fraction
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_MATH_FRACTION_INCONSISTENT_NUMERATOR \n
\return \ref A3D_MATH_FRACTION_INCONSISTENT_DENOMINATOR \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DFractionCreate,(const A3DMathFct1DFractionData* pData,
																A3DMathFct1DFraction** ppMathFn));

#endif	/*	__A3D_MATHFN_FRACTION__ */

#ifndef __A3D_MATHFN_ARCTANCOS__
/*!
\defgroup A3D_mathfn1d_arctancos ArctanCos Function
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct1DArctanCos.
*/
/*!
\brief ArctanCos structure
\ingroup A3D_mathfn1d_arctancos
\version 2.0

The following equation shows the result of this function, where \b t is the parameter and \b x is the result:

<b><center>x = atan((m_dB * cos((t*m_dC) + m_dD))) *m_dA</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_dA;				/*!< */
	A3DDouble m_dB;				/*!< */
	A3DDouble m_dC;				/*!< */
	A3DDouble m_dD;				/*!< */
	A3DDouble m_dE;				/*!< Unused in this version. */
} A3DMathFct1DArctanCosData;

/*!
\brief Populates the \ref A3DMathFct1DArctanCosData structure
\ingroup A3D_mathfn1d_arctancos
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DArctanCosGet,(	const A3DMathFct1DArctanCos* pMathFn,
																A3DMathFct1DArctanCosData* pData));

/*!
\brief Creates an \ref A3DMathFct1DArctanCos from an \ref A3DMathFct1DArctanCosData structure
\ingroup A3D_mathfn1d_arctancos
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct1DArctanCosCreate,(	const A3DMathFct1DArctanCosData* pData,
																	A3DMathFct1DArctanCos** ppMathFn));

#endif	/*	__A3D_MATHFN_ARCTANCOS__ */

#ifndef __A3D_MATHFN_COMBINATION__
/*!
\defgroup A3D_mathfn1d_combination Combination Function
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct1DCombination.
*/
/*!
\brief Combination structure
\ingroup A3D_mathfn1d_combination
\version 2.0

The following equation shows the result of a linear combination of 3 functions (\ref m_uiSize is 2), where \b x is the result:

<b><center>x = m_pdCoeffs[0] * m_ppFunctions[0] + m_pdCoeffs[1] * m_ppFunctions[1] + m_pdCoeffs[2]</center></b>

\warning Size of \ref m_pdCoeffs is equal to size of \ref m_ppFunctions +1.
*/
typedef struct
{
	A3DUns16 m_usStructSize;		/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DUns32 m_uiSize;				/*!< Size of next arrays. */
	A3DMathFct1D** m_ppFunctions;	/*!< Array of functions. */
	A3DDouble* m_pdCoeffs;			/*!< Vector of coefficients (Size is \ref m_uiSize + 1). */
} A3DMathFct1DCombinationData;

/*!
\brief Populates the \ref A3DMathFct1DCombinationData structure
\ingroup A3D_mathfn1d_combination
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
\todo Not yet implemented
*/
A3D_API (A3DStatus, A3DMathFct1DCombinationGet,(const A3DMathFct1DCombination* pMathFn,
																A3DMathFct1DCombinationData* pData));

/*!
\brief Creates an \ref A3DMathFct1DCombination from an \ref A3DMathFct1DCombinationData structure
\ingroup A3D_mathfn1d_combination
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
\todo Not yet implemented
*/
A3D_API (A3DStatus, A3DMathFct1DCombinationCreate,(const A3DMathFct1DCombinationData* pData,
																	A3DMathFct1DCombination** ppMathFn));

#endif	/*	__A3D_MATHFN_COMBINATION__ */

#ifndef __A3D_MATHFN_LINEARTRANSFO__
/*!
\defgroup A3D_mathfn3d_lineartransfo 3D Linear Transformation
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct3DLinear.
*/
/*!
\brief Linear transformation
\ingroup A3D_mathfn3d_lineartransfo
\version 2.0

The following equation shows the result of a linear transformation, where u,v,w are the parameters and x,y,z the results:

<b><center>x = m_adMatrix[0][0] * u + m_adMatrix[1][0] * v + m_adMatrix[2][0] * w + m_adVector[0]</center></b>
<b><center>y = m_adMatrix[0][1] * u + m_adMatrix[1][1] * v + m_adMatrix[2][1] * w + m_adVector[1]</center></b>
<b><center>z = m_adMatrix[0][2] * u + m_adMatrix[1][2] * v + m_adMatrix[2][2] * w + m_adVector[2]</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;	/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DDouble m_adMatrix[3][3];	/*!< Transformation matrix. */
	A3DDouble m_adVector[3];	/*!< Translation vector. */
} A3DMathFct3DLinearData;

/*!
\brief Populates the \ref A3DMathFct3DLinearData structure
\ingroup A3D_mathfn3d_lineartransfo
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct3DLinearGet,(	const A3DMathFct3DLinear* pMathFn,
															A3DMathFct3DLinearData* pData));

/*!
\brief Creates an \ref A3DMathFct3DLinear from an \ref A3DMathFct3DLinearData structure
\ingroup A3D_mathfn3d_lineartransfo
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct3DLinearCreate,(	const A3DMathFct3DLinearData* pData,
																A3DMathFct3DLinear** ppMathFn));

#endif	/*	__A3D_MATHFN_LINEARTRANSFO__ */

#ifndef __A3D_MATHFN_NONLINEARTRANSFO__
/*!
\defgroup A3D_mathfn3d_nonlineartransfo 3D Non-Linear Transformation
\ingroup a3d_maths
Entity type is \ref kA3DTypeMathFct3DNonLinear.
*/
/*!
\brief Non Linear transformation
\ingroup A3D_mathfn3d_nonlineartransfo
\version 2.0

The following equation shows the result of a non-linear transformation, 
where u,v,w are the parameters, x,y,z the results, and a,b,c the temporary result:

<b><center>Apply \ref m_pLeftLinear to (u,v,w) to get (a,b,c)</center></b>
<b><center>a = a * cos(b * m_d2)</center></b>
<b><center>b = b * sin(b * m_d2)</center></b>
<b><center>c unchanged</center></b>
<b><center>Apply \ref m_pRightLinear to (a,b,c) to get (x,y,z)</center></b>

*/
typedef struct
{
	A3DUns16 m_usStructSize;			/*!< Reserved; must be initialized with \ref A3D_INITIALIZE_DATA. */
	A3DMathFct3DLinear* m_pLeftLinear;	/*!< Left transformation matrix. */
	A3DMathFct3DLinear* m_pRightLinear;	/*!< Right transformation matrix. */
	A3DDouble m_d2;						/*!< Coefficient for the trigonometric function. */
} A3DMathFct3DNonLinearData;

/*!
\brief Populates the \ref A3DMathFct3DNonLinearData structure
\ingroup A3D_mathfn3d_nonlineartransfo
\version 2.0

\return \ref A3D_INITIALIZE_NOT_CALLED \n
\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INVALID_ENTITY_NULL \n
\return \ref A3D_INVALID_ENTITY_TYPE \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct3DNonLinearGet,(	const A3DMathFct3DNonLinear* pMathFn,
																A3DMathFct3DNonLinearData* pData));

/*!
\brief Creates an \ref A3DMathFct3DNonLinear from an \ref A3DMathFct3DNonLinearData structure
\ingroup A3D_mathfn3d_nonlineartransfo
\version 2.0

\return \ref A3D_INVALID_DATA_STRUCT_SIZE \n
\return \ref A3D_INVALID_DATA_STRUCT_NULL \n
\return \ref A3D_INTERVAL_INCONSISTENT_DATA \n
\return \ref A3D_SUCCESS \n
*/
A3D_API (A3DStatus, A3DMathFct3DNonLinearCreate,(	const A3DMathFct3DNonLinearData* pData,
																	A3DMathFct3DNonLinear** ppMathFn));

#endif	/*	__A3D_MATHFN_NONLINEARTRANSFO__ */

#endif	/*	__A3DPRCMATH_H__ */
