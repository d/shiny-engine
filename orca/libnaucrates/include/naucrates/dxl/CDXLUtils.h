//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2010 Greenplum, Inc.
//
//	@filename:
//		CDXLUtils.h
//
//	@doc:
//		Entry point for parsing and serializing DXL documents.
//---------------------------------------------------------------------------

#ifndef GPDXL_CDXLUtils_H
#define GPDXL_CDXLUtils_H

#include "gpos/base.h"
#include "gpos/common/CAutoP.h"
#include "gpos/io/IOstream.h"
#include "gpos/string/CWStringDynamic.h"

#include "naucrates/dxl/operators/CDXLNode.h"
#include "naucrates/dxl/xml/dxltokens.h"

#include "naucrates/md/CMDIdGPDB.h"
#include "naucrates/md/IMDCacheObject.h"

#include "naucrates/statistics/CStatistics.h"

#include <xercesc/util/XMLString.hpp>

namespace gpmd
{
	class CMDRequest;
}

namespace gpopt
{
	class CEnumeratorConfig;
	class CStatisticsConfig;
	class COptimizerConfig;
	class ICostModel;
}

namespace gpdxl
{
	using namespace gpos;
	using namespace gpmd;
	using namespace gpnaucrates;

	XERCES_CPP_NAMESPACE_USE

	// fwd decl
	class CParseHandlerDXL;
	class CDXLMemoryManager;
	class CQueryToDXLResult;
	
	typedef CDynamicPtrArray<CStatistics, CleanupRelease> CStatisticsArray;
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CDXLUtils
	//
	//	@doc:
	//		Entry point for parsing and serializing DXL documents.
	//
	//---------------------------------------------------------------------------
	class CDXLUtils 
	{
			
		private:

			// same as above but with a wide string parameter for the DXL document
			static 
			CParseHandlerDXL *GetParseHandlerForDXLString
				(
				IMemoryPool *,
				const CWStringBase *dxl_string,
				const CHAR *xsd_file_path
				);
			


		public:
			// helper functions for serializing DXL document header and footer, respectively
			static void SerializeHeader(IMemoryPool *, CXMLSerializer *);
			static void SerializeFooter(CXMLSerializer *);
			// helper routine which initializes and starts the xerces parser, 
			// and returns the top-level parse handler which can be used to
			// retrieve the parsed elements
			static 
			CParseHandlerDXL *GetParseHandlerForDXLString
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);
			
			// same as above but with DXL file name specified instead of the file contents
			static 
			CParseHandlerDXL *GetParseHandlerForDXLFile
				(
				IMemoryPool *,
				const CHAR *dxl_filename,
				const CHAR *xsd_file_path
				);

			// parse a DXL document containing a DXL plan
			static 
			CDXLNode *GetPlanDXLNode
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path,
				ULLONG *plan_id,
				ULLONG *plan_space_size
				);
			
			// parse a DXL document representing a query
			// to return the DXL tree representing the query and
			// a DXL tree representing the query output
			static 
			CQueryToDXLResult *ParseQueryToQueryDXLTree
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);
			
			// parse a DXL document containing a scalar expression
			static
			CDXLNode *ParseDXLToScalarExprDXLNode
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);

			// parse an MD request
			static 
			CMDRequest *ParseDXLToMDRequest
				(
				IMemoryPool *mp,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);
			
			// parse a list of mdids from a MD request message
			static 
			CMDRequest *ParseDXLToMDRequest
				(
				IMemoryPool *mp,
				const WCHAR *dxl_string,
				const CHAR *xsd_file_path
				);

			// parse optimizer config DXL
			static
			COptimizerConfig *ParseDXLToOptimizerConfig
				(
				IMemoryPool *mp,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);

			static 
			IMDCacheObjectArray *ParseDXLToIMDObjectArray
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);
			
			static 
			IMDCacheObjectArray *ParseDXLToIMDObjectArray
				(
				IMemoryPool *,
				const CWStringBase *dxl_string,
				const CHAR *xsd_file_path
				);
			
			// parse mdid from a metadata document
			static 
			IMDId *ParseDXLToMDId
				(
				IMemoryPool *,
				const CWStringBase *dxl_string,
				const CHAR *xsd_file_path
				);

			static 
			IMDCacheObject *ParseDXLToIMDIdCacheObj
				(
				IMemoryPool *,
				const CWStringBase *dxl_string,
				const CHAR *xsd_file_path
				);

			// parse statistics object from the statistics document
			static 
			CDXLStatsDerivedRelationArray *ParseDXLToStatsDerivedRelArray
				(
				IMemoryPool *,
				const CHAR *dxl_string,
				const CHAR *xsd_file_path
				);

			// parse statistics object from the statistics document
			static 
			CDXLStatsDerivedRelationArray *ParseDXLToStatsDerivedRelArray
				(
				IMemoryPool *,
				const CWStringBase *dxl_string,
				const CHAR *xsd_file_path
				);
			
			// translate the dxl statistics object to optimizer statistics object
			static
			CStatisticsArray *ParseDXLToOptimizerStatisticObjArray
				(
				IMemoryPool *mp,
				CMDAccessor *md_accessor,
				CDXLStatsDerivedRelationArray *dxl_derived_rel_stats_array
				);

			// extract the array of optimizer buckets from the dxl representation of
			// dxl buckets in the dxl derived column statistics object
			static
			CBucketArray *ParseDXLToBucketsArray
				(
				IMemoryPool *mp,
				CMDAccessor *md_accessor,
				CDXLStatsDerivedColumn *dxl_derived_col_stats
				);

			// serialize a DXL query tree into DXL Document
			static 
			void SerializeQuery
				(
				IMemoryPool *mp,
				IOstream& os,
				const CDXLNode *dxl_query_node,
								   const CDXLNodeArray *query_output_dxlnode_array,
								   const CDXLNodeArray *cte_producers,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);
			
			// serialize a ULLONG value
			static
			CWStringDynamic *SerializeULLONG
				(
				IMemoryPool *mp,
				ULLONG value
				);

			// serialize a plan into DXL
			static 
			void SerializePlan
				(
				IMemoryPool *mp,
				IOstream &os,
				const CDXLNode *node,
				ULLONG plan_id,
				ULLONG plan_space_size,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			static 
			CWStringDynamic *SerializeStatistics
				(
				IMemoryPool *mp,
				CMDAccessor *md_accessor,
				const CStatisticsArray *statistics_array,
				BOOL serialize_header_footer,
				BOOL indentation
				);

			// serialize statistics objects into DXL and write to stream
			static 
			void SerializeStatistics
				(
				IMemoryPool *mp,
				CMDAccessor *md_accessor,
				const CStatisticsArray *statistics_array,
				IOstream &os,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			// serialize metadata objects into DXL and write to stream
			static 
			void SerializeMetadata
				(
				IMemoryPool *mp,
				const IMDCacheObjectArray *imd_obj_array,
				IOstream &os,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			// serialize metadata ids into a MD request message
			static 
			void SerializeMDRequest
				(
				IMemoryPool *mp,
				CMDRequest *md_request,
				IOstream &os,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);
			
			// serialize a metadata id into a MD request message
			static 
			void SerializeMDRequest
				(
				IMemoryPool *mp,
				const IMDId *mdid,
				IOstream &os,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			// serialize a list of metadata objects into DXL
			static 
			CWStringDynamic *SerializeMetadata
				(
				IMemoryPool *,
				const IMDCacheObjectArray *,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);
			
			// serialize a metadata id into DXL
			static 
			CWStringDynamic *SerializeMetadata
				(
				IMemoryPool *mp,
				const IMDId *mdid,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			// serialize sample plans
			static
			CWStringDynamic *SerializeSamplePlans
				(
				IMemoryPool *mp,
				CEnumeratorConfig *enumerator_cfg,
				BOOL indentation
				);

			// serialize cost distribution plans
			static
			CWStringDynamic *SerializeCostDistr
				(
				IMemoryPool *mp,
				CEnumeratorConfig *enumerator_cfg,
				BOOL indentation
				);

			// serialize a metadata object into DXL
			static 
			CWStringDynamic *SerializeMDObj
				(
				IMemoryPool *,
				const IMDCacheObject *,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);
			
			// serialize a scalar expression into DXL
			static
			CWStringDynamic *SerializeScalarExpr
				(
				IMemoryPool *mp,
				const CDXLNode *node,
				BOOL serialize_document_header_footer,
				BOOL indentation
				);

			// create a GPOS dynamic string from a Xerces XMLCh array
			static 
			CWStringDynamic *CreateDynamicStringFromXMLChArray
				(
				CDXLMemoryManager *memory_manager,
				const XMLCh *
				);
			
			// create a GPOS string object from a base 64 encoded XML string
			static
			BYTE *CreateStringFrom64XMLStr
				(
				CDXLMemoryManager *memory_manager,
				const XMLCh *xml_string,
				ULONG *length
				);

			// create a GPOS dynamic string from a regular character array
			static 
			CWStringDynamic *CreateDynamicStringFromCharArray
				(
				IMemoryPool *mp,
				const CHAR *c
				);
			
			// create an MD name from a character array
			static 
			CMDName *CreateMDNameFromCharArray(IMemoryPool *mp, const CHAR *c);
			
			// create an MD name from a Xerces character array
			static 
			CMDName *CreateMDNameFromXMLChar(CDXLMemoryManager *memory_manager, const XMLCh *xml_string);
		
			// encode a byte array to a string
			static 
			CWStringDynamic *EncodeByteArrayToString
				(
				IMemoryPool *mp,
				const BYTE *byte,
				ULONG length
				);

			// serialize a list of integers into a comma-separate string
			template <typename T, void (*CleanupFn)(T*)>
			static 
			CWStringDynamic *Serialize
				(
				IMemoryPool *mp,
				const CDynamicPtrArray<T, CleanupFn> *arr
				);

			// serialize a list of lists of integers into a comma-separate string
			static
			CWStringDynamic *Serialize
				(
				IMemoryPool *mp,
				const ULongPtr2dArray *pdrgpul
				);

			// serialize a list of chars into a comma-separate string
			static
			CWStringDynamic *SerializeToCommaSeparatedString
				(
				IMemoryPool *mp,
				const CharPtrArray *pdrgpsz
				);

			// decode a byte array from a string
			static 
			BYTE *DecodeByteArrayFromString
				(
				IMemoryPool *mp,
				const CWStringDynamic *dxl_string,
				ULONG *length
				);
			
			static 
			CHAR *Read(IMemoryPool *mp, const CHAR *filename);
			
			// create a multi-byte character string from a wide character string
			static 
			CHAR *CreateMultiByteCharStringFromWCString(IMemoryPool *mp, const WCHAR *wc_string);
			
			// serialize a double value in a string
			static 
			CWStringDynamic *SerializeDouble
				(
				CDXLMemoryManager *memory_manager,
				CDouble value
				);

			// translate the optimizer datum from dxl datum object
			static
			IDatum *GetDatum
				(
				IMemoryPool *mp,
				CMDAccessor *md_accessor,
				const CDXLDatum *dxl_datum
				);

			// serialize Datum with given tag
			static
			void SerializeBound
					(
					IDatum *new_length,
					const CWStringConst *dxl_string,
					CXMLSerializer *xml_serializer
					);

#ifdef GPOS_DEBUG
			// debug print of the metadata relation
			static
			void DebugPrintMDIdArray(IOstream &os, IMdIdArray *mdid_array);
#endif
	};

	// serialize a list of integers into a comma-separate string
	template <typename T, void (*CleanupFn)(T*)>
	CWStringDynamic *
	CDXLUtils::Serialize
		(
		IMemoryPool *mp,
		const CDynamicPtrArray<T, CleanupFn> *dynamic_ptr_array
		)
	{
		CAutoP<CWStringDynamic> string_var(GPOS_NEW(mp) CWStringDynamic(mp));

		ULONG length = dynamic_ptr_array->Size();
		for (ULONG ul = 0; ul < length; ul++)
		{
			T value = *((*dynamic_ptr_array)[ul]);
			if (ul == length - 1)
			{
				// last element: do not print a comma
				string_var->AppendFormat(GPOS_WSZ_LIT("%d"), value);
			}
			else
			{
				string_var->AppendFormat(GPOS_WSZ_LIT("%d%ls"), value, CDXLTokens::GetDXLTokenStr(EdxltokenComma)->GetBuffer());
			}
		}

		return string_var.Reset();
	}

}

#endif // GPDXL_CDXLUtils_H

// EOF