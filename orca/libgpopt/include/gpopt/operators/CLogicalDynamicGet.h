//---------------------------------------------------------------------------
//	Greenplum Database
//	Copyright (C) 2012 EMC Corp.
//
//	@filename:
//		CLogicalDynamicGet.h
//
//	@doc:
//		Dynamic table accessor for partitioned tables
//---------------------------------------------------------------------------
#ifndef GPOPT_CLogicalDynamicGet_H
#define GPOPT_CLogicalDynamicGet_H

#include "gpos/base.h"
#include "gpopt/operators/CLogicalDynamicGetBase.h"

namespace gpopt
{
	
	// fwd declarations
	class CTableDescriptor;
	class CName;
	class CColRefSet;
	
	//---------------------------------------------------------------------------
	//	@class:
	//		CLogicalDynamicGet
	//
	//	@doc:
	//		Dynamic table accessor
	//
	//---------------------------------------------------------------------------
	class CLogicalDynamicGet : public CLogicalDynamicGetBase
	{

		private:
	
			// private copy ctor
			CLogicalDynamicGet(const CLogicalDynamicGet &);

		public:
		
			// ctors
			explicit
			CLogicalDynamicGet(IMemoryPool *mp);

			CLogicalDynamicGet
				(
				IMemoryPool *mp,
				const CName *pnameAlias,
				CTableDescriptor *ptabdesc,
				ULONG ulPartIndex,
				CColRefArray *colref_array,
				CColRef2dArray *pdrgpdrgpcrPart,
				ULONG ulSecondaryPartIndexId,
				BOOL is_partial,
				CPartConstraint *ppartcnstr,
				CPartConstraint *ppartcnstrRel
				);
			
			CLogicalDynamicGet
				(
				IMemoryPool *mp,
				const CName *pnameAlias,
				CTableDescriptor *ptabdesc,
				ULONG ulPartIndex
				);

			// dtor
			virtual 
			~CLogicalDynamicGet();

			// ident accessors
			virtual 
			EOperatorId Eopid() const
			{
				return EopLogicalDynamicGet;
			}
			
			// return a string for operator name
			virtual 
			const CHAR *SzId() const
			{
				return "CLogicalDynamicGet";
			}
			
			// operator specific hash function
			virtual
			ULONG HashValue() const;

			// match function
			BOOL Matches(COperator *pop) const;

			// sensitivity to order of inputs
			BOOL FInputOrderSensitive() const;

			// return a copy of the operator with remapped columns
			virtual
			COperator *PopCopyWithRemappedColumns(IMemoryPool *mp, UlongToColRefMap *colref_mapping, BOOL must_exist);

			//-------------------------------------------------------------------------------------
			// Derived Relational Properties
			//-------------------------------------------------------------------------------------


			// derive join depth
			virtual
			ULONG JoinDepth
				(
				IMemoryPool *, // mp
				CExpressionHandle & // exprhdl
				)
				const
			{
				return 1;
			}

			//-------------------------------------------------------------------------------------
			// Required Relational Properties
			//-------------------------------------------------------------------------------------

			// compute required stat columns of the n-th child
			virtual
			CColRefSet *PcrsStat
				(
				IMemoryPool *, // mp,
				CExpressionHandle &, // exprhdl
				CColRefSet *, //pcrsInput
				ULONG // child_index
				)
				const
			{
				GPOS_ASSERT(!"CLogicalDynamicGet has no children");
				return NULL;
			}
			
			//-------------------------------------------------------------------------------------
			// Transformations
			//-------------------------------------------------------------------------------------
		
			// candidate set of xforms
			CXformSet *PxfsCandidates(IMemoryPool *mp) const;

			//-------------------------------------------------------------------------------------
			// Statistics
			//-------------------------------------------------------------------------------------

			// derive statistics
			virtual
			IStatistics *PstatsDerive
						(
						IMemoryPool *mp,
						CExpressionHandle &exprhdl,
						IStatisticsArray *stats_ctxt
						)
						const;

			// stat promise
			virtual
			EStatPromise Esp(CExpressionHandle &) const
			{
				return CLogical::EspHigh;
			}

			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
			//-------------------------------------------------------------------------------------
		
			// conversion function
			static
			CLogicalDynamicGet *PopConvert
				(
				COperator *pop
				)
			{
				GPOS_ASSERT(NULL != pop);
				GPOS_ASSERT(EopLogicalDynamicGet == pop->Eopid());
				
				return dynamic_cast<CLogicalDynamicGet*>(pop);
			}
			
			// debug print
			virtual 
			IOstream &OsPrint(IOstream &) const;

	}; // class CLogicalDynamicGet

}


#endif // !GPOPT_CLogicalDynamicGet_H

// EOF