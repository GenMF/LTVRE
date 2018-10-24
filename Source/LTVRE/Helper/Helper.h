#pragma once

#pragma region UE4 includes
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/Paths.h"
#pragma endregion

/// <summary>
/// static helper class
/// </summary>
class LTVRE_API Helper
{
public:
	/// <summary>
	/// get absolute path with file name
	/// </summary>
	/// <param name="_fileName">file name</param>
	/// <returns>absolute path with file name</returns>
	static FString GetAbsoluteFileName(FString _fileName)
	{
		// if app is running on mobile
		bool mobile = true;

		// if not Android or IOS set mobile false
		if (!UGameplayStatics::GetPlatformName().Contains("Android") && !UGameplayStatics::GetPlatformName().Contains("IOS"))
			mobile = false;

		// file name to return
		FString fileName;

		// if mobile app
		if (mobile)
		{
			// get save folder mobile
			fileName = "/sdcard/" + _fileName;
		}

		// if not mobile app
		else
		{
			// get save folder
			fileName = FPaths::ProjectSavedDir() + _fileName;
		}

		// return absolute path file name
		return fileName;
	}
};
