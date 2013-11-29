//
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2013 Project Chrono
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be 
// found in the LICENSE file at the top level of the distribution
// and at http://projectchrono.org/license-chrono.txt.
//

#ifndef CHIRRNODEASSET_H
#define CHIRRNODEASSET_H

//////////////////////////////////////////////////
//
//   ChIrrNodeAsset.h
//
//   FOR IRRLICHT USERS ONLY!
//
//   HEADER file for CHRONO,
//	 Multibody dynamics engine
//
// ------------------------------------------------
//             www.deltaknowledge.com
// ------------------------------------------------
///////////////////////////////////////////////////


#include <irrlicht.h>
#include "assets/ChAsset.h"
#include "irrlicht_interface/ChIrrAppInterface.h"
#include "irrlicht_interface/ChIrrNode.h"





namespace chrono
{



/// Class for adding Irrlicht visualization to a ChPhysicsItem.
/// This must be added as an 'asset' to the item (ex., a ChBody).

class  ChIrrNodeAsset : public ChAsset {

protected:
				//
	  			// DATA
				//

	irr::scene::ChIrrNode* mnode;


public:
				//
	  			// CONSTRUCTORS
				//

	ChIrrNodeAsset () : mnode(0) //, mitem(0), mapp(0)
	{
	};

	virtual ~ChIrrNodeAsset () 
	{
		// remove irrlicht node from scene manager
		this->UnBind();
	};

	void Bind (chrono::ChSharedPtr<chrono::ChPhysicsItem> aitem, irr::ChIrrAppInterface& aapp) 
	{
		UnBind();

		mnode = new irr::scene::ChIrrNode(
									aitem, 
									aapp.GetContainer(), 
									aapp.GetSceneManager(),
									0);
		
		// Grab() to avoid dangling pointer if irrlicht scene is deleted before this obj:
		//  ***NOT NEEDED! Already done in ctor OF ISceneNode when attaching to parent
		//mnode->grab(); 

	};

	void UnBind()
	{
		if (mnode)
		{
			mnode->remove();
			
			mnode->drop();

			mnode = 0;
		}
	}


				//
	  			// FUNCTIONS
				//
	irr::scene::ISceneNode* GetIrrlichtNode() {return mnode;};

	virtual void Update() 
	{
		// inherit parent 
		ChAsset::Update();

		mnode->UpdateAssetsProxies();
	}

};




} // END_OF_NAMESPACE____


#endif // END 

