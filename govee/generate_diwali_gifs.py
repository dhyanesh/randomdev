#!/usr/bin/env python3
"""
Generate Diwali-themed animated GIFs for Govee Curtain Lights Pro (H70B6).
Grid: 30 columns × 32 rows, 960 RGBIC LEDs.
Target: under 700KB per GIF, up to 30fps.
"""

import math
import random
from PIL import Image, ImageDraw

OUTPUT_DIR = "/Users/dhyanesh/dev/govee/diwali_gifs"

W, H = 30, 32
SCALE = 15  # Preview scale (each pixel = 15x15 in preview)

# Color palettes
GOLD = (255, 200, 50)
WARM_YELLOW = (255, 180, 0)
DEEP_ORANGE = (255, 100, 0)
RED = (220, 30, 30)
MAGENTA = (200, 50, 150)
PURPLE = (120, 40, 180)
DARK_PURPLE = (60, 10, 80)
GREEN = (30, 180, 60)
TEAL = (0, 180, 160)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
DARK_BG = (5, 2, 15)
WARM_BG = (15, 5, 5)


def save_gif(frames, filename, duration=100, scale=SCALE):
    """Save frames as both native-res and scaled preview GIF."""
    import os
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Save native resolution (30x32) for Govee upload
    native_path = os.path.join(OUTPUT_DIR, f"{filename}_native.gif")
    frames[0].save(
        native_path,
        save_all=True,
        append_images=frames[1:],
        duration=duration,
        loop=0,
        optimize=True,
    )
    size_kb = os.path.getsize(native_path) / 1024
    print(f"  Native: {native_path} ({size_kb:.1f} KB)")

    # Save scaled preview
    preview_path = os.path.join(OUTPUT_DIR, f"{filename}_preview.gif")
    scaled = []
    for f in frames:
        s = f.resize((W * scale, H * scale), Image.NEAREST)
        scaled.append(s)
    scaled[0].save(
        preview_path,
        save_all=True,
        append_images=scaled[1:],
        duration=duration,
        loop=0,
        optimize=True,
    )
    size_kb = os.path.getsize(preview_path) / 1024
    print(f"  Preview: {preview_path} ({size_kb:.1f} KB)")


# ============================================================
# 1. FLOATING DIYAS (Oil lamps floating upward with flames)
# ============================================================
def generate_floating_diyas():
    print("\n1. Generating Floating Diyas...")
    NUM_FRAMES = 30

    # Diya shape (relative coords) - small bowl with flame
    def draw_diya(draw, cx, cy, flame_phase):
        """Draw a small diya at (cx, cy)"""
        # Bowl
        for dx in range(-2, 3):
            if abs(dx) <= 2:
                draw.point((cx + dx, cy + 1), fill=DEEP_ORANGE)
        for dx in range(-1, 2):
            draw.point((cx + dx, cy), fill=WARM_YELLOW)
        # Wick
        draw.point((cx, cy - 1), fill=WHITE)
        # Flame (flickers)
        flame_colors = [GOLD, WARM_YELLOW, (255, 220, 100)]
        fc = flame_colors[flame_phase % len(flame_colors)]
        draw.point((cx, cy - 2), fill=fc)
        if flame_phase % 3 != 0:
            draw.point((cx - 1, cy - 2), fill=(255, 150, 30))
        if flame_phase % 3 != 1:
            draw.point((cx + 1, cy - 2), fill=(255, 150, 30))
        draw.point((cx, cy - 3), fill=(255, 220, 100, 180))

    # Define diya positions and speeds
    diyas = [
        {"x": 5, "y_start": 28, "speed": 0.8},
        {"x": 12, "y_start": 30, "speed": 1.0},
        {"x": 20, "y_start": 26, "speed": 0.6},
        {"x": 26, "y_start": 32, "speed": 0.9},
        {"x": 8, "y_start": 34, "speed": 0.7},
        {"x": 16, "y_start": 29, "speed": 1.1},
        {"x": 24, "y_start": 33, "speed": 0.5},
    ]

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), DARK_BG)
        draw = ImageDraw.Draw(img)

        # Subtle star sparkles in background
        random.seed(42)  # Consistent stars
        for _ in range(15):
            sx, sy = random.randint(0, W-1), random.randint(0, H-1)
            brightness = random.randint(30, 80)
            if (f + sx + sy) % 5 == 0:
                brightness = min(255, brightness + 60)
            draw.point((sx, sy), fill=(brightness, brightness, brightness + 30))

        for d in diyas:
            y = d["y_start"] - f * d["speed"]
            y_wrapped = y % (H + 8) - 4
            if 2 <= y_wrapped <= H - 2:
                draw_diya(draw, d["x"], int(y_wrapped), f)

        frames.append(img)

    save_gif(frames, "01_floating_diyas", duration=100)


# ============================================================
# 2. RANGOLI MANDALA (Expanding colorful rangoli pattern)
# ============================================================
def generate_rangoli():
    print("\n2. Generating Rangoli Mandala...")
    NUM_FRAMES = 40
    cx, cy = W // 2, H // 2

    rangoli_colors = [RED, GOLD, MAGENTA, TEAL, GREEN, PURPLE, DEEP_ORANGE, WHITE]

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), DARK_PURPLE)
        draw = ImageDraw.Draw(img)

        max_radius = int(f * 0.5) + 3

        for y in range(H):
            for x in range(W):
                dx = x - cx
                dy = y - cy
                dist = math.sqrt(dx * dx + dy * dy)
                angle = math.atan2(dy, dx)

                if dist <= max_radius:
                    # Create concentric ring pattern with angular symmetry
                    ring = int(dist) % len(rangoli_colors)
                    # 8-fold symmetry
                    sym_angle = abs(((angle + math.pi) % (math.pi / 4)) - math.pi / 8)
                    petal = sym_angle < (0.15 + 0.05 * math.sin(f * 0.3))

                    if int(dist) % 3 == 0:
                        c = rangoli_colors[ring % len(rangoli_colors)]
                    elif petal:
                        c = rangoli_colors[(ring + 2) % len(rangoli_colors)]
                    else:
                        c = rangoli_colors[(ring + 4) % len(rangoli_colors)]

                    # Fade at edges
                    if dist > max_radius - 2:
                        fade = (max_radius - dist) / 2
                        c = tuple(int(v * max(0, min(1, fade))) for v in c)

                    draw.point((x, y), fill=c)

        # Center dot
        draw.point((cx, cy), fill=WHITE)

        frames.append(img)

    save_gif(frames, "02_rangoli_mandala", duration=80)


# ============================================================
# 3. FIREWORKS BURST (Diwali crackers/fireworks)
# ============================================================
def generate_fireworks():
    print("\n3. Generating Fireworks...")
    NUM_FRAMES = 45

    class Firework:
        def __init__(self, start_frame):
            self.cx = random.randint(5, W - 5)
            self.cy = random.randint(5, H // 2 + 5)
            self.start = start_frame
            self.color = random.choice([GOLD, RED, MAGENTA, TEAL, GREEN, PURPLE, DEEP_ORANGE])
            self.particles = []
            num_particles = random.randint(8, 16)
            for i in range(num_particles):
                angle = (2 * math.pi * i) / num_particles + random.uniform(-0.2, 0.2)
                speed = random.uniform(0.5, 2.0)
                self.particles.append((angle, speed))

        def draw(self, draw_ctx, frame):
            t = frame - self.start
            if t < 0 or t > 15:
                return

            # Rising trail before burst
            if t < 3:
                trail_y = self.cy + (3 - t) * 5
                if trail_y < H:
                    draw_ctx.point((self.cx, int(trail_y)), fill=WARM_YELLOW)
                    if trail_y + 1 < H:
                        draw_ctx.point((self.cx, int(trail_y) + 1), fill=DEEP_ORANGE)
                return

            # Burst
            burst_t = t - 3
            brightness = max(0, 1.0 - burst_t / 12)
            for angle, speed in self.particles:
                px = self.cx + int(math.cos(angle) * speed * burst_t)
                py = self.cy + int(math.sin(angle) * speed * burst_t + burst_t * 0.3)  # gravity
                if 0 <= px < W and 0 <= py < H:
                    c = tuple(int(v * brightness) for v in self.color)
                    draw_ctx.point((px, py), fill=c)
                    # Sparkle trail
                    if burst_t < 6:
                        px2 = self.cx + int(math.cos(angle) * speed * (burst_t - 1))
                        py2 = self.cy + int(math.sin(angle) * speed * (burst_t - 1) + (burst_t - 1) * 0.3)
                        if 0 <= px2 < W and 0 <= py2 < H:
                            draw_ctx.point((px2, py2), fill=tuple(int(v * brightness * 0.4) for v in self.color))

    random.seed(123)
    fireworks = [Firework(s) for s in [0, 5, 10, 18, 22, 28, 32, 36]]

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), (2, 2, 10))
        draw = ImageDraw.Draw(img)

        # Ground / skyline silhouette
        for x in range(W):
            ground_h = 30 + int(math.sin(x * 0.5) * 1)
            for y in range(ground_h, H):
                draw.point((x, y), fill=(10, 8, 5))

        for fw in fireworks:
            fw.draw(draw, f)

        frames.append(img)

    save_gif(frames, "03_fireworks", duration=80)


# ============================================================
# 4. SHUBH DEEPAVALI TEXT with sparkle border
# ============================================================
def generate_text_sparkle():
    print("\n4. Generating Shubh Deepavali Text with Sparkle Border...")
    NUM_FRAMES = 30

    # "दीपावली" or "DIWALI" in pixel font (simplified)
    # Let's do "DIWALI" centered, with decorative border
    # Each letter is 3-4px wide, 5px tall

    letters = {
        'D': [(0,0),(0,1),(0,2),(0,3),(0,4),(1,0),(1,4),(2,1),(2,2),(2,3)],
        'I': [(0,0),(1,0),(2,0),(1,1),(1,2),(1,3),(0,4),(1,4),(2,4)],
        'W': [(0,0),(0,1),(0,2),(0,3),(0,4),(1,3),(2,2),(3,3),(4,0),(4,1),(4,2),(4,3),(4,4)],
        'A': [(1,0),(0,1),(2,1),(0,2),(1,2),(2,2),(0,3),(2,3),(0,4),(2,4)],
        'L': [(0,0),(0,1),(0,2),(0,3),(0,4),(1,4),(2,4)],
    }

    # Layout "DIWALI" centered
    word = [('D', 3), ('I', 3), ('W', 5), ('A', 3), ('L', 3), ('I', 3)]
    total_w = sum(w for _, w in word) + len(word) - 1  # gaps
    start_x = (W - total_w) // 2
    text_y = 13  # vertical center area

    text_pixels = []
    cx = start_x
    for letter, lw in word:
        for dx, dy in letters[letter]:
            text_pixels.append((cx + dx, text_y + dy))
        cx += lw + 1

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), DARK_BG)
        draw = ImageDraw.Draw(img)

        # Decorative border - twinkling lights
        border_colors = [RED, GOLD, GREEN, MAGENTA, TEAL, DEEP_ORANGE]
        for i in range(W):
            c_idx = (i + f) % len(border_colors)
            brightness = 0.5 + 0.5 * math.sin((i + f * 0.5) * 0.8)
            c = tuple(int(v * brightness) for v in border_colors[c_idx])
            draw.point((i, 0), fill=c)
            draw.point((i, H - 1), fill=c)
        for j in range(H):
            c_idx = (j + f) % len(border_colors)
            brightness = 0.5 + 0.5 * math.sin((j + f * 0.5) * 0.8)
            c = tuple(int(v * brightness) for v in border_colors[c_idx])
            draw.point((0, j), fill=c)
            draw.point((W - 1, j), fill=c)

        # Second border ring
        for i in range(1, W - 1):
            c = border_colors[(i + f + 3) % len(border_colors)]
            b = 0.3 + 0.3 * math.sin((i + f * 0.3) * 1.2)
            c = tuple(int(v * b) for v in c)
            draw.point((i, 1), fill=c)
            draw.point((i, H - 2), fill=c)
        for j in range(1, H - 1):
            c = border_colors[(j + f + 3) % len(border_colors)]
            b = 0.3 + 0.3 * math.sin((j + f * 0.3) * 1.2)
            c = tuple(int(v * b) for v in c)
            draw.point((1, j), fill=c)
            draw.point((W - 2, j), fill=c)

        # Diya at top center
        dcx = W // 2
        draw.point((dcx - 1, 4), fill=DEEP_ORANGE)
        draw.point((dcx, 4), fill=WARM_YELLOW)
        draw.point((dcx + 1, 4), fill=DEEP_ORANGE)
        draw.point((dcx, 3), fill=WHITE)
        flame_c = GOLD if f % 3 != 0 else WARM_YELLOW
        draw.point((dcx, 2), fill=flame_c)

        # Small diyas at bottom
        for diya_x in [5, 10, 15, 20, 25]:
            draw.point((diya_x, H - 4), fill=DEEP_ORANGE)
            draw.point((diya_x - 1, H - 4), fill=WARM_YELLOW)
            draw.point((diya_x + 1, H - 4), fill=WARM_YELLOW)
            draw.point((diya_x, H - 5), fill=WHITE)
            fc = GOLD if (f + diya_x) % 4 != 0 else (255, 220, 100)
            draw.point((diya_x, H - 6), fill=fc)

        # Draw text with color cycling
        for px, py in text_pixels:
            phase = (f * 0.2 + px * 0.1) % 1.0
            if phase < 0.33:
                tc = GOLD
            elif phase < 0.66:
                tc = WARM_YELLOW
            else:
                tc = WHITE
            draw.point((px, py), fill=tc)

        # Sparkles around text
        random.seed(f * 7)
        for _ in range(8):
            sx = random.randint(3, W - 4)
            sy = random.randint(8, 22)
            if (sx, sy) not in text_pixels:
                draw.point((sx, sy), fill=(255, 255, 200))

        frames.append(img)

    save_gif(frames, "04_diwali_text", duration=120)


# ============================================================
# 5. DIYA GRID WAVE (Grid of diyas with a wave of light)
# ============================================================
def generate_diya_wave():
    print("\n5. Generating Diya Grid Wave...")
    NUM_FRAMES = 40

    # Place diyas in a grid pattern
    diya_positions = []
    for row in range(4):
        for col in range(5):
            x = 3 + col * 6
            y = 4 + row * 7
            diya_positions.append((x, y))

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), (8, 3, 12))
        draw = ImageDraw.Draw(img)

        # Subtle rangoli dots on floor
        for x in range(0, W, 4):
            for y in range(0, H, 4):
                draw.point((x, y), fill=(25, 10, 30))

        wave_x = (f / NUM_FRAMES) * (W + 20) - 10

        for dx, dy in diya_positions:
            dist_to_wave = abs(dx - wave_x)
            glow = max(0, 1.0 - dist_to_wave / 8)

            # Bowl
            for bx in range(-2, 3):
                bc = tuple(int(v * (0.3 + 0.7 * glow)) for v in DEEP_ORANGE)
                draw.point((dx + bx, dy + 1), fill=bc)
            for bx in range(-1, 2):
                draw.point((dx + bx, dy), fill=tuple(int(v * (0.3 + 0.7 * glow)) for v in WARM_YELLOW))

            # Flame
            if glow > 0.2:
                flame_h = int(1 + glow * 2)
                for fh in range(flame_h):
                    fy = dy - 1 - fh
                    if fy >= 0:
                        flame_bright = glow * (1 - fh / (flame_h + 1))
                        draw.point((dx, fy), fill=tuple(int(v * flame_bright) for v in GOLD))
                        if fh == 0 and glow > 0.5:
                            draw.point((dx - 1, fy), fill=tuple(int(v * flame_bright * 0.5) for v in WARM_YELLOW))
                            draw.point((dx + 1, fy), fill=tuple(int(v * flame_bright * 0.5) for v in WARM_YELLOW))

            # Glow halo
            if glow > 0.4:
                for gx in range(-3, 4):
                    for gy in range(-3, 4):
                        gdist = math.sqrt(gx * gx + gy * gy)
                        if 2 < gdist < 4:
                            px, py = dx + gx, dy + gy
                            if 0 <= px < W and 0 <= py < H:
                                gb = glow * max(0, (4 - gdist) / 2) * 0.2
                                existing = img.getpixel((px, py))
                                new_c = tuple(min(255, int(existing[i] + gb * GOLD[i])) for i in range(3))
                                draw.point((px, py), fill=new_c)

        frames.append(img)

    save_gif(frames, "05_diya_wave", duration=80)


# ============================================================
# 6. LANTERN / KANDIL HANGING (Swaying lanterns)
# ============================================================
def generate_lanterns():
    print("\n6. Generating Hanging Lanterns (Kandil)...")
    NUM_FRAMES = 36

    lanterns = [
        {"x": 5, "color": RED, "phase": 0},
        {"x": 10, "color": GOLD, "phase": 1},
        {"x": 15, "color": MAGENTA, "phase": 2},
        {"x": 20, "color": GREEN, "phase": 0.5},
        {"x": 25, "color": TEAL, "phase": 1.5},
    ]

    frames = []
    for f in range(NUM_FRAMES):
        img = Image.new("RGB", (W, H), (5, 2, 12))
        draw = ImageDraw.Draw(img)

        # Top decorative string
        for x in range(W):
            catenary = int(2 + 1.5 * math.sin(x * math.pi / W))
            draw.point((x, catenary), fill=(80, 60, 20))

        for lant in lanterns:
            lx = lant["x"]
            sway = int(math.sin((f * 0.2 + lant["phase"]) * math.pi) * 1.5)
            cx = lx + sway
            cy_top = 5
            color = lant["color"]

            # String
            for sy in range(0, cy_top):
                draw.point((cx, sy), fill=(80, 60, 20))

            # Diamond/kandil shape
            # Top triangle
            draw.point((cx, cy_top), fill=color)
            for row in range(1, 5):
                half_w = min(row, 3)
                for dx in range(-half_w, half_w + 1):
                    c = color if abs(dx) < half_w else tuple(max(0, v - 60) for v in color)
                    draw.point((cx + dx, cy_top + row), fill=c)

            # Bottom triangle
            for row in range(1, 5):
                half_w = max(0, 3 - row)
                for dx in range(-half_w, half_w + 1):
                    c = color if abs(dx) < half_w else tuple(max(0, v - 60) for v in color)
                    draw.point((cx + dx, cy_top + 4 + row), fill=c)

            # Bottom tassel
            tassel_y = cy_top + 9
            for ty in range(3):
                draw.point((cx, tassel_y + ty), fill=tuple(max(0, v - 80) for v in color))

            # Inner glow
            glow_phase = 0.7 + 0.3 * math.sin(f * 0.3 + lant["phase"])
            inner_c = tuple(min(255, int(v * glow_phase + 40)) for v in color)
            draw.point((cx, cy_top + 3), fill=inner_c)
            draw.point((cx, cy_top + 4), fill=inner_c)

            # Light pool below
            pool_y = cy_top + 13
            for py in range(pool_y, min(H, pool_y + 10)):
                fade = 1.0 - (py - pool_y) / 10
                pool_w = int(1 + (py - pool_y) * 0.5)
                for pdx in range(-pool_w, pool_w + 1):
                    px = cx + pdx
                    if 0 <= px < W and 0 <= py < H:
                        brightness = fade * glow_phase * 0.15
                        existing = img.getpixel((px, py))
                        new_c = tuple(min(255, int(existing[i] + brightness * color[i])) for i in range(3))
                        draw.point((px, py), fill=new_c)

        frames.append(img)

    save_gif(frames, "06_hanging_lanterns", duration=90)


if __name__ == "__main__":
    import os
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    generate_floating_diyas()
    generate_rangoli()
    generate_fireworks()
    generate_text_sparkle()
    generate_diya_wave()
    generate_lanterns()

    print(f"\n✅ All GIFs generated in: {OUTPUT_DIR}")
    print("Upload the *_native.gif files to Govee Home App.")
    print("View the *_preview.gif files to see scaled previews.")
