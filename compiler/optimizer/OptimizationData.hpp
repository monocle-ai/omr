/*******************************************************************************
 *
 * (c) Copyright IBM Corp. 2000, 2016
 *
 *  This program and the accompanying materials are made available
 *  under the terms of the Eclipse Public License v1.0 and
 *  Apache License v2.0 which accompanies this distribution.
 *
 *      The Eclipse Public License is available at
 *      http://www.eclipse.org/legal/epl-v10.html
 *
 *      The Apache License v2.0 is available at
 *      http://www.opensource.org/licenses/apache2.0.php
 *
 * Contributors:
 *    Multiple authors (IBM Corp.) - initial implementation and documentation
 *******************************************************************************/

#ifndef TR_OPTIMIZATIONDATA_INCL
#define TR_OPTIMIZATIONDATA_INCL

#include "compile/Compilation.hpp"      // for Compilation
#include "env/TRMemory.hpp"             // for Allocator, Allocatable, etc

namespace TR
{

class OptimizationData
	{
	public:

	static void *operator new(size_t size, TR::Allocator a)
           { return a.allocate(size); }
        static void  operator delete(void *ptr, size_t size)
           { ((OptimizationData*)ptr)->allocator().deallocate(ptr, size); } /* t->allocator() must return the same allocator as used for new */

        /* Virtual destructor is necessary for the above delete operator to work
         * See "Modern C++ Design" section 4.7
         */
        virtual ~OptimizationData() {}

        OptimizationData(TR::Compilation *comp) : _comp(comp) {}

	TR::Compilation *comp() { return _comp; }
	TR::Allocator allocator() { return comp()->allocator(); }

	private:
	TR::Compilation *_comp;
	};

}

#endif
