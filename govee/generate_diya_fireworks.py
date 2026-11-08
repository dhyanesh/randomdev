#!/usr/bin/env python3
"""
Diwali GIF: Large central flickering diya with fireworks popping around it.
For Govee Curtain Lights Pro (H70B6) - 30x32 pixel grid.
"""

import math
import random
from PIL import Image, ImageDraw

OUTPUT_DIR = "/Users/dhyanesh/dev/govee/diwali_gifs"
W, H = 30, 32
SCALE = 15

# Colors
GOLD = (255, 200, 50)
WARM_YELLOW = (255, 180, 0)
BRIGHT_YELLOW = (255, 240, 120)
DEEP_ORANGE = (255, 100, 0)
ORANGE = (255, 140, 20)
RED_ORANGE = (230, 70, 10)
RED = (220, 30, 30)
MAGENTA = (200, 50, 150)
PURPLE = (140, 40, 200)
TEAL = (0, 200, 180)
GREEN = (50, 220, 80)
WHITE = (255, 255, 255)
DARK_BG = (3, 1, 10)


class Firework:
    def __init__(self, start_frame, avoid_center=True):
        # Keep fireworks away from center diya area
        if avoid_center:
            side = random.choice(["left", "right", "top"])
            if side == "left":
                self.cx = random.randint(1, 8)
                self.cy = random.randint(2, 18)
            elif side == "right":
                self.cx = random.randint(21, 28)
                self.cy = random.randint(2, 18)
            else:  # top
                self.cx = random.randint(3, 26)
                self.cy = random.randint(1, 8)
        else:
            self.cx = random.randint(3, W - 4)
            self.cy = random.randint(2, 12)

        self.start = start_frame
        self.color = random.choice([
            (255, 80, 80),     # red
            (255, 200, 50),    # gold
            (200, 50, 200),    # magenta
            (50, 220, 200),    # teal
            (80, 255, 80),     # green
            (255, 140, 40),    # orange
            (100, 120, 255),   # blue
            (255, 100, 180),   # pink
        ])
        self.num_particles = random.randint(8, 14)
        self.particles = []
        for i in range(self.num_particles):
            angle = (2 * math.pi * i) / self.num_particles + random.uniform(-0.3, 0.3)
            speed = random.uniform(0.6, 1.8)
            self.particles.append((angle, speed))
        self.lifetime = random.randint(10, 14)

    def draw(self, img, draw, frame):
        t = frame - self.start
        if t < 0 or t > self.lifetime:
            return

        # Rising trail (2 frames)
        if t < 2:
            trail_y = self.cy + (2 - t) * 6
            for ty in range(max(0, int(trail_y) - 1), min(H, int(trail_y) + 2)):
                if 0 <= self.cx < W and 0 <= ty < H:
                    brightness = max(0.3, 1.0 - abs(ty - trail_y) * 0.3)
                    c = tuple(int(v * brightness) for v in WARM_YELLOW)
                    draw.point((self.cx, ty), fill=c)
            return

        # Burst phase
        burst_t = t - 2
        fade = max(0, 1.0 - burst_t / (self.lifetime - 2))

        # Flash at center on first burst frame
        if burst_t == 0:
            for dx in range(-1, 2):
                for dy in range(-1, 2):
                    px, py = self.cx + dx, self.cy + dy
                    if 0 <= px < W and 0 <= py < H:
                        draw.point((px, py), fill=WHITE)

        for angle, speed in self.particles:
            px = self.cx + math.cos(angle) * speed * burst_t
            py = self.cy + math.sin(angle) * speed * burst_t + burst_t * burst_t * 0.05  # gravity
            ipx, ipy = int(round(px)), int(round(py))

            if 0 <= ipx < W and 0 <= ipy < H:
                c = tuple(max(0, min(255, int(v * fade))) for v in self.color)
                existing = img.getpixel((ipx, ipy))
                blended = tuple(min(255, existing[i] + c[i]) for i in range(3))
                draw.point((ipx, ipy), fill=blended)

            # Sparkle trail
            if burst_t > 1 and fade > 0.3:
                px2 = self.cx + math.cos(angle) * speed * (burst_t - 1)
                py2 = self.cy + math.sin(angle) * speed * (burst_t - 1) + (burst_t - 1) ** 2 * 0.05
                ipx2, ipy2 = int(round(px2)), int(round(py2))
                if 0 <= ipx2 < W and 0 <= ipy2 < H:
                    trail_c = tuple(max(0, min(255, int(v * fade * 0.3))) for v in self.color)
                    existing = img.getpixel((ipx2, ipy2))
                    blended = tuple(min(255, existing[i] + trail_c[i]) for i in range(3))
                    draw.point((ipx2, ipy2), fill=blended)


def draw_large_diya(img, draw, frame):
    """Draw a large prominent diya at the bottom center of the frame."""
    cx = W // 2  # 15
    base_y = 26  # Bottom area

    # === DIYA BOWL (large, ~12px wide) ===
    # Bottom of bowl (widest) - row 0 (base_y + 2)
    for dx in range(-6, 7):
        shade = DEEP_ORANGE if abs(dx) > 4 else ORANGE
        draw.point((cx + dx, base_y + 2), fill=shade)

    # Bowl body - row -1 (base_y + 1)
    for dx in range(-5, 6):
        if abs(dx) <= 3:
            draw.point((cx + dx, base_y + 1), fill=ORANGE)
        else:
            draw.point((cx + dx, base_y + 1), fill=RED_ORANGE)

    # Bowl upper rim - row -2 (base_y)
    for dx in range(-5, 6):
        if abs(dx) <= 2:
            draw.point((cx + dx, base_y), fill=WARM_YELLOW)
        elif abs(dx) <= 4:
            draw.point((cx + dx, base_y), fill=ORANGE)
        else:
            draw.point((cx + dx, base_y), fill=DEEP_ORANGE)

    # Bowl inner lip (base_y - 1)
    for dx in range(-4, 5):
        if abs(dx) <= 1:
            draw.point((cx + dx, base_y - 1), fill=WARM_YELLOW)
        elif abs(dx) <= 3:
            draw.point((cx + dx, base_y - 1), fill=ORANGE)
        else:
            draw.point((cx + dx, base_y - 1), fill=RED_ORANGE)

    # Base/foot
    for dx in range(-3, 4):
        draw.point((cx + dx, base_y + 3), fill=RED_ORANGE)
    for dx in range(-2, 3):
        draw.point((cx + dx, base_y + 4), fill=DEEP_ORANGE)

    # === OIL surface (subtle shine) ===
    oil_shine = 0.7 + 0.3 * math.sin(frame * 0.15)
    for dx in range(-3, 4):
        c = tuple(int(v * oil_shine) for v in (180, 120, 20))
        draw.point((cx + dx, base_y - 1), fill=c)

    # === WICK ===
    draw.point((cx, base_y - 2), fill=(200, 180, 100))

    # === FLAME (large, flickering) ===
    # Use multiple noise sources for natural flicker
    flicker1 = math.sin(frame * 0.4) * 0.3
    flicker2 = math.sin(frame * 0.7 + 1.3) * 0.2
    flicker3 = math.sin(frame * 1.1 + 2.7) * 0.15
    flicker = flicker1 + flicker2 + flicker3  # -0.65 to +0.65

    flame_brightness = 0.75 + flicker * 0.35  # 0.52 to 0.98
    flame_sway = math.sin(frame * 0.25) * 1.2  # lateral sway

    # Flame layers (bottom to top: orange -> yellow -> bright yellow -> white tip)
    flame_base_y = base_y - 3

    # Layer 1: Base of flame (widest, orange)
    for dx in [-2, -1, 0, 1, 2]:
        sway_dx = dx + flame_sway
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            b = flame_brightness * (1.0 - abs(dx) * 0.15)
            c = tuple(max(0, min(255, int(v * b))) for v in DEEP_ORANGE)
            draw.point((px, flame_base_y), fill=c)

    # Layer 2: Lower-mid flame (orange-yellow)
    for dx in [-2, -1, 0, 1, 2]:
        sway_dx = dx + flame_sway * 0.9
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            b = flame_brightness * (1.0 - abs(dx) * 0.2)
            c = tuple(max(0, min(255, int(v * b))) for v in ORANGE)
            draw.point((px, flame_base_y - 1), fill=c)

    # Layer 3: Mid flame (warm yellow)
    for dx in [-1, 0, 1]:
        sway_dx = dx + flame_sway * 0.8
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            b = flame_brightness * (1.0 - abs(dx) * 0.15)
            c = tuple(max(0, min(255, int(v * b))) for v in WARM_YELLOW)
            draw.point((px, flame_base_y - 2), fill=c)

    # Layer 4: Upper-mid (bright yellow)
    for dx in [-1, 0, 1]:
        sway_dx = dx + flame_sway * 0.65
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            b = flame_brightness * (1.0 - abs(dx) * 0.2)
            c = tuple(max(0, min(255, int(v * b))) for v in GOLD)
            draw.point((px, flame_base_y - 3), fill=c)

    # Layer 5: Upper flame (bright)
    for dx in [0]:
        sway_dx = dx + flame_sway * 0.5
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            c = tuple(max(0, min(255, int(v * flame_brightness))) for v in BRIGHT_YELLOW)
            draw.point((px, flame_base_y - 4), fill=c)

    # Layer 6: Flame tip (white-ish, sometimes flickers out)
    if flame_brightness > 0.65:
        sway_dx = flame_sway * 0.35
        px = cx + int(round(sway_dx))
        if 0 <= px < W:
            tip_b = (flame_brightness - 0.5) * 2
            c = tuple(max(0, min(255, int(v * tip_b))) for v in (255, 250, 200))
            draw.point((px, flame_base_y - 5), fill=c)

    # === WARM GLOW around flame ===
    glow_center_y = flame_base_y - 2
    glow_radius = 6
    for gy in range(-glow_radius, glow_radius + 1):
        for gx in range(-glow_radius, glow_radius + 1):
            dist = math.sqrt(gx * gx + gy * gy)
            if 2.5 < dist <= glow_radius:
                px, py = cx + gx + int(flame_sway * 0.3), glow_center_y + gy
                if 0 <= px < W and 0 <= py < H:
                    glow_b = max(0, (glow_radius - dist) / glow_radius) * flame_brightness * 0.18
                    existing = img.getpixel((px, py))
                    glow_color = WARM_YELLOW
                    new_c = tuple(min(255, int(existing[i] + glow_b * glow_color[i])) for i in range(3))
                    draw.point((px, py), fill=new_c)

    # === LIGHT POOL on ground below diya ===
    pool_y_start = base_y + 5
    for py in range(pool_y_start, min(H, pool_y_start + 4)):
        pool_fade = 1.0 - (py - pool_y_start) / 4
        pool_w = 4 + (py - pool_y_start)
        for pdx in range(-pool_w, pool_w + 1):
            px = cx + pdx
            if 0 <= px < W and 0 <= py < H:
                dist_fade = 1.0 - abs(pdx) / (pool_w + 1)
                brightness = pool_fade * dist_fade * flame_brightness * 0.12
                existing = img.getpixel((px, py))
                new_c = tuple(min(255, int(existing[i] + brightness * WARM_YELLOW[i])) for i in range(3))
                draw.point((px, py), fill=new_c)


def generate():
    print("Generating Large Diya + Fireworks...")
    NUM_FRAMES = 60

    # Create fireworks that pop at staggered times throughout the loop
    random.seed(42)
    fireworks = []
    # Spread fireworks evenly, making sure some always visible
    spawn_times = [0, 4, 9, 14, 19, 25, 30, 35, 40, 44, 48, 52, 56]
    for t in spawn_times:
        fireworks.append(Firework(t))

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), DARK_BG)
        draw = ImageDraw.Draw(img)

        # Subtle twinkling stars in background
        random.seed(99)
        for _ in range(20):
            sx = random.randint(0, W - 1)
            sy = random.randint(0, 12)  # Only in upper sky
            base_b = random.randint(15, 40)
            twinkle = math.sin(f * 0.3 + sx * 0.7 + sy * 1.1)
            b = max(0, int(base_b + twinkle * 25))
            draw.point((sx, sy), fill=(b, b, b + 10))

        # Draw fireworks (behind the diya glow but visible)
        for fw in fireworks:
            fw.draw(img, draw, f)
            # Wrap-around: also check if firework should re-trigger for looping
            fw.draw(img, draw, f + NUM_FRAMES)

        # Draw the large central diya (on top of everything)
        draw_large_diya(img, draw, f)

        frames.append(img)

    # Save
    import os
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Native
    native_path = os.path.join(OUTPUT_DIR, "07_diya_fireworks_native.gif")
    frames[0].save(native_path, save_all=True, append_images=frames[1:],
                   duration=80, loop=0, optimize=True)
    sz = os.path.getsize(native_path) / 1024
    print(f"  Native: {native_path} ({sz:.1f} KB)")

    # Preview
    preview_path = os.path.join(OUTPUT_DIR, "07_diya_fireworks_preview.gif")
    scaled = [f.resize((W * SCALE, H * SCALE), Image.NEAREST) for f in frames]
    scaled[0].save(preview_path, save_all=True, append_images=scaled[1:],
                   duration=80, loop=0, optimize=True)
    sz = os.path.getsize(preview_path) / 1024
    print(f"  Preview: {preview_path} ({sz:.1f} KB)")


if __name__ == "__main__":
    generate()
    print("\n✅ Done!")
