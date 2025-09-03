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
    
    # Check for unsupported cross-compilation
    if "macos" in args.target and platform.system() != "Darwin":
        print("Error: Cross-compilation to macOS requires running on macOS")
        print("Please use a macOS system or GitHub Actions with macos runners")
        return 1
    
    # Build command arguments
    cmd = ["zig", "build", f"--release={args.release}", f"-Dtarget={args.target}"]
    
    # Add sysroot for macOS builds when running on macOS
    if platform.system() == "Darwin" and "macos" in args.target:
        # Use xcrun to find the correct SDK path
        try:
            sdk_path = subprocess.check_output(["xcrun", "--show-sdk-path"], text=True).strip()
            cmd.extend(["--sysroot", sdk_path])
        except subprocess.CalledProcessError:
            # Fallback to root if xcrun fails
            cmd.extend(["--sysroot", "/"])
    
    if args.run:
        cmd.append("run")
    
    # Print build info
    print(f"Building for {args.target}...")
    
    # Run the build command
    result = subprocess.run(cmd)
    
    # Check if build succeeded
    if result.returncode == 0:
        print("Build completed successfully")
        print("Binary location: zig-out/bin/roller")
        return 0
    else:
        print("Build failed")
        return 1

if __name__ == "__main__":
    sys.exit(main())