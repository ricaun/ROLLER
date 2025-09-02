#!/usr/bin/env bash
#MISE description="Build for specific platform"

#USAGE flag "--target <target>" help="Build target"
#USAGE flag "--release <release>" help="Release mode"

set -euo pipefail

echo "Building ROLLER..."

# Build with Zig for macOS Apple Silicon target
echo "🔨 Building for ${usage_target:-native}..."
zig build --release=${usage_release:-fast} -Dtarget=${usage_target:-native}

echo "✅ macOS ARM64 build completed successfully"
echo "📁 Binary location: zig-out/bin/ROLLER"
