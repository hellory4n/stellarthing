using System;
using System.Diagnostics;
using System.Threading.Tasks;
namespace starry;

/// <summary>
/// debug mode :D
/// </summary>
public static class DebugMode {
    public static Task create() => Task.CompletedTask;
    public static Task update() => Task.CompletedTask;
}