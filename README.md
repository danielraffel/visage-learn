## Visage Learn

Small playground plugin/app that demonstrates the Visage UI toolkit wired through clap-wrapper. The UI shows a few rotary knobs and a simple button, rendered via Visage shaders and assets.

### Outputs
- **Standalone app**: `Visage Learn.app`
- **CLAP**: `Visage Learn.clap`
- **VST3**: `Visage Learn.vst3`
- **AUv2**: `Visage Learn.component`

On macOS, plugin bundles are installed to the user locations during the build:
- CLAP → `~/Library/Audio/Plug-Ins/CLAP/`
- VST3 → `~/Library/Audio/Plug-Ins/VST3/`
- AUv2 → `~/Library/Audio/Plug-Ins/Components/`

### Prereqs
- macOS 13+ recommended (Apple Silicon works great)
- Xcode command line tools (`xcode-select --install`)
- CMake ≥ 3.24 (tested with 4.x)
- Git (for submodules)

### Get the code
```bash
git clone https://github.com/your-org/visage-learn.git
cd visage-learn
git submodule update --init --recursive
```

### Build (Apple Silicon, Release)
```bash
cmake -S . -B build/macos-arm64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build/macos-arm64 -j8
```

Artifacts will be written to:
- Standalone app: `build/macos-arm64/visage-learn_assets/Visage Learn.app`
- Plugins: installed under your `~/Library/Audio/Plug-Ins/...` folders as listed above

Run the standalone:
```bash
open "build/macos-arm64/visage-learn_assets/Visage Learn.app"
```

### Build (Debug)
```bash
cmake -S . -B build/macos-arm64-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_OSX_ARCHITECTURES=arm64
cmake --build build/macos-arm64-debug -j8
```

### Universal binary (arm64 + x86_64)
If you need universal plugins/app:
```bash
cmake -S . -B build/macos-universal -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64"
cmake --build build/macos-universal -j8
```

### Clean build
```bash
rm -rf build/macos-*
```

### What you’re seeing
The screenshot in this repo shows:
- A Visage surface with four rotary knobs (custom draw + animated arcs)
- A rounded Visage button labeled "hello"
- Everything is shader-driven through bgfx; font/asset files are embedded at build time

### Troubleshooting
- "include could not find ... sst-plugininfra" → you skipped submodules. Run:
  ```bash
  git submodule update --init --recursive
  ```
- If CMake can’t find a compiler, make sure Xcode CLTs are installed: `xcode-select --install`
- If AU doesn’t show up, restart the host or run `killall -9 AudioComponentRegistrar`

### License
See `LICENSE.md`.


