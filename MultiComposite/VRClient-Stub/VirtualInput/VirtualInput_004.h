#pragma once
#include "openvr.h"
#include "VirtualCommon.h"

using namespace vr;

class IVRInput_004
{
public:

	// ---------------  Handle management   --------------- //

	/** Sets the path to the action manifest JSON file that is used by this application. If this information
	* was set on the Steam partner site, calls to this function are ignored. If the Steam partner site
	* setting and the path provided by this call are different, VRInputError_MismatchedActionManifest is returned.
	* This call must be made before the first call to UpdateActionState or IVRSystem::PollNextEvent. */
	virtual EVRInputError SetActionManifestPath(const char* pchActionManifestPath) = 0;

	/** Returns a handle for an action set. This handle is used for all performance-sensitive calls. */
	virtual EVRInputError GetActionSetHandle(const char* pchActionSetName, VRActionSetHandle_t* pHandle) = 0;

	/** Returns a handle for an action. This handle is used for all performance-sensitive calls. */
	virtual EVRInputError GetActionHandle(const char* pchActionName, VRActionHandle_t* pHandle) = 0;

	/** Returns a handle for any path in the input system. E.g. /user/hand/right */
	virtual EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, VRInputValueHandle_t* pHandle) = 0;

	// --------------- Reading action state ------------------- //

	/** Reads the current state into all actions. After this call, the results of Get*Action calls
	* will be the same until the next call to UpdateActionState. */
	virtual EVRInputError UpdateActionState(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount) = 0;

	/** Reads the state of a digital action given its handle. This will return VRInputError_WrongType if the type of
	* action is something other than digital */
	virtual EVRInputError GetDigitalActionData(VRActionHandle_t action, InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) = 0;

	/** Reads the state of an analog action given its handle. This will return VRInputError_WrongType if the type of
	* action is something other than analog */
	virtual EVRInputError GetAnalogActionData(VRActionHandle_t action, InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) = 0;

	/** Reads the state of a pose action given its handle. */
	virtual EVRInputError GetPoseActionData(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, InputPoseActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) = 0;

	/** Reads the state of a skeletal action given its handle. */
	virtual EVRInputError GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice) = 0;

	// --------------- Skeletal Bone Data ------------------- //

	/** Reads the state of the skeletal bone data associated with this action and copies it into the given buffer. */
	virtual EVRInputError GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount, VRInputValueHandle_t ulRestrictToDevice) = 0;

	/** Reads the state of the skeletal bone data in a compressed form that is suitable for
	* sending over the network. The required buffer size will never exceed ( sizeof(VR_BoneTransform_t)*boneCount + 2).
	* Usually the size will be much smaller. */
	virtual EVRInputError GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize, VRInputValueHandle_t ulRestrictToDevice) = 0;

	/** Turns a compressed buffer from GetSkeletalBoneDataCompressed and turns it back into a bone transform array. */
	virtual EVRInputError DecompressSkeletalBoneData(void* pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace* peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount) = 0;

	// --------------- Haptics ------------------- //

	/** Triggers a haptic event as described by the specified action */
	virtual EVRInputError TriggerHapticVibrationAction(VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice) = 0;

	// --------------- Action Origins ---------------- //

	/** Retrieve origin handles for an action */
	virtual EVRInputError GetActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT(originOutCount) VRInputValueHandle_t* originsOut, uint32_t originOutCount) = 0;

	/** Retrieves the name of the origin in the current language */
	virtual EVRInputError GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char* pchNameArray, uint32_t unNameArraySize) = 0;

	/** Retrieves useful information for the origin of this action */
	virtual EVRInputError GetOriginTrackedDeviceInfo(VRInputValueHandle_t origin, InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize) = 0;

	/** Shows the current binding for the action in-headset */
	virtual EVRInputError ShowActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle) = 0;

	/** Shows the current binding all the actions in the specified action sets */
	virtual EVRInputError ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, VRInputValueHandle_t originToHighlight) = 0;
};

class VirtualInput_004 : public VirtualCommon, public IVRInput_004
{
public:
	void* GetFnTable();

	// ---------------  Handle management   --------------- //

	/** Sets the path to the action manifest JSON file that is used by this application. If this information
	* was set on the Steam partner site, calls to this function are ignored. If the Steam partner site
	* setting and the path provided by this call are different, VRInputError_MismatchedActionManifest is returned.
	* This call must be made before the first call to UpdateActionState or IVRSystem::PollNextEvent. */
	EVRInputError SetActionManifestPath(const char* pchActionManifestPath);

	/** Returns a handle for an action set. This handle is used for all performance-sensitive calls. */
	EVRInputError GetActionSetHandle(const char* pchActionSetName, VRActionSetHandle_t* pHandle);

	/** Returns a handle for an action. This handle is used for all performance-sensitive calls. */
	EVRInputError GetActionHandle(const char* pchActionName, VRActionHandle_t* pHandle);

	/** Returns a handle for any path in the input system. E.g. /user/hand/right */
	EVRInputError GetInputSourceHandle(const char* pchInputSourcePath, VRInputValueHandle_t* pHandle);

	// --------------- Reading action state ------------------- //

	/** Reads the current state into all actions. After this call, the results of Get*Action calls
	* will be the same until the next call to UpdateActionState. */
	EVRInputError UpdateActionState(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount);

	/** Reads the state of a digital action given its handle. This will return VRInputError_WrongType if the type of
	* action is something other than digital */
	EVRInputError GetDigitalActionData(VRActionHandle_t action, InputDigitalActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice);

	/** Reads the state of an analog action given its handle. This will return VRInputError_WrongType if the type of
	* action is something other than analog */
	EVRInputError GetAnalogActionData(VRActionHandle_t action, InputAnalogActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice);

	/** Reads the state of a pose action given its handle. */
	EVRInputError GetPoseActionData(VRActionHandle_t action, ETrackingUniverseOrigin eOrigin, float fPredictedSecondsFromNow, InputPoseActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice);

	/** Reads the state of a skeletal action given its handle. */
	EVRInputError GetSkeletalActionData(VRActionHandle_t action, InputSkeletalActionData_t* pActionData, uint32_t unActionDataSize, VRInputValueHandle_t ulRestrictToDevice);

	// --------------- Skeletal Bone Data ------------------- //

	/** Reads the state of the skeletal bone data associated with this action and copies it into the given buffer. */
	EVRInputError GetSkeletalBoneData(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount, VRInputValueHandle_t ulRestrictToDevice);

	/** Reads the state of the skeletal bone data in a compressed form that is suitable for
	* sending over the network. The required buffer size will never exceed ( sizeof(VR_BoneTransform_t)*boneCount + 2).
	* Usually the size will be much smaller. */
	EVRInputError GetSkeletalBoneDataCompressed(VRActionHandle_t action, EVRSkeletalTransformSpace eTransformSpace, EVRSkeletalMotionRange eMotionRange, VR_OUT_BUFFER_COUNT(unCompressedSize) void* pvCompressedData, uint32_t unCompressedSize, uint32_t* punRequiredCompressedSize, VRInputValueHandle_t ulRestrictToDevice);

	/** Turns a compressed buffer from GetSkeletalBoneDataCompressed and turns it back into a bone transform array. */
	EVRInputError DecompressSkeletalBoneData(void* pvCompressedBuffer, uint32_t unCompressedBufferSize, EVRSkeletalTransformSpace* peTransformSpace, VR_ARRAY_COUNT(unTransformArrayCount) VRBoneTransform_t* pTransformArray, uint32_t unTransformArrayCount);

	// --------------- Haptics ------------------- //

	/** Triggers a haptic event as described by the specified action */
	EVRInputError TriggerHapticVibrationAction(VRActionHandle_t action, float fStartSecondsFromNow, float fDurationSeconds, float fFrequency, float fAmplitude, VRInputValueHandle_t ulRestrictToDevice);

	// --------------- Action Origins ---------------- //

	/** Retrieve origin handles for an action */
	EVRInputError GetActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t digitalActionHandle, VR_ARRAY_COUNT(originOutCount) VRInputValueHandle_t* originsOut, uint32_t originOutCount);

	/** Retrieves the name of the origin in the current language */
	EVRInputError GetOriginLocalizedName(VRInputValueHandle_t origin, VR_OUT_STRING() char* pchNameArray, uint32_t unNameArraySize);

	/** Retrieves useful information for the origin of this action */
	EVRInputError GetOriginTrackedDeviceInfo(VRInputValueHandle_t origin, InputOriginInfo_t* pOriginInfo, uint32_t unOriginInfoSize);

	/** Shows the current binding for the action in-headset */
	EVRInputError ShowActionOrigins(VRActionSetHandle_t actionSetHandle, VRActionHandle_t ulActionHandle);

	/** Shows the current binding all the actions in the specified action sets */
	EVRInputError ShowBindingsForActionSet(VR_ARRAY_COUNT(unSetCount) VRActiveActionSet_t* pSets, uint32_t unSizeOfVRSelectedActionSet_t, uint32_t unSetCount, VRInputValueHandle_t originToHighlight);
};
