// usings
using UnrealBuildTool;
using System.Collections.Generic;

/// <summary>
/// game target
/// </summary>
public class LTVRETarget : TargetRules
{
    /// <summary>
    /// game target
    /// </summary>
    /// <param name="Target">target info</param>
	public LTVRETarget(TargetInfo Target) : base(Target)
	{
        // set target to game
		Type = TargetType.Game;

        // add modules
		ExtraModuleNames.AddRange( new string[] { "LTVRE" } );
	}
}