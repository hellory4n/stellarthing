using System;
using System.Collections.Generic;
namespace starry;

/// <summary>
/// unitys particle symst5em
/// </summary>
public class Particles: IParticles {
    class Particle {
        public Timer? timer;
        public vec2 pos = (0, 0);
        public vec2 posstart = (0, 0);
        public vec2 posend = (0, 0);
        public double rot = 0;
        public double rotstart = 0;
        public double rotend = 0;
        public color color = color.white;
        public color colorstart = color.white;
        public color colorend = color.white;
        public double lerptime = 0;
        public double start = 0;
    }

    /// <summary>
    /// sprite used for the particles
    /// </summary>
    public required ISprite particle { get; set; }
    public required Func<uint> amountFunc { get; set; }
    public required Func<double> durationFunc { get; set; }
    public required Func<vec2> positionStartFunc { get; set; }
    public required Func<vec2> positionEndFunc { get; set; }
    public required Func<double> rotationStartFunc { get; set; }
    public required Func<double> rotationEndFunc { get; set; }
    public required Func<color> colorStartFunc { get; set; }
    public required Func<color> colorEndFunc { get; set; }

    ConcurrentHashSet<Particle> particles = [];

    /// <summary>
    /// makes a bunch of particles
    /// </summary>
    public void emit()
    {
        uint amount = amountFunc();
        for (int i = 0; i < amount; i++) {
            Timer timetimetimetimetimetimetimetimetime = new(durationFunc(), false);
            Particle laparticula = new() {
                timer = timetimetimetimetimetimetimetimetime,
                posstart = positionStartFunc(),
                posend = positionEndFunc(),
                rotstart = rotationStartFunc(),
                rotend = rotationEndFunc(),
                colorstart = colorStartFunc(),
                colorend = colorEndFunc(),
                start = Window.elapsedTime,
            };
            laparticula.pos = laparticula.posstart;
            laparticula.rot = laparticula.rotstart;
            laparticula.color = laparticula.colorstart;

            particles.Add(laparticula);
            timetimetimetimetimetimetimetimetime.timeout += () => particles.Remove(laparticula);
        }
    }

    /// <summary>
    /// renders the particles
    /// </summary>
    public void draw()
    {
        Queue<Particle> queuedForAnnihilation = [];
        foreach (Particle article in particles) {
            // don't kill your pc
            if (article.pos < (0, 0) || article.pos > Starry.settings.renderSize ||
            article.color.a == 0) {
                queuedForAnnihilation.Enqueue(article);
                continue;
            }

            // first lerp the fuckers
            article.lerptime = (Window.elapsedTime - article.start) / article.timer!.duration;
            article.pos = StMath.lerp(article.posstart, article.posstart + article.posend,
                article.lerptime);
            article.rot = StMath.lerp(article.rotstart, article.rotend, article.lerptime);
            article.color = StMath.lerp(article.colorstart, article.colorend, article.lerptime);

            // then fucking draw the fuckers
            Graphics.drawSprite(particle, (article.pos, particle.getSize()), (0.5, 0.5),
                article.rot, article.color);
        }

        // die
        while (queuedForAnnihilation.Count > 0) {
            particles.Remove(queuedForAnnihilation.Dequeue());
        }
    }
}