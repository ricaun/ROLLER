#!/usr/bin/env bash
#MISE description="Build for specific platform"

#USAGE flag "--target <target>" help="Build target"
#USAGE flag "--release <release>" help="Release mode"
#USAGE flag "--run" help="Run after building"

set -euo pipefail

echo "Building ROLLER..."

ARGS=""
if [ -n usage_run ]; then
    ARGS="run"
fi

# Build with Zig for macOS Apple Silicon target
echo "🔨 Building for ${usage_target:-native}..."
zig build --release=${usage_release:-fast} -Dtarget=${usage_target:-native} $ARGS

echo "✅ Build completed successfully"
echo "📁 Binary location: zig-out/bin/roller"
