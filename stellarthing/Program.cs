using System.IO;
using System.Linq;
using System.Threading.Tasks;
using starry;
using static starry.Starry;
namespace stellarthing;

internal class Program {
    internal static async Task Main(string[] args)
    {
        await create(new StarrySettings {
            startup = () => {
                Entities.addEntity(new Player());
            },
            verbose = isDebug() || args.Contains("--verbose") || args.Contains("-v"),
            gameName = "Stellarthing",
            gameVersion = (0, 11, 0),
            fullscreen = true,
            assetPath = Path.GetFullPath("assets"),
            keymap = new() {
                {"move_left", [Key.A, Key.LEFT]},
                {"move_right", [Key.D, Key.RIGHT]},
                {"move_up", [Key.W, Key.UP]},
                {"move_down", [Key.S, Key.DOWN]},
            }
        });
    }
}