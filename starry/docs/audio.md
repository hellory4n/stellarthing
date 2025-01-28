# Audio

Starry has an audio system.

Supported formats are MP3, OGG, and WAV

Loading and playing an audio file is pretty simple

```cs
Audio handsomeAudio = load<Audio>("audio.mp3");
handsomeAudio.play();
```

Positional audio is also supported:

```cs
Audio mate = load<Audio>("metalpipe.mp3");
mate.position = (2, 2);
```

Setting the [tilemap](tilemap.md) camera position updates the position of the listener too

## Music

There's also music

```cs
Music.play("Kurt Cobain - Beans.mp3");
```

Switching songs automatically makes the previous one fade out, which is pretty cool I think.