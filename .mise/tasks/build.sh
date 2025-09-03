#!/usr/bin/env bash
#MISE description="Build for specific platform"

#USAGE flag "-r --run" help="Run after building"
#USAGE flag "--target <target>" help="Build target"
#USAGE flag "--release <release>" help="Release mode"

echo "Building ROLLER..."

ARGS=""
if [ "$usage_run" = "true" ]; then
    ARGS="run"
fi

# Build with Zig for macOS Apple Silicon target
echo "🔨 Building for ${usage_target:-native}..."
zig build --release=${usage_release:-fast} -Dtarget=${usage_target:-native} $ARGS

# Check if build succeeded
if [ $? -eq 0 ]; then
    echo "✅ Build completed successfully"
    echo "📁 Binary location: zig-out/bin/roller"
else
    echo "❌ Build failed"
    exit 1
fi
