using System;
using System.Collections.Concurrent;
namespace starry;

/// <summary>
/// A tile-based video game, or grid-based video game, is a type of video game where the playing area consists of small square (or, much less often, rectangular, parallelogram, or hexagonal) graphic images referred to as tiles laid out in a grid. That the screen is made of such tiles is a technical distinction, and may not be obvious to people playing the game. The complete set of tiles available for use in a playing area is called a tileset. Tile-based games usually simulate a top-down, side view, or 2.5D view of the playing area, and are almost always two-dimensional. 
/// </summary>
public static class Tilemap {
    /// <summary>
    /// the last underground layer
    /// </summary>
    public const int MIN_LAYER = -128;
    /// <summary>
    /// the last overworld layer
    /// </summary>
    public const int MAX_LAYER = 512;
    /// <summary>
    /// dimension of the chunks in amount of tiles (they're square)
    /// </summary>
    public const int CHUNK_DIMENSIONS = 32;

    /// <summary>
    /// dictionary of worlds, dictionary of chunks, list of layers, queue of tiles
    /// </summary>
    internal static ConcurrentDictionary<string, ConcurrentDictionary<vec2i, ConcurrentDictionary<int, ConcurrentQueue<Tile>>>> worlds = new();

    /// <summary>
    /// the current layers of each world
    /// </summary>
    public static ConcurrentDictionary<string, int> currentLayers { get; set; } = new();
    /// <summary>
    /// the current world. "" is space
    /// </summary>
    public static string currentWorld { get; set; } = "";
    /// <summary>
    /// the current chunks of each world
    /// </summary>
    public static ConcurrentDictionary<string, vec2i> currentChunks { get; set; } = new();
    static vec2 laposiciondelacamera = (0, 0);
    /// <summary>
    /// the position of the camera (in tile coordinates)
    /// </summary>
    public static vec2 camPosition {
        get => laposiciondelacamera;
        set {
            laposiciondelacamera = value;

            // without this, if you move to another chunk you stop being rendered and processed and as such
            // you're stuck there forever :)
            vec2i chunk = (value / (CHUNK_DIMENSIONS, CHUNK_DIMENSIONS)).floor();
            // generate new chunks :))
            if (!worlds[currentWorld].ContainsKey(chunk)) {
                ConcurrentDictionary<int, ConcurrentQueue<Tile>> man = new();
                worlds[currentWorld].TryAdd(chunk, man);
                for (int i = MIN_LAYER; i < MAX_LAYER; i++) {
                    man.TryAdd(i, []);
                }
            }
            currentChunks[currentWorld] = chunk;

            // idfk
            Audio.listener = value;
        }
    }
    /// <summary>
    /// the camera offset (in pixels)
    /// </summary>
    public static vec2 camOffset { get; set; } = Starry.settings.renderSize / (2, 2);
    /// <summary>
    /// the camera scale (multiplier)
    /// </summary>
    public static vec2 camScale { get; set; } = (1, 1);

    public static void create()
    {
        createWorld("");
    }

    /// <summary>
    /// adds a tile to the stuff
    /// </summary>
    public static void pushTile(Tile tile)
    {
        vec2i chunk = (tile.position.as2d() / (CHUNK_DIMENSIONS, CHUNK_DIMENSIONS)).floor();
        // FUCKER
        if (!worlds[tile.world].ContainsKey(chunk)) {
            ConcurrentDictionary<int, ConcurrentQueue<Tile>> man = new();
            worlds[tile.world].TryAdd(chunk, man);
            for (int i = MIN_LAYER; i < MAX_LAYER; i++) {
                man.TryAdd(i, []);
            }
        }

        // yesterday i went outside with my mama's mason jar caught a lovely butterfly when i woke up today looked in on my fairy pet she had withered all away no more sighing in her breast i'm sorry for what i did i did what my body told me to i didn't mean to do you harm every time i pin down what i think i want it slips away the ghost slips away smell you on my hand for days i can't wash away your scent if i'm a dog then you're a bitch i guess you're as real as me maybe i can live with that maybe i need fantasy life of chasing butterfly i'm sorry for what i did i did what my body told me to i didn't mean to do you harm every time i pin down what i think i want it slips away the ghost slips away i told you i would return when the robin makes his nest but i ain't never coming back i'm sorry i'm sorry i'm sorry
        worlds[tile.world][chunk][(int)Math.Round(tile.position.z)].Enqueue(tile);
    }

    /// <summary>
    /// creates a new world
    /// </summary>
    public static void createWorld(string name)
    {
        ConcurrentDictionary<vec2i, ConcurrentDictionary<int, ConcurrentQueue<Tile>>> world = new();
        world.TryAdd((0, 0), new());
        for (int i = MIN_LAYER; i < MAX_LAYER; i++) {
            world[(0, 0)].TryAdd(i, []);
        }
        worlds.TryAdd(name, world);
        currentLayers.TryAdd(name, 0);
        currentChunks.TryAdd(name, (0, 0));
    }

    public static void update()
    {
        // the render distance is every chunk around the current one (so 9)
        // having a variable render distance would be too much work lmao
        for (int y = -1; y < 2; y++) {
            for (int x = -1; x < 2; x++) {
                // you can't render a chunk if it doesn't exist
                if (!worlds[currentWorld].ContainsKey(currentChunks[currentWorld] + (x, y))) continue;

                ConcurrentQueue<Tile> bloodyTiles =
                    worlds[currentWorld][currentChunks[currentWorld] + (x, y)][currentLayers[currentWorld]];

                // hell
                while (!bloodyTiles.IsEmpty) {
                    bloodyTiles.TryDequeue(out Tile? tile);
                    if (tile == null || tile.sprite == null) continue;

                    ISprite sprite = tile.side switch {
                        TileSide.LEFT => tile.sprite.left,
                        TileSide.RIGHT => tile.sprite.right,
                        TileSide.TOP => tile.sprite.top,
                        TileSide.BOTTOM => tile.sprite.bottom,
                        _ => throw new Exception("shut up marge shut up"),
                    };

                    Graphics.drawSprite(
                        sprite,
                        (((tile.position.as2d() - camPosition) * Starry.settings.tileSize) + camOffset,
                        tile.sprite.getSize() * tile.scale * camScale),
                        tile.origin,
                        tile.rotation,
                        tile.tint
                    );
                }
            }
        }
    }
}