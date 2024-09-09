#!/bin/bash

# Check if pandoc is installed, if not, install it
if ! command -v pandoc &> /dev/null; then
    echo "Pandoc is not installed. Installing Pandoc..."
    sudo apt-get update
    sudo apt-get install -y pandoc
fi

# Check if TeX Live is installed, if not, install it
if ! command -v pdflatex &> /dev/null; then
    echo "TeX Live is not installed. Installing TeX Live..."
    sudo apt-get update
    sudo apt-get install -y texlive-full
fi

# Output PDF filename
output_file="output.pdf"

# Find all markdown files in the current directory and subdirectories
markdown_files=$(find . -name "*.md" -printf '%T@ %p\n' | sort -n | cut -d' ' -f2-)

# Check if index.md exists and put it at the beginning of the list
if [[ -f "index.md" ]]; then
    markdown_files=$(echo -e "index.md\n$(echo "$markdown_files" | grep -v "index.md")")
fi

# Compile the markdown files into a single PDF using pandoc with Unicode support
pandoc $markdown_files \
    --pdf-engine=xelatex \
    -V mainfont="IBMPlexSansKR" \
    -V monofont="D2Coding" \
    -V monofontfallback="IBMPlexSansKR" \
    -V fontsize=11pt \
    -V geometry:margin=1in \
    --toc \
    --highlight-style=tango \
    -o "$output_file"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation complete. Output saved as $output_file"
else
    echo "Error: Compilation failed."
    exit 1
fi