/*********************************************************************
 *   File: CommonDefines.hpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#pragma once

#ifndef US_COMMON_DEFINES_HPP
#define	US_COMMON_DEFINES_HPP

#include "Core/MinimalCore.hpp"

enum class ECollisionGroup : int32
{
	/// <summary>
	/// ECG_None
	/// </summary>
	ECG_CollisionGroup_0 = 0,
	/// <summary>
	/// ECG_WorldStatic
	/// </summary>
	ECG_CollisionGroup_1 = 1,
	/// <summary>
	/// ECG_WorldDynamic
	/// </summary>
	ECG_CollisionGroup_2 = 2,
	/// <summary>
	/// ECG_Pawn
	/// </summary>
	ECG_CollisionGroup_3 = 3,
	ECG_CollisionGroup_4 = 4,
	ECG_CollisionGroup_5 = 5,
	ECG_CollisionGroup_6 = 6,
	ECG_CollisionGroup_7 = 7,
	ECG_CollisionGroup_8 = 8,
	ECG_CollisionGroup_9 = 9,

	ECG_CollisionGroup_100 = 100,
	ECG_CollisionGroup_101 = 101,
	ECG_CollisionGroup_102 = 102,
	ECG_CollisionGroup_103 = 103,
	ECG_CollisionGroup_104 = 104,
	ECG_CollisionGroup_105 = 105,
	ECG_CollisionGroup_106 = 106,
	ECG_CollisionGroup_107 = 107,
	ECG_CollisionGroup_108 = 108,
	ECG_CollisionGroup_109 = 109,
	ECG_CollisionGroup_200 = 200,
};

enum class ECollisionMask : int32
{
	/// <summary>
	/// ECM_None
	/// </summary>
	ECM_CollisionMask_0 = 0,
	/// <summary>
	/// ECM_WorldStatic
	/// </summary>
	ECM_CollisionMask_1 = 1,
	ECM_CollisionMask_2 = 2,
	ECM_CollisionMask_3 = 3,
	ECM_CollisionMask_4 = 4,
};

enum class ECollisionObject : int32
{
	ECO_Dynamic   = btCollisionObject::CF_DYNAMIC_OBJECT,
	ECO_Static    = btCollisionObject::CF_STATIC_OBJECT,
	ECO_Kinematic = btCollisionObject::CF_KINEMATIC_OBJECT,
};

#define EnumAsInt(A) (int32)A

#define ECG_None          ECollisionGroup::ECG_CollisionGroup_0
#define ECG_WorldStatic   ECollisionGroup::ECG_CollisionGroup_1
#define ECG_WorldDynamic  ECollisionGroup::ECG_CollisionGroup_2
#define ECG_Pawn          ECollisionGroup::ECG_CollisionGroup_3


#define ECM_None          ECollisionMask::ECM_CollisionMask_0
#define ECM_WorldStatic   ECollisionMask::ECM_CollisionMask_1
#define ECM_WorldDynamic  ECollisionMask::ECM_CollisionMask_2


#define ECO_Dynamic    ECollisionObject::ECO_Dynamic
#define ECO_Static     ECollisionObject::ECO_Static
#define ECO_Kinematic  ECollisionObject::ECO_Kinematic


#endif // !US_COMMON_DEFINES_HPP