using System;
using ManagedBass;
namespace starry;

/// <summary>
/// it's audio.
/// </summary>
public class Audio: IAsset {
    /// <summary>
    /// the position of the listener. <c>Tilemap.camPosition</c> overrides this.
    /// </summary>
    public static vec2 listener { get; set; } = (0, 0);
    int stream = 0;
    static ConcurrentHashSet<Audio> mate = [];

    vec2? pos = null;
    /// <summary>
    /// the position of the audio. setting it turns your audio into spatial audio, if you want it to go back for some reason just set it to null
    /// </summary>
    public vec2 position {
        get => pos ?? (0, 0);
        set {
            pos = value;
            vec2 delta = value - listener;
            double distance = Math.Sqrt(delta.x * delta.x + delta.y * delta.y);
            pan = Math.Clamp(delta.x / distance, -1, 1);
            volume = volume / volume + distance;
        }
    }

    double vol = 0;
    /// <summary>
    /// volume multiplier. 1 is the normal volume. this can't go above 300%
    /// </summary>
    public double volume {
        get => vol;
        set {
            vol = Math.Clamp(value, 0, 3);
            if (stream == 0) return;
            Bass.ChannelSetAttribute(stream, ChannelAttribute.Volume, vol + 1);
        }
    }

    double pain = 0;
    /// <summary>
    /// the stereo panning, -1 is completely on the left, 1 is completely on the right, 0 is on the center
    /// </summary>
    public double pan {
        get => pain;
        set {
            pain = Math.Clamp(value, -1, 1);
            if (stream == 0) return;
            Bass.ChannelSetAttribute(stream, ChannelAttribute.Pan, pain);
        }
    }

    bool elpauso = false;
    /// <summary>
    /// if true, the audio is paused.
    /// </summary>
    public bool paused {
        get => elpauso;
        set {
            elpauso = value;
            if (stream == 0) return;
            if (elpauso) Bass.ChannelPause(stream);
            else Bass.ChannelPlay(stream);
        }
    }

    public void load(string path)
    {
        Graphics.actions.Enqueue(() => {
            stream = Bass.CreateStream(path);
            if (stream != 0) {
                Starry.log($"Loaded audio file at {path}");
                mate.Add(this);
            }
            else {
                Starry.log($"Couldn't load audio file at {path}: {Bass.LastError}");
            }
        });
        Graphics.actionLoopEvent.Set();
    }

    public void cleanup() => mate.Remove(this);

    /// <summary>
    /// it plays audio :)
    /// </summary>
    public void play()
    {
        Graphics.actions.Enqueue(() => {
            if (stream == 0) return;
            Bass.ChannelPlay(stream);
        });
        Graphics.actionLoopEvent.Set();
    }

    /// <summary>
    /// it stops the audio :)
    /// </summary>
    public void stop() {
        Graphics.actions.Enqueue(() => {
            if (stream == 0) return;
            Bass.ChannelStop(stream);
        });
        Graphics.actionLoopEvent.Set();
    }

    // engine stuff
    public static void create()
    {
        Graphics.actions.Enqueue(() => {
            if (Bass.Init()) {
                Starry.log("Initialized Bass");
            }
            else {
                throw new Exception($"no more bass: {Bass.LastError}");
            }
        });
        Graphics.actionLoopEvent.Set();
    }

    // keeping this here just in case i change the backend idfk
    public static void cleanupButAtTheEndBecauseItCleansUpTheBackend() {}

    public static void update()
    {
        // i can't be fucking bothered
        // (this is so it updates to match whatever the listener position is now)
        foreach (Audio a in mate) {
            vec2 delta = a.position - listener;
            double distance = Math.Sqrt(delta.x * delta.x + delta.y * delta.y);
            a.pan = Math.Clamp(delta.x / distance, -1, 1);
            a.volume = a.volume / a.volume + distance;
        }
    }
}