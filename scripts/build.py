#!/usr/bin/env python3

import os
import sys
import subprocess
import platform
import argparse

def main():
    parser = argparse.ArgumentParser(description="Build ROLLER for specific platform")
    parser.add_argument("-r", "--run", action="store_true", help="Run after building")
    parser.add_argument("--target", default="native", help="Build target")
    parser.add_argument("--release", default="fast", help="Release mode")
    
    args = parser.parse_args()
    
    print("Building ROLLER...")
    
    # Build command arguments
    cmd = ["zig", "build", f"--release={args.release}", f"-Dtarget={args.target}"]
    
    # Add sysroot for macOS builds
    if platform.system() == "Darwin" and "macos" in args.target:
        cmd.extend(["--sysroot", "/"])
    
    if args.run:
        cmd.append("run")
    
    # Print build info
    print(f"🔨 Building for {args.target}...")
    
    # Run the build command
    result = subprocess.run(cmd)
    
    # Check if build succeeded
    if result.returncode == 0:
        print("✅ Build completed successfully")
        print("📁 Binary location: zig-out/bin/roller")
        return 0
    else:
        print("❌ Build failed")
        return 1

if __name__ == "__main__":
    sys.exit(main())