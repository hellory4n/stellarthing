using System.Threading.Tasks;

namespace starry;

/// <summary>
/// music systme
/// </summary>
public static class Music {
    /// <summary>
    /// song currently playing
    /// </summary>
    public static Audio? currentSong;
    /// <summary>
    /// the last song that played
    /// </summary>
    public static Audio? previousSong;
    public delegate void SongFinished();
    /// <summary>
    /// called when the song playing is finished
    /// </summary>
    public static event SongFinished? onSongFinished;
    /// <summary>
    /// if true, some song is playing.
    /// </summary>
    public static bool isSongPlaying { get; private set; } = false;
    static bool transitioning = false;
    static double theShitfuck3 = 0;

    /// <summary>
    /// pauses the current song
    /// </summary>
    public static bool paused {
        get => currentSong?.paused ?? false;
        set {
            if (currentSong != null) currentSong.paused = value;
        }
    }

    /// <summary>
    /// changes the song currently playing. if the current song isn't done yet, it's gonna fade out the song.
    /// </summary>
    public static async Task play(string file)
    {
        previousSong = currentSong;
        currentSong = await Starry.load<Audio>(file);

        if (isSongPlaying) {
            theShitfuck3 = 0;
            transitioning = true;
            currentSong.volume = 0;
        }
        else {
            currentSong.volume = 0.75; // TODO dont
            currentSong.play();
            isSongPlaying = true;

            currentSong.onAudioFinished += () => onSongFinished?.Invoke();
            currentSong.onAudioFinished += () => isSongPlaying = false;
        }
    }

    /// <summary>
    /// stops the current song
    /// </summary>
    public static void stop()
    {
        currentSong?.stop();
    }

    /// <summary>
    /// mate
    /// </summary>
    public static void update()
    {
        // help
        if (transitioning && previousSong != null && currentSong != null) {
            theShitfuck3 += Window.deltaTime;
            previousSong.volume = StMath.lerp(0.75, 0, theShitfuck3);

            if (theShitfuck3 >= 1) {
                currentSong.volume = 0.75; // TODO dont
                currentSong.play();
                transitioning = false;
            }
        }
    }
}