#!/usr/bin/env python3
"""
Script for formatting .h and .c files using clang-format
"""

import os
import sys
import subprocess
from pathlib import Path


def find_files(directory, extensions):
    """
    Recursively finds all files with given extensions
    
    Args:
        directory: Directory to search in
        extensions: List of file extensions (e.g., ['.h', '.c'])
    
    Returns:
        List of paths to found files
    """
    files = []
    for ext in extensions:
        files.extend(Path(directory).rglob(f'*{ext}'))
    return sorted(files)


def format_file(file_path, style_file):
    """
    Formats a file using clang-format
    
    Args:
        file_path: Path to file to format
        style_file: Path to style configuration file
    
    Returns:
        True if successful, False on error
    """
    try:
        cmd = ['clang-format-15', '-i', f'--style=file:{style_file}', str(file_path)]
        result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Error formatting {file_path}: {e.stderr}", file=sys.stderr)
        return False
    except FileNotFoundError:
        print("Error: clang-format not found. Install it and add to PATH.", file=sys.stderr)
        sys.exit(1)


def main():
    # Check arguments
    if len(sys.argv) != 2:
        print("Usage: python3 format_code.py <style_file>", file=sys.stderr)
        sys.exit(1)
    
    # Settings
    source_dir = 'srcs'
    style_file = sys.argv[1]
    extensions = ['.h', '.c']
    
    # Check directory exists
    if not os.path.isdir(source_dir):
        print(f"Error: directory '{source_dir}' not found", file=sys.stderr)
        sys.exit(1)
    
    # Check style file exists
    if not os.path.isfile(style_file):
        print(f"Error: style file '{style_file}' not found", file=sys.stderr)
        sys.exit(1)
    
    # Find files
    print(f"Searching for {', '.join(extensions)} files in directory '{source_dir}'...")
    files = find_files(source_dir, extensions)
    
    if not files:
        print("No files found")
        return
    
    print(f"Found files: {len(files)}")
    
    # Format files
    success_count = 0
    fail_count = 0
    
    for file_path in files:
        print(f"Formatting: {file_path}")
        if format_file(file_path, style_file):
            success_count += 1
        else:
            fail_count += 1
    
    # Summary
    print(f"\nDone!")
    print(f"Successfully formatted: {success_count}")
    if fail_count > 0:
        print(f"Errors: {fail_count}")
        sys.exit(1)


if __name__ == '__main__':
    main()