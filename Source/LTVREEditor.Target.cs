// usings
using UnrealBuildTool;
using System.Collections.Generic;

/// <summary>
/// editor target
/// </summary>
public class LTVREEditorTarget : TargetRules
{
    /// <summary>
    /// editor target
    /// </summary>
    /// <param name="Target">target info</param>
	public LTVREEditorTarget(TargetInfo Target) : base(Target)
	{
        // set target to editor
		Type = TargetType.Editor;

        // add modules
		ExtraModuleNames.AddRange( new string[] { "LTVRE" } );
	}
}