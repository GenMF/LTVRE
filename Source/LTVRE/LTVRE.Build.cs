#region usings
using UnrealBuildTool;
#endregion

#region game class
/// <summary>
/// game class
/// </summary>
public class LTVRE : ModuleRules
{
	/// <summary>
	/// project
	/// </summary>
	/// <param name="Target">target rules</param>
	public LTVRE(ReadOnlyTargetRules Target) : base(Target)
	{
		// pch
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// public dependencies
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "XmlParser", "SlateCore" });

		// private dependencies
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
} 
#endregion