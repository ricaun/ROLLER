#!/usr/bin/env python3
#MISE description="Build for specific platform"

#USAGE flag "-r --run" help="Run after building"
#USAGE flag "--target <target>" help="Build target"
#USAGE flag "--release <release>" help="Release mode"

import os
import sys
import subprocess

def main():
    print("Building ROLLER...")
    
    # Get environment variables that mise sets for parsed arguments
    run_after = os.environ.get("usage_run", "false") == "true"
    target = os.environ.get("usage_target", "native")
    release = os.environ.get("usage_release", "fast")
    
    # Build command arguments
    cmd = ["zig", "build", f"--release={release}", f"-Dtarget={target}"]
    
    if run_after:
        cmd.append("run")
    
    # Print build info
    print(f"🔨 Building for {target}...")
    
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